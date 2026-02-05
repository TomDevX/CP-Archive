import os
import re
import subprocess
from datetime import datetime, timedelta, timezone

# --- CONFIGURATION ---
EXCLUDE_DIRS = {'.git', '.github', '.assets', 'venv', '__pycache__'}
README_FILE = 'README.md'
HEADER_FILE = 'HEADER.md'
# Đã cập nhật theo đính chính của Tom: 218 = HCM
CITY_ID = 218 

def natural_sort_key(s):
    """Sắp xếp tự nhiên để xét cả giá trị số và độ dài (bài 2 đứng trước bài 10)."""
    return [int(text) if text.isdigit() else text.lower()
            for text in re.split('([0-9]+)', s)]

def get_last_commit_time():
    """Lấy thời gian của commit cuối cùng từ Git."""
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
    """
    Bóc tách metadata linh hoạt: không phụ thuộc vào số dòng.
    Quét toàn bộ khối comment /** ... **/
    """
    meta = {"source": None, "submission": None, "algorithm": "N/A", "complexity": "N/A", "title": None}
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            in_header = False
            for line in f:
                line_strip = line.strip()
                
                # Bắt đầu khối header
                if line_strip.startswith("/**"):
                    in_header = True
                    continue
                
                # Kết thúc khối header
                if "**/ " in line_strip or line_strip.endswith("**/"):
                    break
                
                if in_header:
                    # Loại bỏ dấu '*' và khoảng trắng thừa
                    clean_line = line_strip.lstrip('*').strip()
                    lower_line = clean_line.lower()
                    
                    if lower_line.startswith("title:"):
                        val = clean_line[6:].strip()
                        if val: meta["title"] = val
                    elif lower_line.startswith("source:"):
                        match = re.search(r'(https?://[^\s]+)', clean_line)
                        if match: meta["source"] = match.group(1)
                    elif lower_line.startswith("submission:"):
                        match = re.search(r'(https?://[^\s]+)', clean_line)
                        if match: meta["submission"] = match.group(1)
                    elif lower_line.startswith("algorithm:"):
                        val = clean_line[10:].strip()
                        if val:
                            algos = [f"`{a.strip()}`" for a in val.split(',') if a.strip()]
                            meta["algorithm"] = ", ".join(algos)
                    elif lower_line.startswith("complexity:"):
                        val = clean_line[11:].strip()
                        if val: 
                            # Sử dụng LaTeX cho độ phức tạp thời gian
                            meta["complexity"] = f"${val}$"
    except Exception as e:
        print(f"⚠️ Error parsing {file_path}: {e}")
    return meta

def auto_generate_link(file_path):
    """Tạo link OJ tự động dựa trên cấu trúc thư mục."""
    path_parts = file_path.replace('\\', '/').split('/')
    filename = path_parts[-1].replace('.cpp', '')
    for part in reversed(path_parts[:-1]):
        up = part.upper()
        if "CSES" in up:
            m = re.search(r'(\d+)', filename)
            return f"https://cses.fi/problemset/task/{m.group(1)}" if m else None
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
            if rel != ".": 
                main_body += f"### 📁 {format_display_name(rel)}\n"
            
            problem_list = []
            for file in files:
                full_path = os.path.join(path, file)
                meta = extract_metadata(full_path)
                name = meta["title"] if meta["title"] else format_display_name(file.replace('.cpp', ''))
                link = meta["source"] or auto_generate_link(full_path)
                problem_list.append({
                    "name": name, "link": link, "sub": meta["submission"],
                    "algo": meta["algorithm"], "comp": meta["complexity"], 
                    "path": full_path.replace('\\', '/'), "raw": file
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
    badge_msg = f"{push_time.strftime('%b %d, %Y - %H:%M')} (GMT+7)_🖱️_[CLICK TO CONVERT]".replace("-", "--").replace(" ", "_")
    badge_url = f"https://img.shields.io/badge/Last_Update-{badge_msg}-0078d4?style=for-the-badge&logo=github"
    time_link = f"https://www.timeanddate.com/worldclock/fixedtime.html?msg=Convert+to+your+timezone&iso={iso_time}&p1={CITY_ID}"

    stats = f"### 📊 Repository Stats\n\n- **Total Problems:** {total_problems}\n- **Origin Timezone:** Ho Chi Minh City (GMT+7)\n\n"
    stats += f"[![Last Update]({badge_url})]({time_link} \"Click to convert timezone\")\n\n"
    
    with open(README_FILE, 'w', encoding='utf-8') as f:
        f.write(header_content + stats + main_body)
    print(f"✅ README Updated (City ID: {CITY_ID} - HCM)")

if __name__ == "__main__":
    generate_readme()