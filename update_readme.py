import os
import re
import subprocess
from datetime import datetime, timedelta, timezone

# --- CONFIGURATION ---
EXCLUDE_DIRS = {'.git', '.github', '.assets', 'venv', '__pycache__'}
README_FILE = 'README.md'
HEADER_FILE = 'HEADER.md'
CITY_ID = 218  # Đã chuẩn hóa: 218 là Hồ Chí Minh (GMT+7)

def natural_sort_key(s):
    """Sort tự nhiên để bài 2 đứng trước bài 10."""
    return [int(text) if text.isdigit() else text.lower()
            for text in re.split('([0-9]+)', s)]

def get_last_commit_time():
    """Lấy thời gian của lần commit/push cuối cùng."""
    try:
        timestamp = subprocess.check_output(['git', 'log', '-1', '--format=%at']).decode('utf-8').strip()
        tz_hcm = timezone(timedelta(hours=7))
        return datetime.fromtimestamp(int(timestamp), tz=tz_hcm)
    except Exception:
        return datetime.now(timezone(timedelta(hours=7)))

def format_display_name(name):
    """Làm đẹp tên file/folder."""
    parts = name.split('_')
    if parts[0].isdigit():
        parts = parts[1:]
    return " ".join(parts).replace('-', ' ').title()

def extract_metadata(file_path):
    """Bóc tách metadata dựa trên Header mới của Tom."""
    meta = {"source": None, "submission": None, "algorithm": "N/A", "complexity": "N/A", "title": None}
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            # Đọc 25 dòng đầu để đảm bảo bao phủ hết block comment mới
            for _ in range(25):
                line = f.readline()
                if not line or "**/" in line: break
                
                line_clean = line.strip().replace('*', '').strip()
                line_lower = line_clean.lower()
                
                if line_lower.startswith("title:"):
                    val = line_clean[6:].strip()
                    if val: meta["title"] = val
                elif line_lower.startswith("source:"):
                    match = re.search(r'(https?://[^\s]+)', line_clean)
                    if match: meta["source"] = match.group(1)
                elif line_lower.startswith("submission:"):
                    match = re.search(r'(https?://[^\s]+)', line_clean)
                    if match: meta["submission"] = match.group(1)
                elif line_lower.startswith("algorithm:"):
                    val = line_clean[10:].strip()
                    if val:
                        algos = [f"`{a.strip()}`" for a in val.split(',') if a.strip()]
                        meta["algorithm"] = ", ".join(algos)
                elif line_lower.startswith("complexity:"):
                    val = line_clean[11:].strip()
                    if val: meta["complexity"] = f"`{val}`"
    except: pass
    return meta

def auto_generate_link(file_path):
    """Fallback link nếu header thiếu source."""
    path_parts = file_path.replace('\\', '/').split('/')
    filename = path_parts[-1].replace('.cpp', '')
    for part in reversed(path_parts[:-1]):
        up = part.upper()
        if "CSES" in up:
            id_m = re.search(r'(\d+)', filename)
            return f"https://cses.fi/problemset/task/{id_m.group(1)}" if id_m else None
        if "VNOI" in up: return f"https://oj.vnoi.info/problem/{filename.lower()}"
    return None

def generate_readme():
    header_content = ""
    if os.path.exists(HEADER_FILE):
        with open(HEADER_FILE, 'r', encoding='utf-8') as f:
            header_content = f.read() + "\n\n---\n"
    else:
        header_content = "# 🏆 Competitive Programming Repository\n\n"

    total_problems = 0
    main_body = ""
    root_dirs = sorted([d for d in os.listdir('.') if os.path.isdir(d) and d not in EXCLUDE_DIRS], key=natural_sort_key)

    for root_dir in root_dirs:
        main_body += f"## 📂 {format_display_name(root_dir)}\n"
        folder_data = []
        for root, ds, files in os.walk(root_dir):
            ds[:] = [d for d in ds if d not in EXCLUDE_DIRS]
            cpp = [f for f in files if f.endswith('.cpp')]
            if cpp: folder_data.append((root, cpp))

        folder_data.sort(key=lambda x: natural_sort_key(x[0]))
        for path, files in folder_data:
            rel = os.path.relpath(path, root_dir)
            if rel != ".": main_body += f"### 📁 {format_display_name(rel)}\n"
            
            problem_list = []
            for file in files:
                meta = extract_metadata(os.path.join(path, file))
                name = meta["title"] if meta["title"] else format_display_name(file.replace('.cpp', ''))
                link = meta["source"] or auto_generate_link(os.path.join(path, file))
                problem_list.append({
                    "name": name, "link": link, "sub": meta["submission"],
                    "algo": meta["algorithm"], "comp": meta["complexity"], 
                    "path": os.path.join(path, file).replace('\\', '/'), "raw": file
                })
            
            problem_list.sort(key=lambda x: natural_sort_key(x["raw"]))
            table = "| # | Problem Name | Algorithm | Complexity | Solution |\n| :--- | :--- | :--- | :--- | :--- |\n"
            for i, p in enumerate(problem_list, 1):
                name_md = f"[{p['name']}]({p['link']})" if p['link'] else p['name']
                sol_md = f"[Code]({p['path']})"
                if p['sub']: sol_md += f" \| [Sub]({p['sub']})"
                table += f"| {i} | {name_md} | {p['algo']} | {p['comp']} | {sol_md} |\n"
                total_problems += 1
            main_body += table + "\n"

    # --- TIME & STATS ---
    push_time = get_last_commit_time()
    iso_time = push_time.strftime("%Y%m%dT%H%M")
    badge_msg = f"{push_time.strftime('%b %d, %Y - %H:%M')} (GMT+7)_🖱️_[CLICK]".replace("-", "--").replace(" ", "_")
    badge_url = f"https://img.shields.io/badge/Last_Update-{badge_msg}-0078d4?style=for-the-badge&logo=github"
    time_link = f"https://www.timeanddate.com/worldclock/fixedtime.html?msg=Convert+to+your+timezone&iso={iso_time}&p1={CITY_ID}"

    stats = f"### 📊 Repository Stats\n\n- **Total Problems:** {total_problems}\n- **Origin Timezone:** Ho Chi Minh City (GMT+7)\n\n"
    stats += f"[![Last Update]({badge_url})]({time_link} \"Click to convert timezone\")\n\n"
    stats += f"**TIP:** *Click the badge to see the update time in your local zone.* 🌍\n\n---\n"
    
    with open(README_FILE, 'w', encoding='utf-8') as f:
        f.write(header_content + stats + main_body)
    print(f"✅ README Updated (City ID: {CITY_ID} - HCM)")

if __name__ == "__main__":
    generate_readme()