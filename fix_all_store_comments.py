#!/usr/bin/env python3
import os
import re

def fix_file(filepath):
    with open(filepath, 'r') as f:
        lines = f.readlines()
    
    fixed_lines = []
    i = 0
    
    while i < len(lines):
        line = lines[i]
        
        # Look for orphaned /** followed by a function-like line
        if line.strip() == '/**' and i + 1 < len(lines):
            next_line = lines[i + 1].strip()
            # Check if next line looks like a function parameter description
            if next_line.startswith('* @'):
                # Add the /** line
                fixed_lines.append(line)
                i += 1
                # Add all comment lines until we find the function
                while i < len(lines) and not re.match(r'^[a-zA-Z_][a-zA-Z0-9_*\s]+\s+[a-zA-Z_][a-zA-Z0-9_]*\s*\(', lines[i]):
                    fixed_lines.append(lines[i])
                    i += 1
                # Add closing */ if missing
                if i < len(lines) and re.match(r'^[a-zA-Z_][a-zA-Z0-9_*\s]+\s+[a-zA-Z_][a-zA-Z0-9_]*\s*\(', lines[i]):
                    fixed_lines.append(' */\n')
            else:
                fixed_lines.append(line)
                i += 1
        else:
            fixed_lines.append(line)
            i += 1
    
    with open(filepath, 'w') as f:
        f.writelines(fixed_lines)

# Fix all store files
store_dirs = ['src/store/create', 'src/store/memory', 'src/store/operations']
for store_dir in store_dirs:
    if os.path.exists(store_dir):
        for file in os.listdir(store_dir):
            if file.endswith('.c'):
                filepath = os.path.join(store_dir, file)
                print(f"Fixing {filepath}")
                fix_file(filepath)