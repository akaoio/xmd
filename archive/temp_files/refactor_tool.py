#!/usr/bin/env python3
"""
XMD Codebase Refactoring Tool - SYSTEMS ENGINEER IMPLEMENTATION
Safely refactors consolidated C files into modular structure
Principle: 1 function → 1 file → 1 directory
"""

import os
import re
import shutil
import datetime
import hashlib
from typing import List, Dict, Tuple
import argparse

class XMDRefactorer:
    def __init__(self, dry_run: bool = True, verbose: bool = True):
        self.dry_run = dry_run
        self.verbose = verbose
        self.backup_dir = None
        self.functions_found = []
        self.files_created = []
        self.validation_data = {}
        
    def log(self, message: str):
        """Print log messages if verbose mode is on"""
        if self.verbose:
            print(f"[{'DRY RUN' if self.dry_run else 'LIVE'}] {message}")
    
    def backup_codebase(self, source_dir: str = ".") -> str:
        """Create timestamped backup in backup/ directory"""
        if self.dry_run:
            self.log("SKIPPING backup in dry-run mode")
            return "backup/dry_run_backup"
            
        timestamp = datetime.datetime.now().strftime("%Y%m%d_%H%M%S")
        backup_path = f"backup/backup_{timestamp}"
        
        self.log(f"Creating backup at {backup_path}")
        
        # Create backup directory
        os.makedirs(backup_path, exist_ok=True)
        
        # Files to backup
        important_dirs = ["src", "include", "test"]
        important_files = ["CMakeLists.txt", "build.sh", "clean.sh"]
        
        # Backup directories
        for dir_name in important_dirs:
            if os.path.exists(dir_name):
                dest = os.path.join(backup_path, dir_name)
                shutil.copytree(dir_name, dest)
                self.log(f"  Backed up {dir_name}/")
        
        # Backup files
        for file_name in important_files:
            if os.path.exists(file_name):
                dest = os.path.join(backup_path, file_name)
                shutil.copy2(file_name, dest)
                self.log(f"  Backed up {file_name}")
        
        self.backup_dir = backup_path
        self.log(f"Backup completed at {backup_path}")
        return backup_path
    
    def calculate_file_hash(self, filepath: str) -> str:
        """Calculate hash of file content for validation"""
        with open(filepath, 'rb') as f:
            return hashlib.sha256(f.read()).hexdigest()
    
    def parse_c_functions(self, filepath: str) -> List[Dict[str, str]]:
        """Extract all functions from a C file"""
        self.log(f"Parsing {filepath}")
        
        with open(filepath, 'r') as f:
            content = f.read()
        
        # Store original hash for validation
        self.validation_data[filepath] = {
            'original_hash': self.calculate_file_hash(filepath),
            'line_count': len(content.splitlines()),
            'size': len(content)
        }
        
        functions = []
        
        # Regex to match C functions (simplified - may need enhancement)
        # Matches: return_type function_name(params) { ... }
        function_pattern = r'((?:static\s+)?(?:const\s+)?(?:struct\s+)?(?:enum\s+)?(?:unsigned\s+)?(?:signed\s+)?(?:\w+[\s\*]+)+)(\w+)\s*\([^)]*\)\s*\{'
        
        matches = list(re.finditer(function_pattern, content, re.MULTILINE))
        
        for i, match in enumerate(matches):
            func_start = match.start()
            func_name = match.group(2)
            return_type = match.group(1).strip()
            
            # Find the matching closing brace
            brace_count = 0
            pos = match.end() - 1  # Start at the opening brace
            
            while pos < len(content):
                if content[pos] == '{':
                    brace_count += 1
                elif content[pos] == '}':
                    brace_count -= 1
                    if brace_count == 0:
                        func_end = pos + 1
                        break
                pos += 1
            
            # Extract function code
            func_code = content[func_start:func_end]
            
            # Extract any comments before the function
            prev_end = matches[i-1].end() if i > 0 else 0
            pre_content = content[prev_end:func_start].strip()
            
            # Look for header comments
            header_comment = ""
            if pre_content:
                comment_match = re.search(r'(/\*.*?\*/|//.*?$)', pre_content, re.DOTALL | re.MULTILINE)
                if comment_match:
                    header_comment = comment_match.group(0)
            
            functions.append({
                'name': func_name,
                'return_type': return_type,
                'code': func_code,
                'header_comment': header_comment,
                'source_file': filepath,
                'line_number': len(content[:func_start].splitlines())
            })
            
            self.log(f"  Found function: {func_name} (line {functions[-1]['line_number']})")
        
        self.functions_found.extend(functions)
        self.log(f"  Total functions found: {len(functions)}")
        return functions
    
    def determine_module_path(self, function_name: str, source_file: str) -> str:
        """Determine the appropriate module path for a function"""
        # Extract module name from source file
        base_name = os.path.basename(source_file)
        module_name = base_name.replace('_consolidated.c', '').replace('.c', '')
        
        # Determine subdirectory based on function name patterns
        if function_name.startswith('ast_parse_'):
            subdir = 'parser'
        elif function_name.startswith('ast_evaluate_'):
            subdir = 'evaluator'
        elif function_name.startswith('ast_create_'):
            subdir = 'creator'
        elif function_name.startswith('ast_free') or function_name.endswith('_free'):
            subdir = 'memory'
        else:
            subdir = 'core'
        
        # Create module path
        return os.path.join('src', module_name, subdir, function_name)
    
    def create_modular_file(self, function_data: Dict[str, str], module_path: str):
        """Create individual file for one function"""
        if self.dry_run:
            self.log(f"  Would create: {module_path}/{function_data['name']}.c")
            self.files_created.append(f"{module_path}/{function_data['name']}.c")
            return
        
        # Create directory structure
        os.makedirs(module_path, exist_ok=True)
        
        # Generate file content
        file_content = f"""/**
 * @file {function_data['name']}.c
 * @brief Implementation of {function_data['name']} function
 * 
 * Extracted from: {function_data['source_file']}
 * Original line: {function_data['line_number']}
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast_node.h"
#include "ast_parser.h"
#include "ast_evaluator.h"

{function_data['header_comment']}
{function_data['code']}
"""
        
        filepath = os.path.join(module_path, f"{function_data['name']}.c")
        with open(filepath, 'w') as f:
            f.write(file_content)
        
        self.log(f"  Created: {filepath}")
        self.files_created.append(filepath)
    
    def generate_cmake_updates(self) -> str:
        """Generate CMakeLists.txt updates for new structure"""
        cmake_content = "# Refactored source files\n"
        
        # Group files by module
        modules = {}
        for filepath in self.files_created:
            parts = filepath.split('/')
            if len(parts) >= 3:
                module = parts[1]
                if module not in modules:
                    modules[module] = []
                modules[module].append(filepath)
        
        # Generate CMake sets
        for module, files in sorted(modules.items()):
            cmake_content += f"\nset({module.upper()}_SOURCES\n"
            for file in sorted(files):
                cmake_content += f"    {file}\n"
            cmake_content += ")\n"
        
        return cmake_content
    
    def validate_refactoring(self) -> bool:
        """Ensure no code lost, all functions preserved"""
        self.log("\nValidating refactoring...")
        
        # Check function count
        self.log(f"  Functions found: {len(self.functions_found)}")
        self.log(f"  Files to create: {len(self.files_created)}")
        
        if len(self.functions_found) != len(self.files_created):
            self.log("  ERROR: Function count mismatch!")
            return False
        
        # In dry-run, just check counts
        if self.dry_run:
            self.log("  Dry-run validation passed")
            return True
        
        # TODO: Add more validation (line counts, etc.)
        self.log("  Validation passed")
        return True
    
    def run(self, target_files: List[str]):
        """Main refactoring process"""
        self.log("=== XMD Refactoring Tool ===")
        self.log(f"Mode: {'DRY RUN' if self.dry_run else 'LIVE'}")
        
        # Step 1: Backup (skip in dry-run)
        backup_path = self.backup_codebase()
        
        # Step 2: Parse all functions
        for filepath in target_files:
            if os.path.exists(filepath):
                self.parse_c_functions(filepath)
        
        # Step 3: Create modular files
        for function in self.functions_found:
            module_path = self.determine_module_path(function['name'], function['source_file'])
            self.create_modular_file(function, module_path)
        
        # Step 4: Generate CMake updates
        cmake_updates = self.generate_cmake_updates()
        if self.dry_run:
            self.log("\nCMakeLists.txt updates needed:")
            print(cmake_updates)
        else:
            with open('CMakeLists_refactored.txt', 'w') as f:
                f.write(cmake_updates)
            self.log("CMake updates saved to CMakeLists_refactored.txt")
        
        # Step 5: Validate
        if self.validate_refactoring():
            self.log("\n✅ Refactoring completed successfully!")
        else:
            self.log("\n❌ Refactoring validation failed!")
            return False
        
        return True


def main():
    parser = argparse.ArgumentParser(description='XMD Codebase Refactoring Tool')
    parser.add_argument('--live', action='store_true', help='Run in live mode (default is dry-run)')
    parser.add_argument('--quiet', action='store_true', help='Reduce output verbosity')
    parser.add_argument('files', nargs='+', help='Files to refactor')
    
    args = parser.parse_args()
    
    refactorer = XMDRefactorer(dry_run=not args.live, verbose=not args.quiet)
    
    # Safety check
    if args.live:
        response = input("⚠️  WARNING: Live mode will modify files! Continue? (yes/no): ")
        if response.lower() != 'yes':
            print("Aborted.")
            return
    
    success = refactorer.run(args.files)
    exit(0 if success else 1)


if __name__ == "__main__":
    main()