import os
import re
import datetime

# --- CONFIGURATION ---
EXCLUDE_DIRS = {'.git', '.github', '.assets', 'venv', '__pycache__'}
README_FILE = 'README.md'
HEADER_FILE = 'HEADER.md'

def format_display_name(name):
    """Làm đẹp tên folder/file"""
    parts = name.split('_')
    if parts[0].isdigit():
        parts = parts[1:]
    return " ".join(parts).replace('-', ' ').title()

def extract_metadata(file_path):
    """Trích xuất metadata từ 15 dòng đầu: title, source, submission, algorithm."""
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
    """Tự động tạo link OJ dựa trên folder"""
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
        category_main_header = f"## 📂 {format_display_name(root_dir)}\n"
        folder_data = []
        for root, dirs, files in os.walk(root_dir):
            dirs[:] = [d for d in dirs if d not in EXCLUDE_DIRS]
            cpp_files = [f for f in files if f.endswith('.cpp')]
            if cpp_files:
                folder_data.append((root, cpp_files))

        folder_data.sort(key=lambda x: x[0].lower())
        sub_sections = ""
        for path, files in folder_data:
            relative_path = os.path.relpath(path, root_dir)
            header = category_main_header if relative_path == "." else f"### 📁 {format_display_name(relative_path)}\n"
            problem_list = []
            for file in files:
                full_path = os.path.join(path, file)
                meta = extract_metadata(full_path)
                display_name = meta["title"] if meta["title"] else format_display_name(file.replace('.cpp', ''))
                prob_link = meta["source"] or auto_generate_link(full_path)
                problem_list.append({
                    "name": display_name, "link": prob_link, "submission": meta["submission"],
                    "algo": meta["algorithm"], "path": full_path.replace('\\', '/')
                })
            problem_list.sort(key=lambda x: x["name"].lower())
            table = "| # | Problem Name | Algorithm | Solution |\n| :--- | :--- | :--- | :--- |\n"
            for i, p in enumerate(problem_list, 1):
                name_display = f"[{p['name']}]({p['link']})" if p['link'] else p['name']
                sub_link = f" \| [Submission]({p['submission']})" if p['submission'] else ""
                table += f"| {i} | {name_display} | `{p['algo']}` | [Code]({p['path']}){sub_link} |\n"
                total_problems += 1
            sub_sections += header + table + "\n"
        main_content += sub_sections

    # --- ĐỊNH DẠNG THEO CODEFORCES (CONTEST STYLE) ---
    # Feb/05/2026 12:30 (UTC+7)
    now = datetime.datetime.now()
    cf_time_format = now.strftime("%b/%d/%Y %H:%M")
    
    # Tạo link tự động chuyển đổi múi giờ cho người xem
    # Dùng trang 'Time.is' với tọa độ chính xác của bạn
    time_convert_link = f"https://time.is/{now.strftime('%H%M')}_05_Feb_2026_in_ICT"

    stats = f"### 📊 Repository Stats\n"
    stats += f"- **Total Problems:** {total_problems}\n"
    stats += f"- **Last Update:** [{cf_time_format} (UTC+7)]({time_convert_link})\n\n"
    
    with open(README_FILE, 'w', encoding='utf-8') as f:
        f.write(content + stats + main_content)
    print(f"✅ README Updated: {cf_time_format} (UTC+7)")

if __name__ == "__main__":
    generate_readme()