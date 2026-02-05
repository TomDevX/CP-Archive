import os

# Configuration
EXCLUDE_DIRS = {'.git', '.github', '.assets', 'venv', '__pycache__'}
README_FILE = 'README.md'
HEADER_FILE = 'HEADER.md'

def format_display_name(name):
    """Cleans folder/file names for professional display."""
    parts = name.split('_')
    if parts[0].isdigit():
        parts = parts[1:]
    return " ".join(parts).replace('-', ' ').title()

def generate_readme():
    # 1. Start with HEADER.md content
    if os.path.exists(HEADER_FILE):
        with open(HEADER_FILE, 'r', encoding='utf-8') as f:
            content = f.read() + "\n\n---\n"
    else:
        content = "# 🏆 Competitive Programming Repository\n\n"

    # 2. Get all directories at root
    root_dirs = sorted([d for d in os.listdir('.') if os.path.isdir(d) and d not in EXCLUDE_DIRS])
    
    total_problems = 0
    sections_content = ""

    for root_dir in root_dirs:
        # We will store all .cpp files found in this root folder and its subfolders
        cpp_files = []
        
        # Recursive scan
        for root, dirs, files in os.walk(root_dir):
            # Skip excluded directories in recursion
            dirs[:] = [d for d in dirs if d not in EXCLUDE_DIRS]
            
            for file in files:
                if file.endswith('.cpp'):
                    file_path = os.path.join(root, file)
                    # Create a readable name including subfolder info if needed
                    # Example: Solutions/CSES/WeirdAlgo.cpp -> CSES: Weird Algo
                    sub_path = os.path.relpath(root, root_dir)
                    display_name = format_display_name(file.replace('.cpp', ''))
                    
                    if sub_path != ".":
                        display_name = f"[{format_display_name(sub_path)}] {display_name}"
                    
                    cpp_files.append((display_name, file_path))

        if not cpp_files:
            continue
            
        # Sort files by name
        cpp_files.sort()
            
        category_name = format_display_name(root_dir)
        sections_content += f"## 📂 {category_name}\n"
        sections_content += "| # | Problem / Topic | Link |\n"
        sections_content += "| :--- | :--- | :--- |\n"
        
        for i, (name, path) in enumerate(cpp_files, 1):
            url_path = path.replace('\\', '/')
            sections_content += f"| {i} | {name} | [View Source]({url_path}) |\n"
            total_problems += 1
        sections_content += "\n"

    # 3. Stats Dashboard
    import datetime
    now = datetime.datetime.now().strftime("%a %b %d %Y")
    stats = f"### 📊 Repository Stats\n- **Total Items:** {total_problems}\n- **Last Sync:** {now}\n\n"
    
    # 4. Save
    with open(README_FILE, 'w', encoding='utf-8') as f:
        f.write(content + stats + sections_content)
    
    print(f"✅ Success! Found {total_problems} items across all directories.")

if __name__ == "__main__":
    generate_readme()