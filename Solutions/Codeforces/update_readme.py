import os
import re

CURRENT_DIR = os.path.dirname(os.path.abspath(__file__))
README_FILE = os.path.join(CURRENT_DIR, 'README.md')

STATUS_MAP = {
    "AC": {"color": "4c1"}, "WA": {"color": "e05d44"}, "TLE": {"color": "dfb317"}, "WIP": {"color": "007ec6"}
}

def natural_sort_key(s):
    return [int(text) if text.isdigit() else text.lower() for text in re.split('([0-9]+)', s)]

def auto_generate_link(file_path):
    # Logic same as master for standalone run
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
        if "LEETCODE" in up: return f"https://leetcode.com/problems/{filename.lower().replace('_', '-')}/"
    return None

def extract_metadata(file_path):
    meta = {"source": None, "title": None, "status": "AC", "tags": "N/A", "complexity": "N/A"}
    try:
        with open(file_path, 'r', encoding='utf-8') as f:
            for line in f:
                low = line.lower()
                if "title:" in low: meta["title"] = line.split(":", 1)[1].strip()
                if "status:" in low: 
                    s = line.split(":", 1)[1].strip().upper()
                    meta["status"] = "WIP" if "WIP" in s else (s if s in STATUS_MAP else "AC")
                if "source:" in low:
                    m = re.search(r'(https?://[^\s]+)', line)
                    if m: meta["source"] = m.group(1)
                if "tags:" in low: meta["tags"] = line.split(":", 1)[1].strip()
                if "complexity:" in low: meta["complexity"] = line.split(":", 1)[1].strip()
    except: pass
    return meta

def get_badge(status):
    color = STATUS_MAP.get(status, {"color": "4c1"})["color"]
    return f"![{status}](https://img.shields.io/static/v1?label=&message=%20{status}%20&color={color}&style=for-the-badge)"

def generate():
    oj_name = os.path.basename(CURRENT_DIR) # Original folder name
    files = sorted([f for f in os.listdir(CURRENT_DIR) if f.endswith('.cpp')], key=natural_sort_key)
    
    content = f"# 📂 {oj_name} Solutions\n\n> **{len(files)}** solutions found in this directory.\n\n"
    table = "| # | Problem Name | Tags | Complexity | Source | Status |\n| :--- | :--- | :--- | :--- | :--- | :--- |\n"
    
    for i, f in enumerate(files, 1):
        full_path = os.path.join(CURRENT_DIR, f)
        meta = extract_metadata(full_path)
        name = meta["title"] if meta["title"] else f.replace('.cpp', '').replace('_', ' ').strip()
        link = meta["source"] or auto_generate_link(full_path)
        
        table += f"| {i} | [{name}]({link or '#'}) | {meta['tags']} | {meta['complexity']} | [`{f}`]({f}) | {get_badge(meta['status'])} |\n"
    
    with open(README_FILE, 'w', encoding='utf-8') as f:
        f.write(content + table)
    print(f"✅ Local README updated: {oj_name}")

if __name__ == "__main__":
    generate()