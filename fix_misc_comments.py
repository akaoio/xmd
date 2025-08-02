#!/usr/bin/env python3
import os
import re

# Find all misc C files
misc_files = []
for root, dirs, files in os.walk('src/misc'):
    for file in files:
        if file.endswith('.c'):
            misc_files.append(os.path.join(root, file))

for filepath in misc_files:
    try:
        with open(filepath, 'r') as f:
            content = f.read()
        
        # Replace the pattern of include followed by " */" and function declaration
        content = re.sub(
            r'(#include [^\n]+)\n \*/\n([a-zA-Z])',
            r'\1\n\n/**\n * @brief Function implementation\n */\n\2',
            content
        )
        
        with open(filepath, 'w') as f:
            f.write(content)
        
        print(f"Fixed {filepath}")
    except Exception as e:
        print(f"Error fixing {filepath}: {e}")