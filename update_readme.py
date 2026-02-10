import os
import re
from datetime import datetime, timedelta, timezone

# 1. Cấu hình loại trừ và file hệ thống
EXCLUDE_DIRS = {'.git', '.github', '.assets', 'venv', '__pycache__', '.cph'}
README_FILE = 'README.md'
HEADER_FILE = 'HEADER.md'
CITY_ID = 218 

# 2. Cấu hình màu sắc Status (Label rỗng)
STATUS_MAP = {
    "AC": {"full": "Accepted", "color": "4c1"},        
    "WA": {"full": "Wrong Answer", "color": "e05d44"},  
    "TLE": {"full": "Time Limit Exceeded", "color": "dfb317"}, 
    "WIP": {"full": "Work In Progress", "color": "007ec6"},     
    "PENDING": {"full": "Pending", "color": "9f9f9f"}   
}

def natural_sort_key(s):
    return [int(text) if text.isdigit() else text.lower()
            for text in re.split('([0-9]+)', s)]

def get_last_commit_time():
    tz_hcm = timezone(timedelta(hours=7))
    return datetime.now(tz=tz_hcm)

def extract_metadata(file_path):
    # Mặc định status là AC
    meta = {"source": None, "submission": None, "tags": "N/A", "complexity": "N/A", "title": None, "date": "N/A", "status": "AC"}
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            in_header = False
            for line in f:
                line_strip = line.strip()
                if line_strip.startswith("/**"):
                    in_header = True; continue
                if "**/ " in line_strip or line_strip.endswith("**/"):
                    break
                if in_header:
                    clean_line = line_strip.lstrip('*').strip()
                    if ':' in clean_line:
                        # Tách key và val, hỗ trợ căn lề nhiều khoảng trắng
                        key, val = [x.strip() for x in clean_line.split(':', 1)]
                        k = key.lower()
                        if k == "title": meta["title"] = val
                        elif k == "status":
                            v_up = val.upper()
                            meta["status"] = "WIP" if ("WIP" in v_up or "PROGRESS" in v_up) else v_up
                        elif k == "source": meta["source"] = val
                        elif k == "submission": meta["submission"] = val
                        elif k == "tags":
                            tags = [f"`{t.strip()}`" for t in val.split(',') if t.strip()]
                            meta["tags"] = ", ".join(tags)
                        elif k == "complexity":
                            if any(p in val for p in ["\\mathcal", "\\Theta"]): meta["complexity"] = f"${val}$"
                            else:
                                inner = re.sub(r'^[Oo]\s*\((.*)\)$', r'\1', val).strip()
                                meta["complexity"] = f"$\\mathcal{{O}}({inner})$"
                        elif k == "created":
                            try:
                                dt = datetime.strptime(val.split(' ')[0], "%Y-%m-%d")
                                meta["date"] = dt.strftime(f"%b {dt.day}, %Y")
                            except: meta["date"] = val.split(' ')[0]
    except: pass
    return meta

def get_status_badge(status_code):
    info = STATUS_MAP.get(status_code, STATUS_MAP["AC"])
    msg = info["full"].replace(" ", "%20")
    # URL style không label để chỉ hiện màu
    url = f"https://img.shields.io/static/v1?label=&message={msg}&color={info['color']}&style=flat-square"
    return f"![{info['full']}]({url})"

def generate_readme():
    header_text = ""
    if os.path.exists(HEADER_FILE):
        with open(HEADER_FILE, 'r', encoding='utf-8') as f:
            header_text = f.read() + "\n\n---\n"
    
    total_problems, total_ac = 0, 0
    main_content = ""
    root_dir = "Solutions"
    if not os.path.isdir(root_dir): return

    folder_data = []
    for root, dirs, files in os.walk(root_dir):
        # Loại bỏ folder rác .cph ngay tại đây
        dirs[:] = sorted([d for d in dirs if d not in EXCLUDE_DIRS], key=natural_sort_key)
        cpp_files = [f for f in files if f.endswith('.cpp')]
        if cpp_files: folder_data.append((root, cpp_files))
    
    folder_data.sort(key=lambda x: natural_sort_key(x[0]))

    for path, files in folder_data:
        rel_path = os.path.relpath(path, root_dir)
        is_oj = (os.path.dirname(rel_path) == "")
        folder_name = os.path.basename(path).replace('_', ' ').title()
        
        main_content += f"## 📂 {folder_name}\n" if is_oj else f"### 📁 {folder_name}\n"
        
        files.sort(key=natural_sort_key)
        table = "| # | Problem Name | Tags | Complexity | Date | Solution | Status |\n| :--- | :--- | :--- | :--- | :--- | :--- | :--- |\n"
        for i, file in enumerate(files, 1):
            meta = extract_metadata(os.path.join(path, file))
            if meta["status"] == "AC": total_ac += 1
            
            name = f"[{meta['title'] or file}]({meta['source']})" if meta['source'] else (meta['title'] or file)
            sol = f"[Code]({os.path.join(path, file).replace(' ', '%20')})"
            if meta["submission"]: sol += f" \\| [Sub]({meta['submission']})"
            
            table += f"| {i} | {name} | {meta['tags']} | {meta['complexity']} | {meta['date']} | {sol} | {get_status_badge(meta['status'])} |\n"
            total_problems += 1
        main_content += table + "\n"

    # Repository Stats với Progress Badge
    push_time = get_last_commit_time()
    badge_time = push_time.strftime("%b_%d,_%Y").replace(" ", "_")
    update_badge = f"https://img.shields.io/badge/Last_Update-{badge_time}-0078d4?style=for-the-badge&logo=github"
    progress_badge = f"https://img.shields.io/badge/Progress-{total_ac}/{total_problems}-4c1?style=for-the-badge&logo=target"
    
    stats = f"### 📊 Repository Stats\n\n![Progress]({progress_badge}) ![Last Update]({update_badge})\n\n"
    stats += f"- **Total Problems:** {total_problems}\n- **Accepted:** {total_ac}\n\n---\n"

    with open(README_FILE, 'w', encoding='utf-8') as f:
        f.write(header_text + stats + main_content)

if __name__ == "__main__":
    generate_readme()