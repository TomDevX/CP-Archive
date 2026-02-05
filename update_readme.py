import os
import re
import datetime

# Configuration
EXCLUDE_DIRS = {'.git', '.github', '.assets', 'venv', '__pycache__'}
README_FILE = 'README.md'
HEADER_FILE = 'HEADER.md'

def format_display_name(name):
    parts = name.split('_')
    if parts[0].isdigit():
        parts = parts[1:]
    return " ".join(parts).replace('-', ' ').title()

def get_link_from_line_5(file_path):
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            lines = f.readlines()
            if len(lines) >= 5:
                line_5 = lines[4].strip()
                match = re.search(r'(https?://[^\s]+)', line_5)
                if match:
                    return match.group(1)
    except:
        pass
    return None

def auto_generate_link(file_path):
    """Tự động tạo link dựa trên tên folder (OJ) và tên file (ID)"""
    path_parts = file_path.replace('\\', '/').split('/')
    filename = path_parts[-1].replace('.cpp', '')
    
    # Tìm tên OJ trong đường dẫn (duyệt ngược từ folder chứa file lên)
    oj_name = ""
    for part in reversed(path_parts[:-1]):
        upper_part = part.upper()
        if any(oj in upper_part for oj in ["CSES", "CODEFORCES", "CF", "VNOI", "LEETCODE"]):
            oj_name = upper_part
            break
    
    if not oj_name: return None

    # 1. CSES Logic
    if "CSES" in oj_name:
        id_match = re.search(r'(\d+)', filename)
        if id_match:
            return f"https://cses.fi/problemset/task/{id_match.group(1)}"

    # 2. Codeforces Logic (Format: 123A hoặc 123_A)
    if "CODEFORCES" in oj_name or "CF" in oj_name:
        cf_match = re.search(r'(\d+)\s*[_-]?\s*([A-Z]\d?)', filename.upper())
        if cf_match:
            contest_id, index = cf_match.groups()
            return f"https://codeforces.com/contest/{contest_id}/problem/{index}"

    # 3. VNOI Logic
    if "VNOI" in oj_name:
        return f"https://oj.vnoi.info/problem/{filename.lower()}"

    # 4. LeetCode Logic
    if "LEETCODE" in oj_name:
        slug = filename.lower().replace('_', '-').replace(' ', '-')
        return f"https://leetcode.com/problems/{slug}/"

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
            cpp_files = sorted([f for f in files if f.endswith('.cpp')])
            if not cpp_files: continue

            relative_path = os.path.relpath(root, root_dir)
            header = category_header if relative_path == "." else f"### 📁 {format_display_name(relative_path)}\n"

            table = "| # | Problem Name | Problem Link | Solution |\n"
            table += "| :--- | :--- | :--- | :--- |\n"
            
            for i, file in enumerate(cpp_files, 1):
                full_path = os.path.join(root, file)
                prob_link = get_link_from_line_5(full_path) or auto_generate_link(full_path)
                
                display_name = format_display_name(file.replace('.cpp', ''))
                url_path = full_path.replace('\\', '/')
                link_display = f"[Problem Link]({prob_link})" if prob_link else "-"
                
                table += f"| {i} | {display_name} | {link_display} | [View Code]({url_path}) |\n"
                total_problems += 1
            subfolder_content += header + table + "\n"
        main_content += subfolder_content

    now = datetime.datetime.now().strftime("%a %b %d %Y")
    stats = f"### 📊 Repository Stats\n- **Total Items:** {total_problems}\n- **Last Sync:** {now}\n\n"
    
    with open(README_FILE, 'w', encoding='utf-8') as f:
        f.write(content + stats + main_content)
    print(f"✅ Success! Updated with {total_problems} problems.")

if __name__ == "__main__":
    generate_readme()