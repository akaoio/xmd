#!/usr/bin/env python3
import os
import re
import glob

# Find all C files with the problematic pattern
problem_files = []

# Search in performance and resource directories
for pattern in ['src/performance/**/*.c', 'src/resource/**/*.c']:
    for filepath in glob.glob(pattern, recursive=True):
        try:
            with open(filepath, 'r') as f:
                content = f.read()
                # Look for orphaned */ or incomplete comment blocks
                if re.search(r'^\s*\*/\s*$', content, re.MULTILINE) or \
                   re.search(r'^\s*\* @(?:param|return|brief)', content, re.MULTILINE):
                    problem_files.append(filepath)
        except:
            pass

print(f"Found {len(problem_files)} files to fix")

for filepath in problem_files:
    with open(filepath, 'r') as f:
        lines = f.readlines()
    
    fixed_lines = []
    i = 0
    while i < len(lines):
        line = lines[i]
        
        # Check if this line is an orphaned comment parameter/return
        if re.match(r'^\s*\* @(param|return|brief)', line.strip()):
            # Add opening /** if not in a comment block
            if i == 0 or not re.match(r'^\s*(/\*\*|\*)', lines[i-1].strip()):
                fixed_lines.append('/**\n')
            fixed_lines.append(line)
        # Check for orphaned */
        elif line.strip() == '*/':
            # Skip if it's immediately after an include
            if i > 0 and '#include' in lines[i-1]:
                i += 1
                continue
            fixed_lines.append(line)
        else:
            fixed_lines.append(line)
        
        i += 1
    
    # Write back
    with open(filepath, 'w') as f:
        f.writelines(fixed_lines)
    
    print(f"Fixed {filepath}")