import os
import re
import sys
import subprocess
from datetime import datetime, timedelta, timezone

# --- CONFIGURATION ---
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
README_FILE = os.path.join(BASE_DIR, 'README.md')
root_dir = os.path.join(BASE_DIR, 'Solutions') if os.path.isdir(os.path.join(BASE_DIR, 'Solutions')) else BASE_DIR

EXCLUDE_DIRS = {'.git', '.github', '.assets', 'venv', '__pycache__', '.cph'}
CITY_ID = 218 

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
    
    # 1. Kiểm tra các file link phụ như cũ
    for file_name in link_files:
        file_path = os.path.join(folder_path, file_name)
        if os.path.exists(file_path):
            try:
                with open(file_path, 'r', encoding='utf-8') as f:
                    content = f.read().strip()
                    if file_name.endswith('.url'):
                        match = re.search(r'URL=(https?://[^\s]+|\./[^\s]+)', content)
                        if match: return match.group(1)
                    if content.startswith(('http', './')):
                        return content.split('\n')[0].strip()
            except Exception: pass

    # 2. BỔ SUNG: Quét trực tiếp header trong các file .cpp ở folder này
    try:
        for file_name in os.listdir(folder_path):
            if file_name.endswith('.cpp'):
                file_path = os.path.join(folder_path, file_name)
                with open(file_path, 'r', encoding='utf-8') as f:
                    # Chỉ đọc 20 dòng đầu để tiết kiệm hiệu năng
                    header_content = "".join([next(f) for _ in range(20) if f])
                    # Regex tìm source: hỗ trợ cả link http và đường dẫn file cục bộ
                    # Dùng [^\s\*] để dừng lại khi gặp khoảng trắng hoặc dấu sao kết thúc comment
                    source_match = re.search(r'source:\s+([^\s\*]+)', header_content)
                    if source_match:
                        return source_match.group(1).strip()
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
                        # FIX: Nhận diện cả http, ./ và không dừng lại ở %20
                        match = re.search(r'(https?://[^\s\*]+|\./[^\s\*]+)', clean_line)
                        if match: meta["source"] = match.group(1).strip()
                    elif lower_line.startswith("created:"):
                        val = clean_line[8:].strip()
                        if val:
                            try:
                                dt = datetime.strptime(val.split(' ')[0], "%Y-%m-%d")
                                day = dt.strftime("%d").lstrip("0")
                                meta["date"] = dt.strftime(f"%b {day}, %Y")
                            except: meta["date"] = val
                    elif lower_line.startswith("submission:"):
                        # FIX: Tương tự cho phần submission
                        match = re.search(r'(https?://[^\s\*]+|\./[^\s\*]+)', clean_line)
                        if match: meta["submission"] = match.group(1).strip()
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
    except Exception: 
        pass
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
    """Count unique problems recursively."""
    folder_unique_ids = {} # {path: set(prob_ids)}
    
    for root, dirs, files in os.walk(directory):
        dirs[:] = [d for d in dirs if d not in EXCLUDE_DIRS]
        
        for file in files:
            if file.endswith('.cpp'):
                full_path = os.path.join(root, file)
                meta = extract_metadata(full_path)
                
                prob_link = meta["source"] or auto_generate_link(full_path)
                prob_id = prob_link if prob_link else full_path
                
                curr = root
                while True:
                    if curr not in folder_unique_ids:
                        folder_unique_ids[curr] = set()
                    folder_unique_ids[curr].add(prob_id)
                    
                    if curr == directory:
                        break
                    curr = os.path.dirname(curr)
                    
    return {path: len(s) for path, s in folder_unique_ids.items()}

def run_sub_scripts():
    """Execute update_readme_child.py if it exists in the root_dir."""
    target_script = "update_readme_child.py"
    script_path = os.path.join(root_dir, target_script)
    
    if os.path.exists(script_path):
        print(f"🚀 [SUB-SCRIPT] Child script detected at: {script_path}")
        try:
            subprocess.run([sys.executable, target_script], cwd=root_dir, check=True)
            print(f"✅ [SUB-SCRIPT] Completed: {target_script}")
        except subprocess.CalledProcessError as e:
            print(f"❌ [SUB-SCRIPT] Error running {target_script}: {e}")
        except Exception as e:
            print(f"⚠️ [SUB-SCRIPT] Unknown error: {e}")
    else:
        print(f"ℹ️ Child script {target_script} not found in {root_dir}. Skipping.")

def generate_readme():
    run_sub_scripts()
    
    print("\n📝 Aggregating main README content...")
    content = "# 🏆 Competitive Programming Solutions\n\n"
    
    unique_problems = {}
    main_content = ""
    toc_content = "## 📌 Table of Contents\n\n"
    
    if not os.path.isdir(root_dir):
        print(f"❌ Source directory {root_dir} does not exist.")
        return

    # Step 1: Count unique problems
    folder_counts = count_problems_recursive(root_dir)

    # Step 2: Traverse, filter, and generate content
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
                    
                    count = folder_counts.get(current_path, 0)
                    title_with_count = f"{display_title} ({count})"
                    
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
        
        count = folder_counts.get(path, 0)
        title_with_count = f"{title} ({count})"
        
        if is_oj_folder:
            oj_url = get_oj_link_from_file(path)
            main_content += f"## 📂 [{title_with_count}]({oj_url})\n" if oj_url else f"## 📂 {title_with_count}\n"
        else:
            main_content += f"### 📁 {title_with_count}\n"
        
        files.sort(key=natural_sort_key)
        table = "| # | Problem Name | Tags | Complexity | Date | Solution | Status |\n| :--- | :--- | :--- | :--- | :--- | :--- | :--- |\n"
        
        for i, file in enumerate(files, 1):
            full_path = os.path.join(path, file)
            meta = extract_metadata(full_path)
            
            prob_link = meta["source"] or auto_generate_link(full_path)
            prob_id = prob_link if prob_link else full_path
            
            current_status = meta["status"]
            if prob_id not in unique_problems or STATUS_MAP[current_status]['prio'] > STATUS_MAP[unique_problems[prob_id]]['prio']:
                unique_problems[prob_id] = current_status
            
            filename_no_ext = file.replace('.cpp', '')
            file_id = filename_no_ext.split('_')[0].upper() if '_' in filename_no_ext else filename_no_ext.upper()
            
            if meta["title"]:
                display_name = f"{file_id} - {meta['title']}"
            else:
                display_name = format_display_name(filename_no_ext) 
            
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
    stats += f"- **Origin Timezone:** Ho Chi Minh City (GMT+7)\n\n"
    stats += f"> *Tips: Press `ctrl + f` on Windows or `cmd + f` on MacOS to search problem by ID or Name*\n---\n"
    
    with open(README_FILE, 'w', encoding='utf-8') as f:
        f.write(content + stats + toc_content + "\n---\n" + main_content)
    print("\n✅ README system update complete!")

if __name__ == "__main__":
    generate_readme()