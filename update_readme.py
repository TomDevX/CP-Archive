import os
import re
import subprocess
from datetime import datetime, timedelta, timezone

# Danh sách loại trừ mặc định (ngoài .gitignore)
EXCLUDE_DIRS = {'.git', '.github', '.assets', 'venv', '__pycache__'}
README_FILE = 'README.md'
HEADER_FILE = 'HEADER.md'
CITY_ID = 218 

# Cấu hình màu sắc chuẩn
STATUS_MAP = {
    "AC": {"full": "Accepted", "color": "4c1"},        
    "WA": {"full": "Wrong Answer", "color": "e05d44"},  
    "TLE": {"full": "Time Limit Exceeded", "color": "dfb317"}, 
    "WIP": {"full": "Work In Progress", "color": "007ec6"},     
    "PENDING": {"full": "Pending", "color": "9f9f9f"}   
}

def load_gitignore():
    """Tự động đọc các thư mục từ .gitignore để thêm vào danh sách loại trừ."""
    excludes = set()
    if os.path.exists('.gitignore'):
        with open('.gitignore', 'r', encoding='utf-8') as f:
            for line in f:
                line = line.strip()
                # Bỏ qua dòng trống, comment hoặc file cụ thể (chỉ tập trung folder)
                if line and not line.startswith('#'):
                    # Loại bỏ dấu / ở đầu hoặc cuối để khớp với os.walk
                    clean_path = line.rstrip('/').lstrip('/')
                    excludes.add(clean_path)
    return excludes

# Cập nhật danh sách loại trừ từ .gitignore
EXCLUDE_DIRS.update(load_gitignore())

def natural_sort_key(s):
    return [int(text) if text.isdigit() else text.lower()
            for text in re.split('([0-9]+)', s)]

def get_last_commit_time():
    tz_hcm = timezone(timedelta(hours=7))
    return datetime.now(tz=tz_hcm)

def get_oj_link_from_file(folder_path):
    link_files = ['link.txt', 'oj.txt', 'source.url']
    for file_name in link_files:
        file_path = os.path.join(folder_path, file_name)
        if os.path.exists(file_path):
            try:
                with open(file_path, 'r', encoding='utf-8') as f:
                    content = f.read().strip()
                    if file_name.endswith('.url'):
                        match = re.search(r'URL=(https?://[^\s]+)', content)
                        if match: return match.group(1)
                    if content.startswith('http'):
                        return content.split('\n')[0].strip()
            except Exception: pass
    return None

def format_display_name(name, is_oj=False):
    if not name: return ""
    if is_oj: return name
    parts = name.split('_')
    if parts[0].isdigit(): parts = parts[1:]
    return " ".join(parts).replace('-', ' ').title()

def create_slug(text):
    slug = text.lower().replace(" ", "-")
    slug = re.sub(r'[^\w\-]', '', slug)
    return slug

def extract_metadata(file_path):
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
                    lower_line = clean_line.lower()
                    
                    # Sử dụng split để bóc tách key: value chính xác hơn
                    if ':' in clean_line:
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
    status_info = STATUS_MAP.get(status_code, STATUS_MAP["AC"])
    msg = status_info["full"].replace(" ", "%20")
    color = status_info["color"]
    # Style 'for-the-badge' giúp lấp đầy cell như bạn mong muốn
    url = f"https://img.shields.io/static/v1?label=&message={msg}&color={color}&style=for-the-badge"
    return f"![{status_info['full']}]({url})"

def generate_readme():
    header_content = ""
    if os.path.exists(HEADER_FILE):
        with open(HEADER_FILE, 'r', encoding='utf-8') as f:
            header_content = f.read() + "\n\n---\n"
    else:
        header_content = "# 🏆 Competitive Programming Repository\n\n"
    
    total_problems, total_ac = 0, 0
    main_content = ""
    toc_content = "## 📌 Table of Contents\n\n"
    root_dir = "Solutions"
    if not os.path.isdir(root_dir): return

    added_to_toc = set()
    folder_data = []
    for root, dirs, files in os.walk(root_dir):
        # Lọc folder dựa trên EXCLUDE_DIRS (bao gồm cả dữ liệu từ .gitignore)
        dirs[:] = sorted([d for d in dirs if d not in EXCLUDE_DIRS], key=natural_sort_key)
        cpp_files = [f for f in files if f.endswith('.cpp')]
        if cpp_files:
            folder_data.append((root, cpp_files))
    
    folder_data.sort(key=lambda x: natural_sort_key(x[0]))

    for path, files in folder_data:
        rel_path = os.path.relpath(path, root_dir)
        is_oj = (os.path.dirname(rel_path) == "")
        title = format_display_name(os.path.basename(path), is_oj=is_oj)
        
        # Thêm vào Table of Contents
        depth = 0 if is_oj else 1
        indent = "  " * depth
        if path not in added_to_toc:
            toc_content += f"{indent}* [📂 {title}](#-{create_slug(title)})\n"
            added_to_toc.add(path)

        main_content += f"## 📂 {title}\n" if is_oj else f"### 📁 {title}\n"
        
        files.sort(key=natural_sort_key)
        table = "| # | Problem Name | Tags | Complexity | Date | Solution | Status |\n| :--- | :--- | :--- | :--- | :--- | :--- | :--- |\n"
        for i, file in enumerate(files, 1):
            meta = extract_metadata(os.path.join(path, file))
            if meta["status"] == "AC": total_ac += 1
            
            name_link = f"[{meta['title'] or file}]({meta['source']})" if meta['source'] else (meta['title'] or file)
            sol_link = f"[Code]({os.path.join(path, file).replace(' ', '%20')})"
            if meta["submission"]: sol_link += f" \\| [Sub]({meta['submission']})"
            
            table += f"| {i} | {name_link} | {meta['tags']} | {meta['complexity']} | {meta['date']} | {sol_link} | {get_status_badge(meta['status'])} |\n"
            total_problems += 1
        main_content += table + "\n"

    # Repository Stats
    push_time = get_last_commit_time()
    badge_time = push_time.strftime("%b_%d,_%Y").replace(" ", "_")
    update_badge = f"https://img.shields.io/badge/Last_Update-{badge_time}-0078d4?style=for-the-badge&logo=github"
    progress_badge = f"https://img.shields.io/badge/Progress-{total_ac}/{total_problems}-4c1?style=for-the-badge&logo=target"
    
    stats = f"### 📊 Repository Stats\n\n![Progress]({progress_badge}) ![Last Update]({update_badge})\n\n"
    stats += f"- **Total Problems:** {total_problems}\n- **Accepted:** {total_ac}\n\n---\n"

    with open(README_FILE, 'w', encoding='utf-8') as f:
        f.write(header_content + stats + toc_content + "\n---\n" + main_content)

if __name__ == "__main__":
    generate_readme()