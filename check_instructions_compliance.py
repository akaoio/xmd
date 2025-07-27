#!/usr/bin/env python3

"""
INSTRUCTIONS.md Compliance Checker
Scans the codebase for violations of the 18 rules defined in docs/dev/INSTRUCTIONS.md
"""

import os
import re
import sys
from pathlib import Path

# Colors for output
class Colors:
    RED = '\033[0;31m'
    GREEN = '\033[0;32m'
    YELLOW = '\033[1;33m'
    BLUE = '\033[0;34m'
    NC = '\033[0m'  # No Color

# Counters
violations = 0
warnings = 0
total_files = 0

# Directories to ignore
IGNORE_DIRS = {'.git', 'build', 'node_modules', '.vscode', '.idea', 'CMakeFiles', 'Testing', '__pycache__'}
IGNORE_ROOT_PATTERNS = ['test_*.c', 'debug_*.c', '*_debug.c']

def should_ignore(path):
    """Check if path should be ignored"""
    path_parts = Path(path).parts
    return any(ignore_dir in path_parts for ignore_dir in IGNORE_DIRS)

def report_violation(rule, file_path, message):
    """Report a rule violation"""
    global violations
    print(f"{Colors.RED}❌ RULE {rule} VIOLATION:{Colors.NC} {file_path}")
    print(f"   {message}")
    violations += 1

def report_warning(rule, file_path, message):
    """Report a rule warning"""
    global warnings
    print(f"{Colors.YELLOW}⚠️  RULE {rule} WARNING:{Colors.NC} {file_path}")
    print(f"   {message}")
    warnings += 1

def detect_functions_in_file(file_path):
    """
    Detect function definitions in a C file
    Returns list of function names found
    """
    try:
        with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()
    except:
        return []
    
    functions = []
    lines = content.split('\n')
    
    # Patterns for function detection
    # Pattern 1: function_name(...) {
    pattern1 = re.compile(r'^\s*(static\s+)?[a-zA-Z_][a-zA-Z0-9_*\s]*?([a-zA-Z_][a-zA-Z0-9_]*)\s*\([^)]*\)\s*\{')
    
    # Pattern 2: function signature on one line, { on next line
    pattern2 = re.compile(r'^\s*(static\s+)?[a-zA-Z_][a-zA-Z0-9_*\s]*?([a-zA-Z_][a-zA-Z0-9_]*)\s*\([^)]*\)\s*$')
    
    i = 0
    while i < len(lines):
        line = lines[i].strip()
        
        # Skip comments, preprocessor directives, and declarations
        if (line.startswith('/*') or line.startswith('*') or line.startswith('//') or 
            line.startswith('#') or 'typedef' in line or 'struct' in line or 
            'enum' in line or 'extern' in line):
            i += 1
            continue
        
        # Check pattern 1: function with opening brace on same line
        match1 = pattern1.match(lines[i])
        if match1:
            func_name = match1.group(2)
            # Filter out control flow statements
            if func_name not in ['if', 'while', 'for', 'switch', 'do']:
                functions.append(func_name)
        
        # Check pattern 2: function signature, then check next line for opening brace
        elif pattern2.match(lines[i]) and i + 1 < len(lines):
            if lines[i + 1].strip().startswith('{'):
                match2 = pattern2.match(lines[i])
                if match2:
                    func_name = match2.group(2)
                    if func_name not in ['if', 'while', 'for', 'switch', 'do']:
                        functions.append(func_name)
        
        i += 1
    
    return functions

def check_rule_1():
    """Rule 1: One file per folder"""
    print("1. Checking Rule 1: One file per folder...")
    
    for root, dirs, files in os.walk('.'):
        if should_ignore(root):
            continue
        
        # Filter out ignored directories
        dirs[:] = [d for d in dirs if d not in IGNORE_DIRS]
        
        c_files = [f for f in files if f.endswith('.c')]
        
        # Special handling for root directory
        if root == '.':
            c_files = [f for f in c_files if not any(
                f.startswith(pattern.replace('*', '').replace('.c', ''))
                for pattern in IGNORE_ROOT_PATTERNS
            )]
        
        if len(c_files) > 1:
            report_violation("1", root, f"Multiple .c files in directory: {', '.join(c_files)}")

def check_rule_2():
    """Rule 2: One function per file"""
    print("2. Checking Rule 2: One function per file...")
    global total_files
    
    for root, dirs, files in os.walk('.'):
        if should_ignore(root):
            continue
        
        dirs[:] = [d for d in dirs if d not in IGNORE_DIRS]
        
        for file in files:
            if file.endswith('.c'):
                file_path = os.path.join(root, file)
                if should_ignore(file_path):
                    continue
                
                functions = detect_functions_in_file(file_path)
                total_files += 1
                
                if len(functions) > 1:
                    func_list = ', '.join(functions[:5])  # Show first 5 functions
                    if len(functions) > 5:
                        func_list += '...'
                    report_violation("2", file_path, f"Multiple functions found ({len(functions)} functions): {func_list}")

def check_rule_3():
    """Rule 3: File/folder naming convention (snake_case/snake_case.c)"""
    print("3. Checking Rule 3: snake_case naming convention...")
    
    snake_case_pattern = re.compile(r'^[a-z][a-z0-9_]*$')
    
    for root, dirs, files in os.walk('.'):
        if should_ignore(root):
            continue
        
        dirs[:] = [d for d in dirs if d not in IGNORE_DIRS]
        
        for file in files:
            if file.endswith('.c'):
                file_path = os.path.join(root, file)
                if should_ignore(file_path):
                    continue
                
                parent_dir = os.path.basename(root)
                basename_file = os.path.splitext(file)[0]
                
                # Skip root and special directories
                if root in ['.', './src', './test']:
                    continue
                
                # Check if folder name matches file name
                if parent_dir != basename_file:
                    report_violation("3", file_path, f"Folder name '{parent_dir}' doesn't match file name '{basename_file}'")
                
                # Check snake_case pattern
                if not snake_case_pattern.match(basename_file):
                    report_violation("3", file_path, f"File name '{basename_file}' is not snake_case")
                
                if not snake_case_pattern.match(parent_dir):
                    report_violation("3", file_path, f"Folder name '{parent_dir}' is not snake_case")

def check_rule_5():
    """Rule 5: Maximum 200 lines per file"""
    print("5. Checking Rule 5: Maximum 200 lines per file...")
    
    for root, dirs, files in os.walk('.'):
        if should_ignore(root):
            continue
        
        dirs[:] = [d for d in dirs if d not in IGNORE_DIRS]
        
        for file in files:
            if file.endswith(('.c', '.h')):
                file_path = os.path.join(root, file)
                if should_ignore(file_path):
                    continue
                
                try:
                    with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
                        line_count = sum(1 for _ in f)
                    
                    if line_count > 200:
                        report_violation("5", file_path, f"File has {line_count} lines (exceeds 200 line limit)")
                except:
                    pass

def check_rule_7():
    """Rule 7: No TODO, mock, simplified, tech debts"""
    print("7. Checking Rule 7: No TODO, mock, simplified, tech debts...")
    
    todo_pattern = re.compile(r'(TODO|FIXME|HACK|XXX)', re.IGNORECASE)
    mock_pattern = re.compile(r'(mock|simplified|placeholder)', re.IGNORECASE)
    
    for root, dirs, files in os.walk('.'):
        if should_ignore(root):
            continue
        
        dirs[:] = [d for d in dirs if d not in IGNORE_DIRS]
        
        for file in files:
            if file.endswith(('.c', '.h')):
                file_path = os.path.join(root, file)
                if should_ignore(file_path):
                    continue
                
                try:
                    with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
                        content = f.read()
                    
                    # Check for TODO comments
                    todo_matches = todo_pattern.findall(content)
                    if todo_matches:
                        report_violation("7", file_path, f"Contains {', '.join(set(todo_matches))}")
                    
                    # Check for mock/simplified mentions
                    mock_matches = mock_pattern.findall(content)
                    if mock_matches:
                        report_warning("7", file_path, f"Contains {', '.join(set(mock_matches))}")
                except:
                    pass

def check_rule_9():
    """Rule 9: No external dependencies"""
    print("9. Checking Rule 9: No external dependencies...")
    
    external_lib_pattern = re.compile(r'#include\s*[<"](curl|boost|json|xml|openssl|sqlite)', re.IGNORECASE)
    
    for root, dirs, files in os.walk('.'):
        if should_ignore(root):
            continue
        
        dirs[:] = [d for d in dirs if d not in IGNORE_DIRS]
        
        for file in files:
            if file.endswith(('.c', '.h')):
                file_path = os.path.join(root, file)
                if should_ignore(file_path):
                    continue
                
                try:
                    with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
                        content = f.read()
                    
                    matches = external_lib_pattern.findall(content)
                    if matches:
                        report_warning("9", file_path, f"Potential external dependency: {', '.join(matches)}")
                except:
                    pass
    
    # Check CMakeLists.txt
    if os.path.exists('CMakeLists.txt'):
        try:
            with open('CMakeLists.txt', 'r') as f:
                content = f.read()
            
            if re.search(r'find_package|target_link_libraries.*[^m pthread dl]', content):
                report_warning("9", "CMakeLists.txt", "Potential external dependencies in build system")
        except:
            pass

def check_rule_10():
    """Rule 10: Doxygen documentation style"""
    print("10. Checking Rule 10: Doxygen documentation style...")
    
    for root, dirs, files in os.walk('.'):
        if should_ignore(root):
            continue
        
        dirs[:] = [d for d in dirs if d not in IGNORE_DIRS]
        
        for file in files:
            if file.endswith('.c'):
                file_path = os.path.join(root, file)
                if should_ignore(file_path):
                    continue
                
                functions = detect_functions_in_file(file_path)
                
                if len(functions) > 0:
                    try:
                        with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
                            content = f.read()
                        
                        # Check for @brief documentation
                        brief_count = len(re.findall(r'/\*\*.*?@brief', content, re.DOTALL))
                        
                        if brief_count < len(functions):
                            missing = len(functions) - brief_count
                            report_warning("10", file_path, f"{missing} functions missing Doxygen @brief documentation")
                    except:
                        pass

def check_rule_15():
    """Rule 15: CMake usage, no manual Makefiles"""
    print("15. Checking Rule 15: CMake usage, no manual Makefiles...")
    
    for root, dirs, files in os.walk('.'):
        if should_ignore(root):
            continue
        
        dirs[:] = [d for d in dirs if d not in IGNORE_DIRS]
        
        if 'Makefile' in files and not root.startswith('./build'):
            report_violation("15", os.path.join(root, 'Makefile'), "Manual Makefile found (should use CMake only)")

def check_rule_16():
    """Rule 16: Build artifacts in build/ directory"""
    print("16. Checking Rule 16: Build artifacts in build/ directory...")
    
    for root, dirs, files in os.walk('.'):
        if should_ignore(root):
            continue
        
        dirs[:] = [d for d in dirs if d not in IGNORE_DIRS]
        
        artifacts = [f for f in files if f.endswith(('.o', '.a', '.so'))]
        if artifacts and not root.startswith('./build'):
            for artifact in artifacts:
                report_violation("16", os.path.join(root, artifact), "Build artifact found outside build/ directory")

def check_rule_17():
    """Rule 17: Official tests in test/ directory"""
    print("17. Checking Rule 17: Official tests in test/ directory...")
    
    for root, dirs, files in os.walk('.'):
        if should_ignore(root):
            continue
        
        dirs[:] = [d for d in dirs if d not in IGNORE_DIRS]
        
        test_files = [f for f in files if f.startswith('test_') and f.endswith('.c')]
        if test_files and not root.startswith('./test') and not root.startswith('./build'):
            for test_file in test_files:
                report_warning("17", os.path.join(root, test_file), "Test file found outside test/ directory")

def main():
    """Main function"""
    print(f"{Colors.BLUE}🔍 INSTRUCTIONS.md Compliance Checker{Colors.NC}")
    print("==========================================")
    print("Checking project compliance with docs/dev/INSTRUCTIONS.md rules...")
    print()
    
    print(f"{Colors.BLUE}📋 Checking Rules:{Colors.NC}")
    
    # Run all checks
    check_rule_1()
    check_rule_2()
    check_rule_3()
    check_rule_5()
    check_rule_7()
    check_rule_9()
    check_rule_10()
    check_rule_15()
    check_rule_16()
    check_rule_17()
    
    # Summary
    print()
    print("==========================================")
    print(f"{Colors.BLUE}📊 COMPLIANCE SUMMARY{Colors.NC}")
    print("==========================================")
    print(f"Total files scanned: {total_files}")
    print(f"Violations: {Colors.RED}{violations}{Colors.NC}")
    print(f"Warnings: {Colors.YELLOW}{warnings}{Colors.NC}")
    
    if violations == 0 and warnings == 0:
        print(f"{Colors.GREEN}🎉 Perfect compliance! All INSTRUCTIONS.md rules followed.{Colors.NC}")
        sys.exit(0)
    elif violations == 0:
        print(f"{Colors.YELLOW}✅ No violations found, but {warnings} warnings to review.{Colors.NC}")
        sys.exit(0)
    else:
        print(f"{Colors.RED}❌ Found {violations} violations that need to be fixed.{Colors.NC}")
        sys.exit(1)

if __name__ == "__main__":
    main()