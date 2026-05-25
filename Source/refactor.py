import os
import re

dir_path = r"c:\Users\Admin\Desktop\progtram\AiGame_\Source"

for root, _, files in os.walk(dir_path):
    for file in files:
        if file.endswith('.cpp') or file.endswith('.h'):
            path = os.path.join(root, file)
            with open(path, 'rb') as f:
                raw = f.read()
            try:
                text = raw.decode('shift_jis')
                encoding = 'shift_jis'
            except UnicodeDecodeError:
                try:
                    text = raw.decode('utf-8')
                    encoding = 'utf-8'
                except:
                    continue
            
            new_text = re.sub(r'\bm_x\b', 'mvPosition.x', text)
            new_text = re.sub(r'\bm_y\b', 'mvPosition.y', new_text)
            new_text = re.sub(r'^[ \t]*float\s+mvPosition\.x\s*,\s*mvPosition\.y\s*;.*$\n?', '', new_text, flags=re.MULTILINE)
            
            if new_text != text:
                with open(path, 'wb') as f:
                    f.write(new_text.encode(encoding))
                print(f"Updated {file}")
