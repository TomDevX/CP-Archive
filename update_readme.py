import os
import re
import datetime

# --- CONFIGURATION ---
EXCLUDE_DIRS = {'.git', '.github', '.assets', 'venv', '__pycache__'}
README_FILE = 'README.md'
HEADER_FILE = 'HEADER.md'

def format_display_name(name):
    """Làm đẹp tên folder/file: '03_dynamic_programming' -> 'Dynamic Programming'"""
    parts = name.split('_')
    if parts[0].isdigit():
        parts = parts[1:]
    return " ".join(parts).replace('-', ' ').title()

def extract_metadata(file_path):
    """
    Trích xuất metadata từ 15 dòng đầu của file C++.
    Cấu trúc: title, source, submission, algorithm.
    """
    meta = {"source": None, "submission": None, "algorithm": "N/A", "title": None}
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            for _ in range(15):
                line = f.readline()
                if not line: break
                line_lower = line.lower()
                
                if "title:" in line_lower:
                    meta["title"] = line.split("title:")[1].replace('**/', '').replace('*', '').strip()
                elif "source:" in line_lower:
                    match = re.search(r'(https?://[^\s]+)', line)
                    if match: meta["source"] = match.group(1)
                elif "submission:" in line_lower:
                    match = re.search(r'(https?://[^\s]+)', line)
                    if match: meta["submission"] = match.group(1)
                elif "algorithm:" in line_lower:
                    meta["algorithm"] = line.split("algorithm:")[1].replace('**/', '').replace('*', '').strip()
    except:
        pass
    return meta

def auto_generate_link(file_path):
    """Tự động tạo link dựa trên tên folder (OJ) và tên file (ID)"""
    path_parts = file_path.replace('\\', '/').split('/')
    filename = path_parts[-1].replace('.cpp', '')
    oj_name = ""
    for part in reversed(path_parts[:-1]):
        upper_part = part.upper()
        if any(oj in upper_part for oj in ["CSES", "CODEFORCES", "CF", "VNOI", "LEETCODE"]):
            oj_name = upper_part
            break
    if not oj_name: return None
    
    if "CSES" in oj_name:
        id_match = re.search(r'(\d+)', filename)
        return f"https://cses.fi/problemset/task/{id_match.group(1)}" if id_match else None
    if "CODEFORCES" in oj_name or "CF" in oj_name:
        cf_match = re.search(r'(\d+)\s*[_-]?\s*([A-Z]\d?)', filename.upper())
        return f"https://codeforces.com/contest/{cf_match.group(1)}/problem/{cf_match.group(2)}" if cf_match else None
    if "VNOI" in oj_name:
        return f"https://oj.vnoi.info/problem/{filename.lower()}"
    if "LEETCODE" in oj_name:
        return f"https://leetcode.com/problems/{filename.lower().replace('_', '-')}/"
    return None

def generate_readme():
    if os.path.exists(HEADER_FILE):
        with open(HEADER_FILE, 'r', encoding='utf-8') as f:
            content = f.read() + "\n\n---\n"
    else:
        content = "# 🏆 Competitive Programming Repository\n\n"

    total_problems = 0
    main_content = ""
    root_dirs = sorted([d for d in os.listdir('.') if os.path.isdir(d) and d not in EXCLUDE_DIRS])

    for root_dir in root_dirs:
        category_header = f"## 📂 {format_display_name(root_dir)}\n"
        subfolder_content = ""

        for root, dirs, files in os.walk(root_dir):
            dirs[:] = sorted([d for d in dirs if d not in EXCLUDE_DIRS])
            cpp_files_in_folder = [f for f in files if f.endswith('.cpp')]
            if not cpp_files_in_folder: continue

            relative_path = os.path.relpath(root, root_dir)
            header = category_header if relative_path == "." else f"### 📁 {format_display_name(relative_path)}\n"

            problem_list = []
            for file in cpp_files_in_folder:
                full_path = os.path.join(root, file)
                meta = extract_metadata(full_path)
                
                display_name = meta["title"] if meta["title"] else format_display_name(file.replace('.cpp', ''))
                prob_link = meta["source"] or auto_generate_link(full_path)
                
                problem_list.append({
                    "name": display_name,
                    "link": prob_link,
                    "submission": meta["submission"],
                    "algo": meta["algorithm"],
                    "path": full_path.replace('\\', '/')
                })

            problem_list.sort(key=lambda x: x["name"].lower())

            # Điều chỉnh tiêu đề bảng: Đưa Submission vào chung cột hoặc riêng tùy ý
            # Ở đây tôi giữ cấu trúc gọn: Tên bài (Link) | Algorithm | Solution (Code + Submission)
            table = "| # | Problem Name | Algorithm | Solution |\n"
            table += "| :--- | :--- | :--- | :--- |\n"
            for i, p in enumerate(problem_list, 1):
                name_display = f"[{p['name']}]({p['link']})" if p['link'] else p['name']
                # Đổi Verify thành Submission theo yêu cầu
                submission_link = f" \| [Submission]({p['submission']})" if p['submission'] else ""
                table += f"| {i} | {name_display} | `{p['algo']}` | [Code]({p['path']}){submission_link} |\n"
                total_problems += 1
            
            subfolder_content += header + table + "\n"
        main_content += subfolder_content

    # Cập nhật dòng Last Update theo yêu cầu
    now = datetime.datetime.now().strftime("%a %b %d %Y")
    stats = f"### 📊 Repository Stats\n- **Total Problems:** {total_problems}\n- **Last Update:** {now}\n\n"
    
    with open(README_FILE, 'w', encoding='utf-8') as f:
        f.write(content + stats + main_content)
    print(f"✅ Success! README updated with {total_problems} problems.")

if __name__ == "__main__":
    generate_readme()