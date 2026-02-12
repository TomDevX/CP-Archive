import os
import re
import subprocess
from datetime import datetime, timedelta, timezone

# --- CONFIGURATION ---
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
README_FILE = os.path.join(BASE_DIR, 'README.md')
# Thư mục gốc chứa các lời giải (mặc định là 'Solutions')
ROOT_SOLUTIONS = os.path.join(BASE_DIR, 'Solutions') if os.path.isdir(os.path.join(BASE_DIR, 'Solutions')) else BASE_DIR

EXCLUDE_DIRS = {'.git', '.github', '.assets', 'venv', '__pycache__', '.cph'}
CITY_ID = 218 

STATUS_MAP = {
    "AC": {"full": "Accepted", "color": "4c1", "prio": 4},        
    "WA": {"full": "Wrong Answer", "color": "e05d44", "prio": 2},  
    "TLE": {"full": "Time Limit Exceeded", "color": "dfb317", "prio": 3}, 
    "WIP": {"full": "Work In Progress", "color": "007ec6", "prio": 1},     
}

# --- HELPERS (RETAINED FROM YOUR CODE) ---
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
    if is_oj: return name.upper()
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
                    if lower_line.startswith("title:"):
                        meta["title"] = clean_line[6:].strip()
                    elif lower_line.startswith("status:"):
                        val = clean_line[7:].strip().upper()
                        meta["status"] = "WIP" if "WIP" in val else (val if val in STATUS_MAP else "AC")
                    elif lower_line.startswith("source:"):
                        match = re.search(r'(https?://[^\s]+)', clean_line)
                        if match: meta["source"] = match.group(1)
                    elif lower_line.startswith("tags:"):
                        val = clean_line[5:].strip()
                        if val: meta["tags"] = ", ".join([f"`{t.strip()}`" for t in val.split(',') if t.strip()])
                    elif lower_line.startswith("complexity:"):
                        val = clean_line[11:].strip()
                        if val: meta["complexity"] = f"$\\mathcal{{O}}({val.strip('Oo() ')})$"
    except Exception: pass
    return meta

def get_status_badge(status_code):
    status_info = STATUS_MAP.get(status_code, STATUS_MAP["AC"])
    badge_url = f"https://img.shields.io/static/v1?label=&message=%20%20%20{status_code}%20%20%20&color={status_info['color']}&style=for-the-badge"
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

# --- ORCHESTRATION LOGIC ---
def run_child_scripts():
    """Tự động tìm và chạy các file update_readme.py trong thư mục con."""
    for root, dirs, files in os.walk(ROOT_SOLUTIONS):
        if 'update_readme.py' in files:
            script_path = os.path.join(root, 'update_readme.py')
            if os.path.abspath(script_path) == os.path.abspath(__file__):
                continue
            try:
                subprocess.run(['python', 'update_readme.py'], cwd=root, check=True)
            except Exception: pass

def calculate_counts():
    """Tính toán số lượng bài tập (file .cpp) cộng dồn theo thư mục."""
    counts = {}
    for root, dirs, files in os.walk(ROOT_SOLUTIONS):
        dirs[:] = [d for d in dirs if d not in EXCLUDE_DIRS]
        cpp_count = len([f for f in files if f.endswith('.cpp')])
        counts[root] = cpp_count
    
    total_counts = counts.copy()
    for p in sorted(counts.keys(), key=lambda x: len(x.split(os.sep)), reverse=True):
        parent = os.path.dirname(p)
        if parent in total_counts:
            total_counts[parent] += total_counts[p]
    return total_counts

def generate_readme():
    run_child_scripts()
    counts = calculate_counts()
    
    content = "# 🏆 Competitive Programming Repository\n\n"
    unique_problems = {}
    main_content = ""
    toc_content = "## 📌 Table of Contents\n\n"
    folder_data = []
    added_to_toc = set()

    for root, dirs, files in os.walk(ROOT_SOLUTIONS):
        dirs[:] = sorted([d for d in dirs if d not in EXCLUDE_DIRS], key=natural_sort_key)
        rel_path = os.path.relpath(root, ROOT_SOLUTIONS)
        
        if rel_path != ".":
            parts = rel_path.split(os.sep)
            for i in range(len(parts)):
                current_path = os.path.join(ROOT_SOLUTIONS, *parts[:i+1])
                if current_path not in added_to_toc:
                    depth = i
                    indent = "  " * depth
                    title = format_display_name(parts[i], is_oj=(i == 0))
                    count = counts.get(current_path, 0)
                    toc_content += f"{indent}* [📂 {title}](#-{create_slug(title)}) `{count} bài` \n"
                    added_to_toc.add(current_path)

        cpp_files = [f for f in files if f.endswith('.cpp')]
        if cpp_files:
            folder_data.append((root, cpp_files))

    folder_data.sort(key=lambda x: natural_sort_key(x[0]))

    for path, files in folder_data:
        rel_path_from_sol = os.path.relpath(path, ROOT_SOLUTIONS)
        base_name = os.path.basename(path)
        is_oj_folder = (os.path.dirname(rel_path_from_sol) == "")
        title = format_display_name(base_name, is_oj=is_oj_folder)
        count = counts.get(path, 0)
        
        if is_oj_folder:
            oj_url = get_oj_link_from_file(path)
            main_content += f"## 📂 [{title} ({count} bài)]({oj_url})\n" if oj_url else f"## 📂 {title} ({count} bài)\n"
        else:
            main_content += f"### 📁 {title} ({count} bài)\n"
        
        files.sort(key=natural_sort_key)
        table = "| # | Problem Name | Tags | Complexity | Solution | Status |\n| :--- | :--- | :--- | :--- | :--- | :--- |\n"
        
        for i, file in enumerate(files, 1):
            full_path = os.path.join(path, file)
            meta = extract_metadata(full_path)
            
            prob_id = meta["source"] if meta["source"] else full_path
            if prob_id not in unique_problems or STATUS_MAP[meta["status"]]['prio'] > STATUS_MAP[unique_problems[prob_id]]['prio']:
                unique_problems[prob_id] = meta["status"]
            
            filename_no_ext = file.replace('.cpp', '')
            display_name = meta["title"] if meta["title"] else format_display_name(filename_no_ext)
            prob_link = meta["source"] or auto_generate_link(full_path)
            
            rel_sol_path = os.path.relpath(full_path, BASE_DIR).replace('\\', '/').replace(' ', '%20')
            table += f"| {i} | [{display_name}]({prob_link or '#'}) | {meta['tags']} | {meta['complexity']} | [Code]({rel_sol_path}) | {get_status_badge(meta['status'])} |\n"
        main_content += table + "\n"
        
    # --- STATS SECTION ---
    total_problems = len(unique_problems)
    total_ac = list(unique_problems.values()).count("AC")
    
    push_time = get_last_commit_time()
    iso_string = push_time.strftime("%Y%m%dT%H%M")
    time_str = push_time.strftime("%b %d, %Y - %H:%M (GMT+7)")
    badge_time = (time_str.replace("-", "--").replace(" ", "_").replace(":", "%3A")
                          .replace(",", "%2C").replace("(", "%28").replace(")", "%29"))
    
    badge_url = f"https://img.shields.io/badge/Last_Update-{badge_time}-0078d4?style=for-the-badge&logo=github"
    time_link = f"https://www.timeanddate.com/worldclock/fixedtime.html?msg=Convert+to+your+timezone&iso={iso_string}&p1={CITY_ID}"
    progress_badge = f"https://img.shields.io/badge/Progress-{total_ac}/{total_problems}-4c1?style=for-the-badge&logo=target"
    
    stats = f"### 📊 Repository Stats\n\n![Progress]({progress_badge}) [![Last Update]({badge_url})]({time_link})\n\n"
    stats += f"- **Total Problems:** {total_problems}\n"
    stats += f"- **Accepted:** {total_ac}\n\n---\n"
    
    with open(README_FILE, 'w', encoding='utf-8') as f:
        f.write(content + stats + toc_content + "\n---\n" + main_content)
    print("🏆 Master README updated successfully!")

if __name__ == "__main__":
    generate_readme()