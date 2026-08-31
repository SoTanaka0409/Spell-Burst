import os
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
    in_main = False
    has_conflict = False
    
    for line in lines:
        if line.startswith('<<<<<<< HEAD'):
            has_conflict = True
            pass
        elif line.startswith('======='):
            in_main = True
        elif line.startswith('>>>>>>>'):
            in_main = False
        else:
            if not in_main:
                out_lines.append(line)
                
    if has_conflict:
        # Save back in shift_jis as MSVC expects it
        with open(filepath, 'w', encoding='shift_jis') as f:
            f.writelines(out_lines)
        return True
    return False

files = glob.glob('Source/*.cpp') + glob.glob('Source/*.h')
fixed_count = 0
for f in files:
    if fix_file(f):
        fixed_count += 1
print(f'Fixed {fixed_count} files.')
