import os
import re
import subprocess
from datetime import datetime, timedelta, timezone

# --- CONFIGURATION ---
EXCLUDE_DIRS = {'.git', '.github', '.assets', 'venv', '__pycache__'}
README_FILE = 'README.md'
HEADER_FILE = 'HEADER.md'

# ĐÍNH CHÍNH: 218 là Hồ Chí Minh (Vietnam)
CITY_ID = 218 

def natural_sort_key(s):
    """
    Hỗ trợ sort tự nhiên: '2.cpp' sẽ đứng trước '10.cpp'
    Tách chuỗi thành list gồm số (int) và chữ (str).
    """
    return [int(text) if text.isdigit() else text.lower()
            for text in re.split('([0-9]+)', s)]

def get_last_commit_time():
    """Lấy Unix timestamp của commit cuối cùng từ Git."""
    try:
        timestamp = subprocess.check_output(['git', 'log', '-1', '--format=%at']).decode('utf-8').strip()
        tz_hcm = timezone(timedelta(hours=7))
        return datetime.fromtimestamp(int(timestamp), tz=tz_hcm)
    except Exception:
        return datetime.now(timezone(timedelta(hours=7)))

def format_display_name(name):
    """Làm đẹp tên folder/file."""
    parts = name.split('_')
    if parts[0].isdigit():
        parts = parts[1:]
    return " ".join(parts).replace('-', ' ').title()

def extract_metadata(file_path):
    """Trích xuất metadata: title, source, submission, algorithm."""
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
                    raw_algo = line.split("algorithm:")[1].replace('**/', '').replace('*', '').strip()
                    algos = [f"`{a.strip()}`" for a in raw_algo.split(',') if a.strip()]
                    meta["algorithm"] = ", ".join(algos)
    except: pass
    return meta

def auto_generate_link(file_path):
    """Tự động tạo link OJ dựa trên folder."""
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
    if "VNOI" in oj_name: return f"https://oj.vnoi.info/problem/{filename.lower()}"
    if "LEETCODE" in oj_name: return f"https://leetcode.com/problems/{filename.lower().replace('_', '-')}/"
    return None

def generate_readme():
    if os.path.exists(HEADER_FILE):
        with open(HEADER_FILE, 'r', encoding='utf-8') as f:
            content = f.read() + "\n\n---\n"
    else:
        content = "# 🏆 Competitive Programming Repository\n\n"

    total_problems = 0
    main_content = ""
    root_dirs = sorted([d for d in os.listdir('.') if os.path.isdir(d) and d not in EXCLUDE_DIRS], key=natural_sort_key)

    for root_dir in root_dirs:
        category_main_header = f"## 📂 {format_display_name(root_dir)}\n"
        folder_data = []
        for root, dirs, files in os.walk(root_dir):
            dirs[:] = [d for d in dirs if d not in EXCLUDE_DIRS]
            cpp_files = [f for f in files if f.endswith('.cpp')]
            if cpp_files: folder_data.append((root, cpp_files))

        # Sort folder và file theo logic tự nhiên (ID số)
        folder_data.sort(key=lambda x: natural_sort_key(x[0]))
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
                    "algo": meta["algorithm"], "path": full_path.replace('\\', '/'),
                    "raw_filename": file # Để dùng cho sorting
                })
            
            # SORTING THEO ID (Sử dụng filename gốc để chính xác nhất)
            problem_list.sort(key=lambda x: natural_sort_key(x["raw_filename"]))

            table = "| # | Problem Name | Algorithm | Solution |\n| :--- | :--- | :--- | :--- |\n"
            for i, p in enumerate(problem_list, 1):
                name_display = f"[{p['name']}]({p['link']})" if p['link'] else p['name']
                sub_link = f" \| [Submission]({p['submission']})" if p['submission'] else ""
                table += f"| {i} | {name_display} | {p['algo']} | [Code]({p['path']}){sub_link} |\n"
                total_problems += 1
            sub_sections += header + table + "\n"
        main_content += sub_sections

    # --- CẤU HÌNH THỜI GIAN THEO PUSH (GMT+7) ---
    push_time = get_last_commit_time()
    iso_string = push_time.strftime("%Y%m%dT%H%M")
    
    # Badge: Thêm Icon CLICK và hiệu ứng Hover
    time_str = push_time.strftime("%b %d, %Y - %H:%M (GMT+7)")
    badge_msg = f"{time_str}_🖱️_[CLICK_TO_CONVERT]".replace("-", "--").replace(" ", "_")
    
    badge_url = f"https://img.shields.io/badge/Last_Update-{badge_msg}-0078d4?style=for-the-badge&logo=github"
    time_link = f"https://www.timeanddate.com/worldclock/fixedtime.html?msg=Convert+to+your+timezone&iso={iso_string}&p1={CITY_ID}"

    # --- TỔNG HỢP STATS ---
    stats = f"### 📊 Repository Stats\n\n"
    stats += f"- **Total Problems:** {total_problems}\n"
    stats += f"- **Origin Timezone:** Ho Chi Minh City (GMT+7)\n\n"
    
    stats += f"[![Last Update]({badge_url})]({time_link} \"🖱️ Click to convert to your timezone\")\n\n"
    stats += f"**TIP:** *Click the badge above to see when this was updated in your time.* 🌍\n\n"
    stats += f"---\n"
    
    with open(README_FILE, 'w', encoding='utf-8') as f:
        f.write(content + stats + main_content)
    print(f"✅ README Updated (Push Time: {push_time.strftime('%H:%M')}, City ID: {CITY_ID})")

if __name__ == "__main__":
    generate_readme()