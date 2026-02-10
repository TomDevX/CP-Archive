import os
import re
import subprocess
from datetime import datetime, timedelta, timezone

# Script resides inside Solutions/, so we ignore itself and standard rác folders
EXCLUDE_DIRS = {'.git', '.github', '.assets', 'venv', '__pycache__', '.cph'}
README_FILE = 'README.md'
CITY_ID = 218

# Configuration with Priority and English Labels
# Priority: AC (4) > TLE (3) > WA (2) > WIP (1)
STATUS_MAP = {
    "AC": {"full": "Accepted", "color": "4c1", "prio": 4},        
    "WA": {"full": "Wrong Answer", "color": "e05d44", "prio": 2},  
    "TLE": {"full": "Time Limit Exceeded", "color": "dfb317", "prio": 3}, 
    "WIP": {"full": "Work In Progress", "color": "007ec6", "prio": 1}
}

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
    # Preserving your exact header parsing logic
    meta = {"source": None, "submission": None, "tags": "N/A", "complexity": "N/A", "title": None, "date": "N/A", "status": "AC"}
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
                    elif lower_line.startswith("status:"):
                        val = clean_line[7:].strip().upper()
                        if "IN PROGRESS" in val or "WIP" in val:
                            meta["status"] = "WIP"
                        elif val in STATUS_MAP:
                            meta["status"] = val
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

def get_status_badge(status_code):
    # Using short code (AC/WA) with padding to fill the cell [cite: 2026-01-04]
    status_info = STATUS_MAP.get(status_code, STATUS_MAP["AC"])
    color = status_info["color"]
    padded_msg = f"%20%20%20{status_code}%20%20%20"
    badge_url = f"https://img.shields.io/static/v1?label=&message={padded_msg}&color={color}&style=for-the-badge"
    return f"![{status_code}]({badge_url})"

def generate_readme():
    header_text = "# 📚 Detailed Problem Solving Log\n\n"
    header_text += "[⬅️ Back to Home](../README.md)\n\n"
    header_text += "This log aggregates all solutions categorized by platform. Duplicates are counted only once in stats.\n\n---\n"
    
    # root_dir is current directory (.) because script is inside Solutions/
    root_dir = "."
    unique_problems = {} # Used for deduplication and best-status tracking
    main_content = ""
    toc_content = "## 📌 Table of Contents\n\n"

    folder_data = []
    for root, dirs, files in os.walk(root_dir):
        dirs[:] = sorted([d for d in dirs if d not in EXCLUDE_DIRS], key=natural_sort_key)
        cpp_files = [f for f in files if f.endswith('.cpp')]
        if cpp_files:
            folder_data.append((root, cpp_files))
    folder_data.sort(key=lambda x: natural_sort_key(x[0]))

    added_to_toc = set()
    for path, files in folder_data:
        rel_path = os.path.relpath(path, root_dir)
        if rel_path == ".": continue
        
        folder_name = os.path.basename(path).replace('_', ' ').title()
        is_oj = (os.path.dirname(rel_path) == "")
        
        if path not in added_to_toc:
            indent = "" if is_oj else "  "
            toc_content += f"{indent}* [📂 {folder_name}](#-{folder_name.lower().replace(' ', '-')})\n"
            added_to_toc.add(path)

        main_content += f"## 📂 {folder_name}\n" if is_oj else f"### 📁 {folder_name}\n"
        
        files.sort(key=natural_sort_key)
        table = "| # | Problem | Tags | Complexity | Date | Solution | Status |\n| :--- | :--- | :--- | :--- | :--- | :--- | :--- |\n"
        for i, file in enumerate(files, 1):
            full_path = os.path.join(path, file)
            meta = extract_metadata(full_path)
            
            # Logic: Track the best status for each unique problem [cite: 2026-01-15, 2026-01-04]
            prob_id = meta["source"] if meta["source"] else full_path
            current_status = meta["status"]
            
            if prob_id not in unique_problems:
                unique_problems[prob_id] = current_status
            else:
                new_prio = STATUS_MAP.get(current_status, {}).get("prio", 0)
                old_prio = STATUS_MAP.get(unique_problems[prob_id], {}).get("prio", 0)
                if new_prio > old_prio:
                    unique_problems[prob_id] = current_status
            
            name = meta['title'] or file
            # Relative path from Solutions/README.md
            sol_link = full_path.replace('./', '').replace('\\', '/').replace(' ', '%20')
            sol_md = f"[Code]({sol_link})"
            if meta["submission"]: sol_md += f" \\| [Sub]({meta['submission']})"
            
            table += f"| {i} | {name} | {meta['tags']} | {meta['complexity']} | {meta['date']} | {sol_md} | {get_status_badge(meta['status'])} |\n"
        main_content += table + "\n"

    # Statistics based on unique problems
    total_problems = len(unique_problems)
    total_ac = list(unique_problems.values()).count("AC")
    
    badge_time = get_last_commit_time().strftime("%b_%d,_%Y")
    update_badge = f"https://img.shields.io/badge/Last_Update-{badge_time}-0078d4?style=for-the-badge&logo=github"
    progress_badge = f"https://img.shields.io/badge/Progress-{total_ac}/{total_problems}-4c1?style=for-the-badge&logo=target"
    
    stats = f"### 📊 Solving Stats\n\n![Progress]({progress_badge}) ![Last Update]({update_badge})\n\n"
    stats += f"- **Unique Problems Solved:** {total_problems}\n- **Accepted (Best Effort):** {total_ac}\n\n"
    
    legend = "#### 💡 Quick Legend\n> " + " | ".join([f"**{k}**: {v['full']}" for k, v in STATUS_MAP.items()]) + "\n\n---\n"

    with open(README_FILE, 'w', encoding='utf-8') as f:
        f.write(header_text + stats + legend + toc_content + "\n---\n" + main_content)

if __name__ == "__main__":
    generate_readme()