import os
import re
from datetime import datetime, timedelta, timezone

# Configuration: Script is now located inside the Solutions folder
EXCLUDE_DIRS = {'.git', '.github', '.assets', 'venv', '__pycache__', '.cph'}
README_FILE = 'README.md'
CITY_ID = 218 

STATUS_MAP = {
    "AC": {"full": "Accepted", "color": "4c1", "prio": 4},        
    "WA": {"full": "Wrong Answer", "color": "e05d44", "prio": 2},  
    "TLE": {"full": "Time Limit Exceeded", "color": "dfb317", "prio": 3}, 
    "WIP": {"full": "Work In Progress", "color": "007ec6", "prio": 1},     
    "PENDING": {"full": "Pending", "color": "9f9f9f", "prio": 0}   
}

def natural_sort_key(s):
    return [int(text) if text.isdigit() else text.lower()
            for text in re.split('([0-9]+)', s)]

def get_last_commit_time():
    tz_hcm = timezone(timedelta(hours=7))
    return datetime.now(tz=tz_hcm)

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
                    if ':' in clean_line:
                        key, val = [x.strip() for x in clean_line.split(':', 1)]
                        k = key.lower()
                        if k == "title": meta["title"] = val
                        elif k == "status":
                            v_up = val.upper()
                            if "IN PROGRESS" in v_up or "WIP" in v_up: meta["status"] = "WIP"
                            elif v_up in STATUS_MAP: meta["status"] = v_up
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
    except Exception: pass
    return meta

def get_status_badge(status_code):
    status_info = STATUS_MAP.get(status_code, STATUS_MAP["AC"])
    padded_msg = f"%20%20%20{status_code}%20%20%20"
    badge_url = f"https://img.shields.io/static/v1?label=&message={padded_msg}&color={status_info['color']}&style=for-the-badge"
    return f"![{status_code}]({badge_url})"

def generate_readme():
    # Header for the Solutions page
    header_text = "# 📚 Detailed Problem Solving Log\n\n"
    header_text += "[⬅️ Back to Home](../README.md)\n\n"
    header_text += "This page automatically aggregates all solved problems. Data is extracted directly from the headers of `.cpp` files.\n\n---\n"
    
    # root_dir is current directory (Solutions/)
    root_dir = "."
    unique_problems = {}
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
            sol_link = full_path.replace('./', '').replace('\\', '/').replace(' ', '%20')
            sol_md = f"[Code]({sol_link})"
            if meta["submission"]: sol_md += f" \\| [Sub]({meta['submission']})"
            
            table += f"| {i} | {name} | {meta['tags']} | {meta['complexity']} | {meta['date']} | {sol_md} | {get_status_badge(meta['status'])} |\n"
        main_content += table + "\n"

    total_problems = len(unique_problems)
    total_ac = list(unique_problems.values()).count("AC")
    
    badge_time = get_last_commit_time().strftime("%b_%d,_%Y")
    update_badge = f"https://img.shields.io/badge/Last_Update-{badge_time}-0078d4?style=for-the-badge&logo=github"
    progress_badge = f"https://img.shields.io/badge/Progress-{total_ac}/{total_problems}-4c1?style=for-the-badge&logo=target"
    
    stats = f"### 📊 Solving Stats\n\n![Progress]({progress_badge}) ![Last Update]({update_badge})\n\n"
    stats += f"- **Unique Problems:** {total_problems}\n- **Accepted:** {total_ac}\n\n"
    
    legend = "#### 💡 Quick Legend\n> " + " | ".join([f"**{k}**: {v['full']}" for k, v in STATUS_MAP.items()]) + "\n\n---\n"

    with open(README_FILE, 'w', encoding='utf-8') as f:
        f.write(header_text + stats + legend + toc_content + "\n---\n" + main_content)

if __name__ == "__main__":
    generate_readme()