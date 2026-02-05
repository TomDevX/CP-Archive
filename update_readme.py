import os
import re
import subprocess
from datetime import datetime, timedelta, timezone

EXCLUDE_DIRS = {'.git', '.github', '.assets', 'venv', '__pycache__'}
README_FILE = 'README.md'
HEADER_FILE = 'HEADER.md'
CITY_ID = 218 

def natural_sort_key(s):
    return [int(text) if text.isdigit() else text.lower()
            for text in re.split('([0-9]+)', s)]

def get_last_commit_time():
    try:
        timestamp = subprocess.check_output(['git', 'log', '-1', '--format=%at']).decode('utf-8').strip()
        tz_hcm = timezone(timedelta(hours=7))
        return datetime.fromtimestamp(int(timestamp), tz=tz_hcm)
    except Exception:
        return datetime.now(timezone(timedelta(hours=7)))

def format_display_name(name):
    parts = name.split('_')
    if parts[0].isdigit():
        parts = parts[1:]
    return " ".join(parts).replace('-', ' ').title()

def extract_metadata(file_path):
    meta = {"source": None, "submission": None, "algorithm": "N/A", "complexity": "N/A", "title": None}
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            in_header = False
            for i, line in enumerate(f):
                line_strip = line.strip()
                if line_strip.startswith("/**"):
                    in_header = True
                    continue
                if "**/ " in line_strip or line_strip.endswith("**/"):
                    break
                if in_header:
                    clean_line = line_strip.lstrip('*').strip()
                    lower_line = clean_line.lower()
                    if lower_line.startswith("title:"):
                        val = clean_line[6:].strip()
                        if val: meta["title"] = val
                    elif lower_line.startswith("source:"):
                        match = re.search(r'(https?://[^\s]+)', clean_line)
                        if match: meta["source"] = match.group(1)
                    elif lower_line.startswith("submission:"):
                        match = re.search(r'(https?://[^\s]+)', clean_line)
                        if match: meta["submission"] = match.group(1)
                    elif lower_line.startswith("algorithm:"):
                        val = clean_line[10:].strip()
                        if val:
                            algos = [f"`{a.strip()}`" for a in val.split(',') if a.strip()]
                            meta["algorithm"] = ", ".join(algos)
                    elif lower_line.startswith("complexity:"):
                        val = clean_line[11:].strip()
                        if val:
                            if any(p in val for p in ["\\mathcal{O}", "\\Theta", "\\Omega"]):
                                meta["complexity"] = f"${val}$"
                            else:
                                inner = re.sub(r'^[Oo]\s*\((.*)\)$', r'\1', val).strip()
                                meta["complexity"] = f"$\\mathcal{{O}}({inner})$"
    except Exception: pass
    return meta

def auto_generate_link(file_path):
    path_parts = file_path.replace('\\', '/').split('/')
    filename = path_parts[-1].replace('.cpp', '').upper()
    for part in reversed(path_parts[:-1]):
        up = part.upper()
        if "CODEFORCES" in up or "CF" in up:
            cf_match = re.search(r'(\d+)\s*[_-]?\s*([A-Z]\d?)', filename)
            if cf_match: return f"https://codeforces.com/contest/{cf_match.group(1)}/problem/{cf_match.group(2)}"
        if "CSES" in up:
            m = re.search(r'(\d+)', filename)
            if m: return f"https://cses.fi/problemset/task/{m.group(1)}"
        if "VNOI" in up: return f"https://oj.vnoi.info/problem/{filename.lower()}"
        if "LEETCODE" in up: return f"https://leetcode.com/problems/{filename.lower().replace('_', '-')}/"
    return None

def generate_readme():
    if os.path.exists(HEADER_FILE):
        with open(HEADER_FILE, 'r', encoding='utf-8') as f:
            content = f.read() + "\n\n---\n"
    else:
        content = "# 🏆 Competitive Programming Repository\n\n"

    total_problems = 0
    main_content = ""
    toc_content = "## 📌 Table of Contents\n\n"
    
    root_dirs = sorted([d for d in os.listdir('.') if os.path.isdir(d) and d not in EXCLUDE_DIRS], key=natural_sort_key)

    for root_dir in root_dirs:
        is_sol_dir = root_dir.lower() == "solutions"
        root_title = format_display_name(root_dir)
        root_anchor = root_title.lower().replace(" ", "-")
        toc_content += f"* [📂 {root_title}](#-{root_anchor})\n"
        main_content += f"## 📂 {root_title}\n"
        
        folder_data = []
        for root, dirs, files in os.walk(root_dir):
            dirs[:] = [d for d in dirs if d not in EXCLUDE_DIRS]
            
            # Logic lọc file theo yêu cầu mới của Tom
            if is_sol_dir:
                # Chỉ lấy file .cpp
                relevant_files = [f for f in files if f.endswith('.cpp')]
            else:
                # Lấy file có extension (ví dụ: .pdf, .txt, .md, .py...)
                relevant_files = [f for f in files if os.path.splitext(f)[1]]
                
            if relevant_files: folder_data.append((root, relevant_files))

        folder_data.sort(key=lambda x: natural_sort_key(x[0]))
        for path, files in folder_data:
            relative_path = os.path.relpath(path, root_dir)
            if relative_path != ".":
                sub_title = format_display_name(relative_path)
                sub_anchor = sub_title.lower().replace(" ", "-")
                toc_content += f"  * [📁 {sub_title}](#-{sub_anchor})\n"
                main_content += f"### 📁 {sub_title}\n"
            
            files.sort(key=natural_sort_key)
            
            if is_sol_dir:
                table = "| # | Problem Name | Algorithm | Complexity | Solution |\n| :--- | :--- | :--- | :--- | :--- |\n"
                for i, file in enumerate(files, 1):
                    full_path = os.path.join(path, file)
                    meta = extract_metadata(full_path)
                    
                    filename_no_ext = file.replace('.cpp', '')
                    file_id = filename_no_ext.split('_')[0].upper() if '_' in filename_no_ext else filename_no_ext.upper()
                    
                    if meta["title"]:
                        display_name = f"{file_id} - {meta['title']}"
                    elif '_' in filename_no_ext:
                        display_name = f"{file_id} - {format_display_name(filename_no_ext)}"
                    else:
                        display_name = file_id
                    
                    prob_link = meta["source"] or auto_generate_link(full_path)
                    name_md = f"[{display_name}]({prob_link})" if prob_link else display_name
                    sol_md = f"[Code]({full_path.replace('\\', '/')})"
                    
                    # FIX: Dùng double backslash '\\|' để tránh SyntaxWarning
                    if meta["submission"]: sol_md += f" \\| [Sub]({meta['submission']})"
                    
                    table += f"| {i} | {name_md} | {meta['algorithm']} | {meta['complexity']} | {sol_md} |\n"
                    total_problems += 1
            else:
                table = "| File Name | Source |\n| :--- | :--- |\n"
                for file in files:
                    full_path = os.path.join(path, file).replace('\\', '/')
                    display_name = os.path.splitext(file)[0]
                    table += f"| {display_name} | [Link]({full_path}) |\n"

            main_content += table + "\n"

    push_time = get_last_commit_time()
    iso_string = push_time.strftime("%Y%m%dT%H%M")
    time_str = push_time.strftime("%b %d, %Y - %H:%M (GMT+7)")
    badge_msg = f"{time_str}_🖱️_[CLICK_TO_CONVERT]".replace("-", "--").replace(" ", "_")
    badge_url = f"https://img.shields.io/badge/Last_Update-{badge_msg}-0078d4?style=for-the-badge&logo=github"
    time_link = f"https://www.timeanddate.com/worldclock/fixedtime.html?msg=Convert+to+your+timezone&iso={iso_string}&p1={CITY_ID}"

    stats = f"### 📊 Repository Stats\n\n- **Total Problems:** {total_problems}\n- **Origin Timezone:** Ho Chi Minh City (GMT+7)\n\n"
    stats += f"[![Last Update]({badge_url})]({time_link} \"🖱️ CLICK TO CONVERT\")\n\n---\n"
    
    with open(README_FILE, 'w', encoding='utf-8') as f:
        f.write(content + stats + toc_content + "\n---\n" + main_content)
    print(f"✅ README Updated (City ID: {CITY_ID})")

if __name__ == "__main__":
    generate_readme()