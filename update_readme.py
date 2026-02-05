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
    tz_hcm = timezone(timedelta(hours=7))
    return datetime.now(tz=tz_hcm)

def format_display_name(name):
    if not name: return ""
    parts = name.split('_')
    if parts[0].isdigit():
        parts = parts[1:]
    return " ".join(parts).replace('-', ' ').title()

def create_slug(text):
    slug = text.lower().replace(" ", "-")
    slug = re.sub(r'[^\w\-]', '', slug)
    return slug

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
        if "LEETCODE" in up:
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
    toc_content = "## 📌 Table of Contents\n\n"
    
    root_dir = "solutions"
    if not os.path.isdir(root_dir):
        print(f"⚠️ Thư mục '{root_dir}' không tồn tại.")
        return

    # --- 1. Tạo TOC (Bỏ folder Solutions, bắt đầu từ cấp con) ---
    added_to_toc = set()
    for root, dirs, files in os.walk(root_dir):
        dirs[:] = sorted([d for d in dirs if d not in EXCLUDE_DIRS], key=natural_sort_key)
        
        # Lấy đường dẫn tương đối so với 'solutions'
        rel_path = os.path.relpath(root, root_dir)
        if rel_path == ".":
            continue # Bỏ qua chính folder 'solutions' trong TOC
            
        parts = rel_path.split(os.sep)
        for i in range(len(parts)):
            # Đường dẫn đầy đủ để kiểm tra trùng lặp
            current_path = os.path.join(root_dir, *parts[:i+1])
            if current_path not in added_to_toc:
                depth = i # Độ sâu bắt đầu từ 0 cho các con của solutions
                indent = "  " * depth
                raw_name = parts[i]
                
                title = "CSES" if raw_name.lower() == "cses" else format_display_name(raw_name)
                toc_content += f"{indent}* [📂 {title}](#-{create_slug(title)})\n"
                added_to_toc.add(current_path)

    # --- 2. Tạo Nội Dung Chính ---
    folder_data = []
    for root, dirs, files in os.walk(root_dir):
        dirs[:] = sorted([d for d in dirs if d not in EXCLUDE_DIRS], key=natural_sort_key)
        cpp_files = [f for f in files if f.endswith('.cpp')]
        if cpp_files:
            folder_data.append((root, cpp_files))

    folder_data.sort(key=lambda x: natural_sort_key(x[0]))
    
    for path, files in folder_data:
        rel_path_from_sol = os.path.relpath(path, root_dir)
        
        # Nếu là thư mục con trực tiếp của solutions -> Dùng Header H2 (##)
        # Nếu sâu hơn -> Dùng Header H3 (###)
        if rel_path_from_sol == ".":
            # Trường hợp có file .cpp nằm ngay trong solutions (thường ít có)
            main_content += f"## 📂 Solutions\n"
        else:
            base_name = os.path.basename(path)
            title = "CSES" if base_name.lower() == "cses" else format_display_name(base_name)
            if os.path.dirname(rel_path_from_sol) == "":
                main_content += f"## 📂 {title}\n"
            else:
                main_content += f"### 📁 {title}\n"
        
        files.sort(key=natural_sort_key)
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
            
            if meta["submission"]: sol_md += f" \\| [Sub]({meta['submission']})"
            
            table += f"| {i} | {name_md} | {meta['algorithm']} | {meta['complexity']} | {sol_md} |\n"
            total_problems += 1
        
        main_content += table + "\n"

    # --- 3. Badge & Stats ---
    push_time = get_last_commit_time()
    iso_string = push_time.strftime("%Y%m%dT%H%M")
    badge_url = f"https://img.shields.io/badge/Last_Update-{push_time.strftime('%b_%d,_%Y')}-0078d4?style=for-the-badge&logo=github"
    time_link = f"https://www.timeanddate.com/worldclock/fixedtime.html?msg=Convert+to+your+timezone&iso={iso_string}&p1={CITY_ID}"

    stats = f"### 📊 Repository Statss\n\n"
    stats += f"- **Total Problems:** {total_problems}\n"
    stats += f"- **Origin Timezone:** Ho Chi Minh City (GMT+7)\n\n"
    stats += f"[![Last Update]({badge_url})]({time_link} \"🖱️ CLICK TO CONVERT\")\n\n"
    stats += f"---\n"
    
    with open(README_FILE, 'w', encoding='utf-8') as f:
        f.write(content + stats + toc_content + "\n---\n" + main_content)
    print(f"✅ README Tinh gọn thành công (Bỏ qua folder mẹ 'solutions').")

if __name__ == "__main__":
    generate_readme()