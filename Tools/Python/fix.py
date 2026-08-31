import glob

def fix_file(filepath):
    try:
        with open(filepath, 'r', encoding='utf-8') as f:
            lines = f.readlines()
    except UnicodeDecodeError:
        try:
            with open(filepath, 'r', encoding='shift_jis') as f:
                lines = f.readlines()
        except Exception:
            return False

    out_lines = []
    state = "NORMAL"
    has_conflict = False

    for line in lines:
        if line.startswith("<<<<<<< HEAD"):
            state = "HEAD"
            has_conflict = True
        elif line.startswith("======="):
            state = "MAIN"
        elif line.startswith(">>>>>>>"):
            state = "NORMAL"
        else:
            if state == "NORMAL" or state == "HEAD":
                out_lines.append(line)

    if has_conflict:
        with open(filepath, 'w', encoding='shift_jis') as f:
            f.writelines(out_lines)
        return True
    return False

files = glob.glob('Source/*.cpp') + glob.glob('Source/*.h')
count = 0
for f in files:
    if fix_file(f):
        count += 1
print(f"Fixed {count} files")
