import os
import subprocess
import re

def get_original_text(filepath):
    try:
        # Get bytes from git HEAD
        result = subprocess.run(['git', 'show', f'HEAD:{filepath}'], capture_output=True)
        if result.returncode != 0:
            return None
        data = result.stdout
        # Try decodings
        if data.startswith(b'\xff\xfe'):
            return data.decode('utf-16le')
        if data.startswith(b'\xef\xbb\xbf'):
            return data.decode('utf-8-sig')
        try:
            return data.decode('shift_jis')
        except:
            return data.decode('utf-8', errors='ignore')
    except Exception as e:
        return None

def fix_file(filepath):
    orig_text = get_original_text(filepath)
    if not orig_text:
        return
        
    with open(filepath, 'r', encoding='utf-8') as f:
        curr_text = f.read()
        
    # If there's no replacement character in the current text, it might be fine, but we need to check if PlaySE or DrawString are messed up.
    # Actually, the replacement character is \uFFFD.
    if '\uFFFD' not in curr_text and '.3' not in curr_text:
        return
        
    orig_lines = orig_text.splitlines()
    curr_lines = curr_text.splitlines()
    
    # We will just replace any line in curr_lines that contains \uFFFD or '.3"' with the closest matching line from orig_lines
    for i, line in enumerate(curr_lines):
        if '\uFFFD' in line or '.3"' in line or 'mp3' not in line and 'PlaySE' in line:
            # Find a matching line in orig_lines
            # We look for a line in orig_lines that has a similar structure
            for orig_line in orig_lines:
                # Basic heuristic: if the line contains PlaySE and the current line contains PlaySE
                if 'PlaySE' in line and 'PlaySE' in orig_line:
                    # just take the original
                    curr_lines[i] = orig_line
                    break
                elif 'DrawString' in line and 'DrawString' in orig_line:
                    # check if they share something
                    curr_lines[i] = orig_line
                    break
                elif '//' in line and '//' in orig_line:
                    # A bit risky, but if it's a comment, maybe just ignore or try to match line number
                    pass
            
            # Better approach for comments: just use the original line at the same index if it exists and both start with //
            if i < len(orig_lines) and orig_lines[i].strip().startswith('//') and curr_lines[i].strip().startswith('//'):
                curr_lines[i] = orig_lines[i]

    with open(filepath, 'w', encoding='utf-8-sig') as f:
        f.write('\n'.join(curr_lines))
        
for root, dirs, files in os.walk('Source'):
    for file in files:
        if file.endswith('.cpp') or file.endswith('.h'):
            fix_file(os.path.join(root, file))
