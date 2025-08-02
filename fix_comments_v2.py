#!/usr/bin/env python3
import os
import re
import sys

def fix_c_file(filepath):
    with open(filepath, 'r') as f:
        lines = f.readlines()
    
    fixed_lines = []
    in_comment = False
    i = 0
    
    while i < len(lines):
        line = lines[i]
        stripped = line.strip()
        
        # Check if we're starting a comment block
        if stripped.startswith('/**'):
            if in_comment:
                # We're already in a comment, skip this line
                i += 1
                continue
            else:
                in_comment = True
                fixed_lines.append(line)
        # Check if we're ending a comment block
        elif stripped.endswith('*/'):
            in_comment = False
            fixed_lines.append(line)
        # Check for orphan comment content that needs /**
        elif (not in_comment and 
              stripped.startswith('* @') and 
              (i == 0 or not lines[i-1].strip().startswith('/**'))):
            # Add opening comment
            fixed_lines.append('/**\n')
            fixed_lines.append(line)
            in_comment = True
        else:
            fixed_lines.append(line)
        
        i += 1
    
    # Write back
    with open(filepath, 'w') as f:
        f.writelines(fixed_lines)

if __name__ == '__main__':
    if len(sys.argv) > 1:
        for filepath in sys.argv[1:]:
            if filepath.endswith('.c'):
                print(f"Fixing {filepath}")
                fix_c_file(filepath)
    else:
        # Fix all C files in src/
        for root, dirs, files in os.walk('src/'):
            for file in files:
                if file.endswith('.c'):
                    filepath = os.path.join(root, file)
                    print(f"Fixing {filepath}")
                    fix_c_file(filepath)