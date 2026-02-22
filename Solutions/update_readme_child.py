import os
import re
from datetime import datetime, timedelta, timezone

# --- CONFIGURATION ---
# This script should be placed in the Solutions directory.
# It scans every sub-folder and creates a README for each.
BASE_DIR = os.path.dirname(os.path.abspath(__file__))

EXCLUDE_DIRS = {'.git', '.github', '.assets', 'venv', '__pycache__', '.cph'}
CITY_ID = 218 # Ho Chi Minh City

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

def format_display_name(name):
    """Keep the exact folder name as requested."""
    return name

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
    return None

def count_problems_in_subtree(directory):
    """Count unique problems in a specific directory tree."""
    problem_statuses = {} # {id: status}

    for root, dirs, files in os.walk(directory):
        dirs[:] = [d for d in dirs if d not in EXCLUDE_DIRS]
        for file in files:
            if file.endswith('.cpp'):
                full_path = os.path.join(root, file)
                meta = extract_metadata(full_path)
                prob_link = meta["source"] or auto_generate_link(full_path)
                prob_id = prob_link if prob_link else full_path
                
                status = meta["status"]
                if prob_id not in problem_statuses or STATUS_MAP[status]['prio'] > STATUS_MAP[problem_statuses[prob_id]]['prio']:
                    problem_statuses[prob_id] = status
    
    total = len(problem_statuses)
    ac = list(problem_statuses.values()).count("AC")
    return total, ac

def generate_single_readme(target_dir):
    """Generate README.md for a specific directory."""
    folder_name = os.path.basename(target_dir)
    if not folder_name: folder_name = "Solutions" 
    
    readme_path = os.path.join(target_dir, 'README.md')
    
    total_problems, total_ac = count_problems_in_subtree(target_dir)
    if total_problems == 0: return # Do not create README if no problems found

    content = f"# 📁 {format_display_name(folder_name)} Solutions\n\n"
    
    # --- STATS ---
    push_time = get_last_commit_time()
    time_str = push_time.strftime("%b %d, %Y - %H:%M (GMT+7)")
    badge_time = time_str.replace("-", "--").replace(" ", "_").replace(":", "%3A").replace(",", "%2C")
    
    badge_url = f"https://img.shields.io/badge/Last_Update-{badge_time}-0078d4?style=for-the-badge&logo=github"
    progress_badge = f"https://img.shields.io/badge/Progress-{total_ac}/{total_problems}-4c1?style=for-the-badge&logo=target"
    
    stats = f"### 📊 {format_display_name(folder_name)} Stats\n\n"
    stats += f"![Progress]({progress_badge}) ![Last Update]({badge_url})\n\n"
    stats += f"- **Total Unique Problems:** {total_problems}\n"
    stats += f"- **Solved (AC):** {total_ac}\n"
    stats += f"*Tips: Press `ctrl + f` on Windows or `cmd + f` on MacOS to search problem by ID or Name*\n---\n"
    
    # --- TOC & CONTENT ---
    toc_content = "## 📌 Table of Contents\n\n"
    main_tables = ""
    
    folder_data = []
    for root, dirs, files in os.walk(target_dir):
        dirs[:] = sorted([d for d in dirs if d not in EXCLUDE_DIRS], key=natural_sort_key)
        cpp_files = [f for f in files if f.endswith('.cpp')]
        if cpp_files:
            folder_data.append((root, cpp_files))
            
    folder_data.sort(key=lambda x: natural_sort_key(x[0]))
    
    for i, (path, files) in enumerate(folder_data):
        rel_path = os.path.relpath(path, target_dir)
        display_name = format_display_name(os.path.basename(path))
        
        this_folder_total, _ = count_problems_in_subtree(path)
        title_with_count = f"{display_name} ({this_folder_total})"
        
        # TOC indentation based on depth
        depth = 0 if rel_path == "." else rel_path.count(os.sep) + 1
        toc_content += f"{'  ' * depth}* [📁 {title_with_count}](#-{create_slug(title_with_count)})\n"
        
        # Header for Table
        if rel_path == ".":
            main_tables += f"## 📂 {title_with_count}\n"
        else:
            main_tables += f"{'#' * (depth + 2)} 📁 {title_with_count}\n"
            
        table = "| # | Problem Name | Tags | Complexity | Date | Solution | Status |\n| :--- | :--- | :--- | :--- | :--- | :--- | :--- |\n"
        files.sort(key=natural_sort_key)
        for idx, file in enumerate(files, 1):
            full_path = os.path.join(path, file)
            meta = extract_metadata(full_path)
            prob_link = meta["source"] or auto_generate_link(full_path)
            
            filename_no_ext = file.replace('.cpp', '')
            file_id = filename_no_ext.split('_')[0].upper() if '_' in filename_no_ext else filename_no_ext.upper()
            prob_title = f"{file_id} - {meta['title']}" if meta["title"] else format_display_name(filename_no_ext)
            
            name_md = f"[{prob_title}]({prob_link})" if prob_link else prob_title
            rel_code_path = os.path.relpath(full_path, target_dir).replace('\\', '/').replace(' ', '%20')
            sol_md = f"[Code]({rel_code_path})"
            if meta["submission"]: sol_md += f" \\| [Sub]({meta['submission']})"
            
            table += f"| {idx} | {name_md} | {meta['tags']} | {meta['complexity']} | {meta['date']} | {sol_md} | {get_status_badge(meta['status'])} |\n"
        
        main_tables += table + "\n"

    with open(readme_path, 'w', encoding='utf-8') as f:
        f.write(content + stats + toc_content + "\n---\n" + main_tables)
    print(f"Generated: {readme_path}")

def main():
    # Traverse all sub-directories in BASE_DIR
    for root, dirs, files in os.walk(BASE_DIR):
        dirs[:] = [d for d in dirs if d not in EXCLUDE_DIRS]
        generate_single_readme(root)

if __name__ == "__main__":
    main()