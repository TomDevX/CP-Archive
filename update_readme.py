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

# Hàm mới để đọc link từ file trong folder
def get_oj_link_from_file(folder_path):
    # Bạn có thể thêm các định dạng file khác vào list này
    link_files = ['link.txt', 'oj.txt', 'source.url']
    for file_name in link_files:
        file_path = os.path.join(folder_path, file_name)
        if os.path.exists(file_path):
            try:
                with open(file_path, 'r', encoding='utf-8') as f:
                    content = f.read().strip()
                    # Nếu là file .url (Windows shortcut), ta cần regex để lấy URL
                    if file_name.endswith('.url'):
                        match = re.search(r'URL=(https?://[^\s]+)', content)
                        if match: return match.group(1)
                    # Nếu là file txt thường, lấy luôn nội dung dòng đầu
                    if content.startswith('http'):
                        return content.split('\n')[0].strip()
            except Exception:
                pass
    return None

def format_display_name(name, is_oj=False):
    if not name: return ""
    if is_oj:
        return name
    parts = name.split('_')
    if parts[0].isdigit():
        parts = parts[1:]
    return " ".join(parts).replace('-', ' ').title()

def create_slug(text):
    slug = text.lower().replace(" ", "-")
    slug = re.sub(r'[^\w\-]', '', slug)
    return slug

def extract_metadata(file_path):
    meta = {"source": None, "submission": None, "tags": "N/A", "complexity": "N/A", "title": None, "date": "N/A"}
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
                    elif lower_line.startswith("created:"):
                        val = clean_line[8:].strip()
                        if val:
                            raw_date = val.split(' ')[0] 
                            try:
                                dt = datetime.strptime(raw_date, "%Y-%m-%d")
                                day = dt.strftime("%d").lstrip("0")
                                meta["date"] = dt.strftime(f"%b {day}, %Y")
                            except ValueError:
                                meta["date"] = raw_date
                    elif lower_line.startswith("submission:"):
                        match = re.search(r'(https?://[^\s]+)', clean_line)
                        if match: meta["submission"] = match.group(1)
                    elif lower_line.startswith("tags:"):
                        val = clean_line[5:].strip()
                        if val:
                            tags = [f"`{t.strip()}`" for t in val.split(',') if t.strip()]
                            meta["tags"] = ", ".join(tags)
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
    root_dir = "Solutions"
    if not os.path.isdir(root_dir):
        return
    added_to_toc = set()
    for root, dirs, files in os.walk(root_dir):
        dirs[:] = sorted([d for d in dirs if d not in EXCLUDE_DIRS], key=natural_sort_key)
        rel_path = os.path.relpath(root, root_dir)
        if rel_path == ".": continue
        parts = rel_path.split(os.sep)
        for i in range(len(parts)):
            current_path = os.path.join(root_dir, *parts[:i+1])
            if current_path not in added_to_toc:
                depth = i
                indent = "  " * depth
                title = format_display_name(parts[i], is_oj=(i == 0))
                toc_content += f"{indent}* [📂 {title}](#-{create_slug(title)})\n"
                added_to_toc.add(current_path)
    
    folder_data = []
    for root, dirs, files in os.walk(root_dir):
        dirs[:] = sorted([d for d in dirs if d not in EXCLUDE_DIRS], key=natural_sort_key)
        cpp_files = [f for f in files if f.endswith('.cpp')]
        if cpp_files:
            folder_data.append((root, cpp_files))
    folder_data.sort(key=lambda x: natural_sort_key(x[0]))

    for path, files in folder_data:
        rel_path_from_sol = os.path.relpath(path, root_dir)
        if rel_path_from_sol == ".":
            main_content += f"## 📂 {root_dir}\n"
        else:
            base_name = os.path.basename(path)
            is_oj_folder = (os.path.dirname(rel_path_from_sol) == "")
            title = format_display_name(base_name, is_oj=is_oj_folder)
            
            # Logic: Tìm link OJ từ file config trong folder
            if is_oj_folder:
                oj_url = get_oj_link_from_file(path)
                if oj_url:
                    main_content += f"## 📂 [{title}]({oj_url})\n"
                else:
                    main_content += f"## 📂 {title}\n"
            else:
                main_content += f"### 📁 {title}\n"
                
        files.sort(key=natural_sort_key)
        table = "| # | Problem Name | Tags | Complexity | Date | Solution |\n| :--- | :--- | :--- | :--- | :--- | :--- |\n"
        for i, file in enumerate(files, 1):
            full_path = os.path.join(path, file)
            meta = extract_metadata(full_path)
            filename_no_ext = file.replace('.cpp', '')
            file_id = filename_no_ext.split('_')[0].upper() if '_' in filename_no_ext else filename_no_ext.upper()
            if meta["title"]:
                display_name = f"{file_id} - {meta['title']}"
            elif '_' in filename_no_ext:
                prob_name_parts = filename_no_ext.split('_')[1:]
                display_name = f"{file_id} - {' '.join(prob_name_parts).title()}"
            else:
                display_name = file_id
            prob_link = meta["source"] or auto_generate_link(full_path)
            name_md = f"[{display_name}]({prob_link})" if prob_link else display_name
            safe_path = full_path.replace('\\', '/').replace(' ', '%20')
            sol_md = f"[Code]({safe_path})"
            if meta["submission"]: sol_md += f" \\| [Sub]({meta['submission']})"
            table += f"| {i} | {name_md} | {meta['tags']} | {meta['complexity']} | {meta['date']} | {sol_md} |\n"
            total_problems += 1
        main_content += table + "\n"
        
    # Phần Stats và Badge giữ nguyên...
    push_time = get_last_commit_time()
    iso_string = push_time.strftime("%Y%m%dT%H%M")
    time_str = push_time.strftime("%b %d, %Y - %H:%M (GMT+7)")
    badge_time = (time_str.replace("-", "--").replace(" ", "_").replace(":", "%3A")
                          .replace(",", "%2C").replace("(", "%28").replace(")", "%29"))
    badge_url = f"https://img.shields.io/badge/Last_Update-{badge_time}-0078d4?style=for-the-badge&logo=github"
    time_link = f"https://www.timeanddate.com/worldclock/fixedtime.html?msg=Convert+to+your+timezone&iso={iso_string}&p1={CITY_ID}"
    stats = f"### 📊 Repository Stats\n\n- **Total Problems:** {total_problems}\n- **Origin Timezone:** Ho Chi Minh City (GMT+7)\n\n[![Last Update]({badge_url})]({time_link} \"🖱️ CLICK TO CONVERT\")\n\n---\n"
    with open(README_FILE, 'w', encoding='utf-8') as f:
        f.write(content + stats + toc_content + "\n---\n" + main_content)

if __name__ == "__main__":
    generate_readme()