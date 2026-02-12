import os
import re
from datetime import datetime, timedelta, timezone

# --- CONFIGURATION ---
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
README_FILE = os.path.join(BASE_DIR, 'README.md')
# Duyệt từ thư mục Solutions hoặc thư mục hiện tại
root_dir = os.path.join(BASE_DIR, 'Solutions') if os.path.isdir(os.path.join(BASE_DIR, 'Solutions')) else BASE_DIR

EXCLUDE_DIRS = {'.git', '.github', '.assets', 'venv', '__pycache__', '.cph'}
CITY_ID = 218 

# Labels cũ & Priority để xử lý trùng bài
STATUS_MAP = {
    "AC": {"full": "Accepted", "color": "4c1", "prio": 4},        
    "WA": {"full": "Wrong Answer", "color": "e05d44", "prio": 2},  
    "TLE": {"full": "Time Limit Exceeded", "color": "dfb317", "prio": 3}, 
    "WIP": {"full": "Work In Progress", "color": "007ec6", "prio": 1},     
}

# --- HELPERS ---
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
    # Xử lý chuỗi đã bỏ extension
    parts = name.split('_')
    if parts[0].isdigit(): parts = parts[1:]
    return " ".join(parts).replace('-', ' ').title()

def create_slug(text):
    """Tạo slug chuẩn GitHub để link nội bộ hoạt động."""
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
                    elif lower_line.startswith("status:"):
                        val = clean_line[7:].strip().upper()
                        if "IN PROGRESS" in val or "WIP" in val: meta["status"] = "WIP"
                        elif val in STATUS_MAP: meta["status"] = val
                    elif lower_line.startswith("source:"):
                        match = re.search(r'(https?://[^\s]+)', clean_line)
                        if match: meta["source"] = match.group(1)
                    elif lower_line.startswith("created:"):
                        val = clean_line[8:].strip()
                        if val:
                            try:
                                dt = datetime.strptime(val.split(' ')[0], "%Y-%m-%d")
                                day = dt.strftime("%d").lstrip("0")
                                meta["date"] = dt.strftime(f"%b {day}, %Y")
                            except: meta["date"] = val
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

def get_status_badge(status_code):
    status_info = STATUS_MAP.get(status_code, STATUS_MAP["AC"])
    padded_msg = f"%20%20%20{status_code}%20%20%20"
    badge_url = f"https://img.shields.io/static/v1?label=&message={padded_msg}&color={status_info['color']}&style=for-the-badge"
    return f"![{status_code}]({badge_url})"

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

def count_problems_recursive(directory):
    """Đếm số file .cpp trong thư mục và các thư mục con."""
    counts = {}
    for root, dirs, files in os.walk(directory):
        # Loại bỏ các thư mục không mong muốn để tránh đếm sai
        dirs[:] = [d for d in dirs if d not in EXCLUDE_DIRS]
        
        cpp_count = len([f for f in files if f.endswith('.cpp')])
        
        # Cộng dồn cho thư mục hiện tại và tất cả các thư mục cha cho đến root_dir
        curr = root
        while True:
            counts[curr] = counts.get(curr, 0) + cpp_count
            if curr == directory:
                break
            curr = os.path.dirname(curr)
    return counts

def generate_readme():
    content = "# 🏆 Competitive Programming Repository\n\n"
    
    unique_problems = {}
    main_content = ""
    toc_content = "## 📌 Table of Contents\n\n"
    
    if not os.path.isdir(root_dir):
        return

    # Bước 1: Đếm số lượng bài tập trước
    folder_counts = count_problems_recursive(root_dir)

    # Bước 2: Duyệt, lọc và tạo nội dung
    folder_data = []
    added_to_toc = set()

    for root, dirs, files in os.walk(root_dir):
        dirs[:] = sorted([d for d in dirs if d not in EXCLUDE_DIRS], key=natural_sort_key)
        rel_path = os.path.relpath(root, root_dir)
        
        if rel_path != ".":
            parts = rel_path.split(os.sep)
            for i in range(len(parts)):
                current_path = os.path.join(root_dir, *parts[:i+1])
                if current_path not in added_to_toc:
                    depth = i
                    indent = "  " * depth
                    raw_title = parts[i]
                    display_title = format_display_name(raw_title, is_oj=(i == 0))
                    
                    # Lấy số lượng bài tập từ folder_counts
                    count = folder_counts.get(current_path, 0)
                    title_with_count = f"{display_title} ({count})"
                    
                    # Quan trọng: Link phải trỏ đến slug chứa cả số lượng bài tập
                    toc_content += f"{indent}* [📂 {title_with_count}](#-{create_slug(title_with_count)})\n"
                    added_to_toc.add(current_path)

        cpp_files = [f for f in files if f.endswith('.cpp')]
        if cpp_files:
            folder_data.append((root, cpp_files))

    folder_data.sort(key=lambda x: natural_sort_key(x[0]))

    for path, files in folder_data:
        rel_path_from_sol = os.path.relpath(path, root_dir)
        base_name = os.path.basename(path)
        is_oj_folder = (os.path.dirname(rel_path_from_sol) == "")
        title = format_display_name(base_name, is_oj=is_oj_folder)
        
        # Lấy count cho folder hiện tại
        count = folder_counts.get(path, 0)
        title_with_count = f"{title} ({count})"
        
        if is_oj_folder:
            oj_url = get_oj_link_from_file(path)
            # Thêm count vào header ##
            main_content += f"## 📂 [{title_with_count}]({oj_url})\n" if oj_url else f"## 📂 {title_with_count}\n"
        else:
            # Thêm count vào header ###
            main_content += f"### 📁 {title_with_count}\n"
        
        files.sort(key=natural_sort_key)
        table = "| # | Problem Name | Tags | Complexity | Date | Solution | Status |\n| :--- | :--- | :--- | :--- | :--- | :--- | :--- |\n"
        
        for i, file in enumerate(files, 1):
            full_path = os.path.join(path, file)
            meta = extract_metadata(full_path)
            
            prob_id = meta["source"] if meta["source"] else full_path
            current_status = meta["status"]
            if prob_id not in unique_problems or STATUS_MAP[current_status]['prio'] > STATUS_MAP[unique_problems[prob_id]]['prio']:
                unique_problems[prob_id] = current_status
            
            filename_no_ext = file.replace('.cpp', '')
            file_id = filename_no_ext.split('_')[0].upper() if '_' in filename_no_ext else filename_no_ext.upper()
            
            if meta["title"]:
                display_name = f"{file_id} - {meta['title']}"
            else:
                display_name = format_display_name(filename_no_ext) 
            
            prob_link = meta["source"] or auto_generate_link(full_path)
            name_md = f"[{display_name}]({prob_link})" if prob_link else display_name
            
            rel_sol_path = os.path.relpath(full_path, BASE_DIR).replace('\\', '/').replace(' ', '%20')
            sol_md = f"[Code]({rel_sol_path})"
            if meta["submission"]: sol_md += f" \\| [Sub]({meta['submission']})"
            
            table += f"| {i} | {name_md} | {meta['tags']} | {meta['complexity']} | {meta['date']} | {sol_md} | {get_status_badge(meta['status'])} |\n"
                
        main_content += table + "\n"
        
    # --- STATS SECTION ---
    total_problems_count = len(unique_problems)
    total_ac = list(unique_problems.values()).count("AC")
    
    push_time = get_last_commit_time()
    iso_string = push_time.strftime("%Y%m%dT%H%M")
    time_str = push_time.strftime("%b %d, %Y - %H:%M (GMT+7)")
    badge_time = (time_str.replace("-", "--").replace(" ", "_").replace(":", "%3A")
                          .replace(",", "%2C").replace("(", "%28").replace(")", "%29"))
    
    badge_url = f"https://img.shields.io/badge/Last_Update-{badge_time}-0078d4?style=for-the-badge&logo=github"
    time_link = f"https://www.timeanddate.com/worldclock/fixedtime.html?msg=Convert+to+your+timezone&iso={iso_string}&p1={CITY_ID}"
    progress_badge = f"https://img.shields.io/badge/Progress-{total_ac}/{total_problems_count}-4c1?style=for-the-badge&logo=target"
    
    stats = f"### 📊 Repository Stats\n\n"
    stats += f"![Progress]({progress_badge}) [![Last Update]({badge_url})]({time_link} \"🖱️ CLICK TO CONVERT\")\n\n"
    stats += f"- **Total Problems:** {total_problems_count}\n"
    stats += f"- **Accepted:** {total_ac}\n"
    stats += f"- **Origin Timezone:** Ho Chi Minh City (GMT+7)\n\n---\n"
    
    with open(README_FILE, 'w', encoding='utf-8') as f:
        f.write(content + stats + toc_content + "\n---\n" + main_content)

if __name__ == "__main__":
    generate_readme()