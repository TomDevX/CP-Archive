import os

# Configuration
EXCLUDE_DIRS = {'.git', '.github', '.assets', 'venv', '__pycache__'}
README_FILE = 'README.md'
HEADER_FILE = 'HEADER.md'

def format_display_name(name):
    """
    Cleans folder/file names. 
    Example: '01_dynamic_programming' -> 'Dynamic Programming'
    """
    # Remove leading numbers and underscores
    parts = name.split('_')
    if parts[0].isdigit():
        parts = parts[1:]
    return " ".join(parts).replace('-', ' ').title()

def generate_readme():
    # 1. Start with the static Header
    if os.path.exists(HEADER_FILE):
        with open(HEADER_FILE, 'r', encoding='utf-8') as f:
            content = f.read() + "\n\n---\n"
    else:
        content = "# 🏆 Competitive Programming Repository\n\n"

    # 2. Scan for folders (Categories)
    dirs = sorted([d for d in os.listdir('.') if os.path.isdir(d) and d not in EXCLUDE_DIRS])
    
    total_problems = 0
    sections_html = ""

    for folder in dirs:
        # Get all .cpp files in this folder
        files = sorted([f for f in os.listdir(folder) if f.endswith('.cpp')])
        
        if not files:
            continue
            
        category_name = format_display_name(folder)
        sections_html += f"## 📂 {category_name}\n"
        sections_html += "| # | Problem Name | Code Link |\n"
        sections_html += "| :--- | :--- | :--- |\n"
        
        for i, file in enumerate(files, 1):
            # Clean file name: 'CSES_1068_WeirdAlgo.cpp' -> 'Weird Algo'
            # Or if it's just 'WeirdAlgo.cpp' -> 'Weird Algo'
            clean_file = file.replace('.cpp', '')
            display_file = format_display_name(clean_file)
            
            path = f"./{folder}/{file}".replace('\\', '/')
            sections_html += f"| {i} | {display_file} | [View Solution]({path}) |\n"
            total_files_in_cat = i
            
        total_problems += total_files_in_cat
        sections_html += "\n"

    # 3. Add a Stats Dashboard
    stats = f"### 📊 Repository Stats\n- **Total Problems Solved:** {total_problems}\n- **Last Updated:** {os.popen('date').read().strip()}\n\n"
    
    final_output = content + stats + sections_html

    # 4. Write to README.md
    with open(README_FILE, 'w', encoding='utf-8') as f:
        f.write(final_output)
    
    print(f"✅ README.md updated successfully with {total_problems} problems.")

if __name__ == "__main__":
    generate_readme()