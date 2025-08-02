#!/usr/bin/env python3
import os
import re
import sys

def fix_c_file(filepath):
    with open(filepath, 'r') as f:
        content = f.read()
    
    # Fix files that have multiple /** on consecutive lines
    # This pattern matches /** on one line followed by /** on the next
    content = re.sub(r'/\*\*\n\s*/\*\*', r'/**', content, flags=re.MULTILINE)
    
    # Fix files that have /** followed by another /** after some lines
    content = re.sub(r'/\*\*\n([^\n]*\n){0,2}/\*\*', r'/**\n\1', content)
    
    # Remove empty comment lines that appear right after /**
    content = re.sub(r'/\*\*\n\s*\n\s*\*', r'/**\n *', content)
    
    # Fix files where * @file or * @brief appears without opening /**
    content = re.sub(r'(?<!\*)\n\s*\* @file', r'\n/**\n * @file', content)
    content = re.sub(r'^(?<!\*)\s*\* @file', r'/**\n * @file', content, flags=re.MULTILINE)
    content = re.sub(r'(?<!\*)\n\s*\* @brief', r'\n/**\n * @brief', content)
    
    with open(filepath, 'w') as f:
        f.write(content)

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