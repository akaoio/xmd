#!/usr/bin/env python3
import os
import re
import sys

def fix_c_file(filepath):
    with open(filepath, 'r') as f:
        content = f.read()
    
    # Pattern 1: Fix include followed immediately by /** without blank line
    content = re.sub(r'(#include [^\n]+)\n(/\*\*)', r'\1\n\n\2', content)
    
    # Pattern 2: Fix missing */ before function declaration
    # This matches /** followed by * @brief and then a function declaration without closing */
    content = re.sub(
        r'(/\*\*\n\s*\* @brief[^\n]+\n)(\s*\* @[^\n]+\n)*(\s*\*[^\n]*\n)*([a-zA-Z_][a-zA-Z0-9_*\s]+\([^)]*\)\s*{)',
        r'\1\2\3 */\n\4',
        content
    )
    
    # Pattern 3: Fix orphaned /** that should be part of the previous comment block
    content = re.sub(r'(\*/)\n+/\*\*\n(\s*\* @)', r'\1\n\n/**\n\2', content)
    
    # Pattern 4: Remove duplicate /** lines 
    content = re.sub(r'/\*\*\n\s*/\*\*', r'/**', content)
    
    # Pattern 5: Fix unterminated comments - add */ before function definitions
    lines = content.split('\n')
    fixed_lines = []
    in_comment = False
    
    for i, line in enumerate(lines):
        stripped = line.strip()
        
        # Track comment state
        if stripped.startswith('/**'):
            in_comment = True
        elif stripped.endswith('*/'):
            in_comment = False
        
        # If we're in a comment and the next line looks like a function definition
        if (in_comment and 
            i + 1 < len(lines) and 
            re.match(r'^[a-zA-Z_][a-zA-Z0-9_*\s]+\s+[a-zA-Z_][a-zA-Z0-9_]*\s*\([^)]*\)\s*{?\s*$', lines[i + 1])):
            # Add closing */ if current line doesn't have it
            if not stripped.endswith('*/'):
                fixed_lines.append(line + ' */' if line.strip() else ' */')
                in_comment = False
            else:
                fixed_lines.append(line)
        else:
            fixed_lines.append(line)
    
    content = '\n'.join(fixed_lines)
    
    with open(filepath, 'w') as f:
        f.write(content)

if __name__ == '__main__':
    # Target the specific directories that have issues
    target_dirs = [
        'src/variable/create',
        'src/variable/array',
        'src/variable/object',
        'src/variable/operations',
        'src/variable/memory'
    ]
    
    for target_dir in target_dirs:
        if os.path.exists(target_dir):
            for file in os.listdir(target_dir):
                if file.endswith('.c'):
                    filepath = os.path.join(target_dir, file)
                    print(f"Fixing {filepath}")
                    fix_c_file(filepath)