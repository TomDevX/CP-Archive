import os
import re
from datetime import datetime

# --- CONFIGURATION (LOCAL) ---
CURRENT_DIR = os.path.dirname(os.path.abspath(__file__))
README_FILE = os.path.join(CURRENT_DIR, 'README.md')

STATUS_MAP = {
    "AC": {"full": "Accepted", "color": "4c1", "prio": 4},        
    "WA": {"full": "Wrong Answer", "color": "e05d44", "prio": 2},  
    "TLE": {"full": "Time Limit Exceeded", "color": "dfb317", "prio": 3}, 
    "WIP": {"full": "Work In Progress", "color": "007ec6", "prio": 1},     
}

# --- HELPERS (Bản sao từ Master để đảm bảo format đồng nhất) ---
def natural_sort_key(s):
    return [int(text) if text.isdigit() else text.lower() for text in re.split('([0-9]+)', s)]

def format_display_name(name, is_oj=False):
    if not name: return ""
    parts = name.split('_')
    if parts[0].isdigit(): parts = parts[1:]
    return " ".join(parts).replace('-', ' ').title()

def extract_metadata(file_path):
    meta = {"source": None, "submission": None, "tags": "N/A", "complexity": "N/A", "title": None, "date": "N/A", "status": "AC"}
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            in_header = False
            for line in f:
                line_strip = line.strip()
                if line_strip.startswith("/**"): in_header = True; continue
                if "**/ " in line_strip or line_strip.endswith("**/"): break
                if in_header:
                    clean_line = line_strip.lstrip('*').strip()
                    lower_line = clean_line.lower()
                    if lower_line.startswith("title:"): meta["title"] = clean_line[6:].strip()
                    elif lower_line.startswith("status:"):
                        val = clean_line[7:].strip().upper()
                        meta["status"] = "WIP" if ("WIP" in val or "IN PROGRESS" in val) else (val if val in STATUS_MAP else "AC")
                    elif lower_line.startswith("source:"):
                        match = re.search(r'(https?://[^\s]+)', clean_line)
                        if match: meta["source"] = match.group(1)
                    elif lower_line.startswith("tags:"):
                        val = clean_line[5:].strip()
                        if val: meta["tags"] = ", ".join([f"`{t.strip()}`" for t in val.split(',')])
                    elif lower_line.startswith("complexity:"):
                        val = clean_line[11:].strip()
                        if val: meta["complexity"] = f"${val}$" if "\\" in val else f"$\\mathcal{{O}}({val.strip('Oo() ')})$"
    except: pass
    return meta

def get_status_badge(status_code):
    info = STATUS_MAP.get(status_code, STATUS_MAP["AC"])
    return f"![{status_code}](https://img.shields.io/static/v1?label=&message=%20%20%20{status_code}%20%20%20&color={info['color']}&style=for-the-badge)"

def generate_local_readme():
    oj_name = os.path.basename(CURRENT_DIR).upper()
    content = f"# 📂 {oj_name} Solutions\n\n"
    
    # Quét tất cả file .cpp trong thư mục này (không quét đệ quy để tránh lộn xộn)
    files = sorted([f for f in os.listdir(CURRENT_DIR) if f.endswith('.cpp')], key=natural_sort_key)
    
    if not files: return

    # Thống kê nhanh cho thư mục này
    total = len(files)
    ac_count = 0
    
    table = "| # | Problem Name | Tags | Complexity | Date | Solution | Status |\n| :--- | :--- | :--- | :--- | :--- | :--- | :--- |\n"
    
    for i, file in enumerate(files, 1):
        full_path = os.path.join(CURRENT_DIR, file)
        meta = extract_metadata(full_path)
        if meta["status"] == "AC": ac_count += 1
        
        filename_no_ext = file.replace('.cpp', '')
        display_name = f"{filename_no_ext.split('_')[0].upper()} - {meta['title']}" if meta["title"] else format_display_name(filename_no_ext)
        
        name_md = f"[{display_name}]({meta['source']})" if meta["source"] else display_name
        sol_md = f"[Code]({file})"
        if meta["submission"]: sol_md += f" \\| [Sub]({meta['submission']})"
        
        table += f"| {i} | {name_md} | {meta['tags']} | {meta['complexity']} | {meta['date']} | {sol_md} | {get_status_badge(meta['status'])} |\n"

    stats = f"> 📊 **Progress:** {ac_count}/{total} Problems Solved\n\n---\n"
    
    with open(README_FILE, 'w', encoding='utf-8') as f:
        f.write(content + stats + table)
    print(f"✅ Local README updated: {oj_name}")

if __name__ == "__main__":
    generate_local_readme()