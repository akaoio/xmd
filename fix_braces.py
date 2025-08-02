#!/usr/bin/env python3
import os
import re

def count_braces(content):
    """Count opening and closing braces"""
    open_count = content.count('{')
    close_count = content.count('}')
    return open_count, close_count

def fix_brace_issues(filepath):
    """Try to fix common brace issues"""
    with open(filepath, 'r') as f:
        lines = f.readlines()
    
    fixed = False
    new_lines = []
    brace_level = 0
    
    for i, line in enumerate(lines):
        new_lines.append(line)
        
        # Count braces in this line
        open_braces = line.count('{')
        close_braces = line.count('}')
        brace_level += open_braces - close_braces
        
        # Check for common patterns that indicate missing braces
        stripped = line.strip()
        
        # Pattern: "free(var);" not followed by return/close brace
        if (stripped.startswith('free(') and stripped.endswith(');') and 
            i + 1 < len(lines) and 
            not lines[i + 1].strip().startswith('return') and
            not lines[i + 1].strip() == '}'):
            # Check if next line looks like it should be in else block
            next_line = lines[i + 1].strip() if i + 1 < len(lines) else ""
            if next_line and not next_line.startswith('}'):
                # Likely missing a return NULL; }
                new_lines.append('        return NULL;\n')
                new_lines.append('    }\n')
                fixed = True
    
    # Write back if we made changes
    if fixed:
        with open(filepath, 'w') as f:
            f.writelines(new_lines)
        return True
    
    # Check final brace balance
    open_count, close_count = count_braces(''.join(new_lines))
    if open_count != close_count:
        print(f"  Brace mismatch in {filepath}: {open_count} open, {close_count} close")
        return False
    
    return False

# Find files with compilation errors
error_files = [
    "src/variable/create/variable_new_array.c",
    "src/variable/memory/variable_unref.c", 
    "src/variable/object/variable_object_find_key.c"
]

for filepath in error_files:
    if os.path.exists(filepath):
        print(f"Checking {filepath}")
        if fix_brace_issues(filepath):
            print(f"  Fixed issues in {filepath}")
        else:
            # Manual check
            with open(filepath, 'r') as f:
                content = f.read()
            open_count, close_count = count_braces(content)
            print(f"  Braces: {open_count} open, {close_count} close")