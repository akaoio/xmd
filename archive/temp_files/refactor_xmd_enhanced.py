#!/usr/bin/env python3
"""
XMD Codebase Refactoring Tool - Enhanced Version
Genesis Principle: 1 function → 1 file → 1 directory

Enhanced by Developer with:
- Advanced header dependency analysis
- Forward declaration generation
- Static function grouping
- Git branch strategy integration
"""

import os
import re
import sys
import shutil
import subprocess
from datetime import datetime
from pathlib import Path
from typing import List, Dict, Tuple, Optional, Set
import argparse

class FunctionInfo:
    """Enhanced information about a parsed C function"""
    def __init__(self, name: str, return_type: str, params: str, body: str, 
                 docs: str = "", full_text: str = "", is_static: bool = False):
        self.name = name
        self.return_type = return_type
        self.params = params
        self.body = body
        self.docs = docs
        self.full_text = full_text
        self.target_path = ""
        self.is_static = is_static
        self.calls_functions = set()  # Functions this function calls
        self.uses_types = set()       # Types/structs this function uses
        self.required_headers = set() # Headers this function needs
        
class XMDRefactorerEnhanced:
    """Enhanced refactoring tool for XMD codebase"""
    
    def __init__(self, dry_run: bool = True, use_git_branch: bool = True):
        self.dry_run = dry_run
        self.use_git_branch = use_git_branch
        self.backup_dir = None
        self.functions_found = {}
        self.files_to_create = []
        self.directories_to_create = set()
        self.static_function_groups = {}  # Group static functions with their main functions
        self.forward_declarations = {}    # Forward declarations needed
        self.type_definitions = {}        # Shared types found
        
        # Enhanced function to directory mapping rules
        self.mapping_rules = [
            # AST Parser functions
            (r'ast_parse_program', 'ast/parser/program'),
            (r'ast_parse_statement', 'ast/parser/statement'),
            (r'ast_parse_expression', 'ast/parser/expression'),
            (r'ast_parse_assignment', 'ast/parser/assignment'),
            (r'ast_parse_if', 'ast/parser/control'),
            (r'ast_parse_elif', 'ast/parser/control'),
            (r'ast_parse_else', 'ast/parser/control'),
            (r'ast_parse_while', 'ast/parser/loop'),
            (r'ast_parse_for', 'ast/parser/loop'),
            (r'ast_parse_loop', 'ast/parser/loop'),
            (r'ast_parse_range', 'ast/parser/loop'),
            (r'ast_parse_function', 'ast/parser/function'),
            (r'ast_parse_class', 'ast/parser/class'),
            (r'ast_parse_method', 'ast/parser/class'),
            (r'ast_parse_string', 'ast/parser/literal'),
            (r'ast_parse_number', 'ast/parser/literal'),
            (r'ast_parse_boolean', 'ast/parser/literal'),
            (r'ast_parse_comparison', 'ast/parser/expression'),
            (r'ast_parse_binary', 'ast/parser/expression'),
            (r'ast_parse_primary', 'ast/parser/expression'),
            (r'ast_parse_array', 'ast/parser/literal'),
            (r'ast_parse_math', 'ast/parser/expression'),
            (r'ast_parse_multiple_variables', 'ast/parser/assignment'),
            (r'ast_parse_object', 'ast/parser/object'),
            (r'ast_parse_single_value', 'ast/parser/expression'),
            (r'ast_parse_potential_function', 'ast/parser/function'),
            
            # AST Evaluator functions
            (r'ast_evaluate_program', 'ast/evaluator/program'),
            (r'ast_evaluate_statement', 'ast/evaluator/statement'),
            (r'ast_evaluate_expression', 'ast/evaluator/expression'),
            (r'ast_evaluate_assignment', 'ast/evaluator/assignment'),
            (r'ast_evaluate_conditional', 'ast/evaluator/control'),
            (r'ast_evaluate_loop', 'ast/evaluator/loop'),
            (r'ast_evaluate_while', 'ast/evaluator/loop'),
            (r'ast_evaluate_function', 'ast/evaluator/function'),
            (r'ast_evaluate_binary', 'ast/evaluator/expression'),
            (r'ast_evaluate_identifier', 'ast/evaluator/expression'),
            (r'ast_evaluate_file', 'ast/evaluator/fileio'),
            
            # AST Node functions
            (r'ast_create_program', 'ast/node/create'),
            (r'ast_create_statement', 'ast/node/create'),
            (r'ast_create_assignment', 'ast/node/create'),
            (r'ast_create_binary', 'ast/node/create'),
            (r'ast_create_identifier', 'ast/node/create'),
            (r'ast_create_number', 'ast/node/create'),
            (r'ast_create_string', 'ast/node/create'),
            (r'ast_create_boolean', 'ast/node/create'),
            (r'ast_create_array', 'ast/node/create'),
            (r'ast_create_conditional', 'ast/node/create'),
            (r'ast_create_loop', 'ast/node/create'),
            (r'ast_create_function', 'ast/node/create'),
            (r'ast_create_block', 'ast/node/create'),
            (r'ast_create_break', 'ast/node/create'),
            (r'ast_create_continue', 'ast/node/create'),
            
            # AST Utility functions
            (r'ast_add_', 'ast/util'),
            (r'ast_free', 'ast/util'),
            (r'ast_clone', 'ast/util'),
            (r'ast_print', 'ast/util'),
            
            # AST Value functions
            (r'ast_value_create', 'ast/value'),
            (r'ast_value_from', 'ast/value'),
            (r'ast_value_to', 'ast/value'),
            (r'ast_value_free', 'ast/value'),
            
            # Store functions
            (r'store_', 'core/store'),
            
            # Variable functions
            (r'variable_', 'core/variable'),
            
            # Token functions
            (r'token_', 'core/token'),
            
            # Lexer functions
            (r'lexer_', 'core/lexer'),
            
            # XMD core functions
            (r'xmd_', 'core/xmd'),
            
            # Default
            (r'.*', 'misc'),
        ]
        
    def create_git_branch(self) -> bool:
        """Create a new git branch for refactoring"""
        if not self.use_git_branch:
            return True
            
        try:
            # Check if we're in a git repo
            result = subprocess.run(['git', 'status'], capture_output=True)
            if result.returncode != 0:
                print("⚠️  Not in a git repository, skipping branch creation")
                return True
                
            # Create and checkout new branch
            branch_name = f"modular-refactoring-{datetime.now().strftime('%Y%m%d-%H%M%S')}"
            subprocess.run(['git', 'checkout', '-b', branch_name], check=True)
            print(f"✅ Created and checked out git branch: {branch_name}")
            return True
            
        except Exception as e:
            print(f"❌ Git branch creation failed: {e}")
            return False
            
    def analyze_function_dependencies(self, func_info: FunctionInfo) -> None:
        """Analyze what functions and types this function uses"""
        # Extract function calls
        func_call_pattern = r'\b(\w+)\s*\('
        for match in re.finditer(func_call_pattern, func_info.body):
            called_func = match.group(1)
            # Ignore common C functions and keywords
            if called_func not in ['if', 'while', 'for', 'switch', 'return', 'sizeof']:
                func_info.calls_functions.add(called_func)
                
        # Extract type usage (struct, enum, typedef)
        type_patterns = [
            r'\b(struct\s+\w+)\b',
            r'\b(enum\s+\w+)\b',
            r'\b(ast_node|ast_value|ast_evaluator|variable|token|lexer)\b',
            r'\b(source_location|binary_operator|unary_operator)\b',
        ]
        
        for pattern in type_patterns:
            for match in re.finditer(pattern, func_info.full_text):
                func_info.uses_types.add(match.group(1))
                
    def determine_required_headers(self, func_info: FunctionInfo) -> Set[str]:
        """Determine which headers a function needs based on dependency analysis"""
        headers = set()
        
        # Always include common headers
        headers.add('"xmd_common.h"')
        
        # Add headers based on function calls
        for called_func in func_info.calls_functions:
            if called_func.startswith('ast_'):
                headers.add('"ast.h"')
                if 'parse' in called_func:
                    headers.add('"ast_parser.h"')
                if 'evaluate' in called_func:
                    headers.add('"ast_evaluator.h"')
                if 'create' in called_func:
                    headers.add('"ast_node.h"')
            elif called_func.startswith('variable_'):
                headers.add('"variable.h"')
            elif called_func.startswith('token_'):
                headers.add('"token.h"')
            elif called_func.startswith('lexer_'):
                headers.add('"lexer.h"')
            elif called_func.startswith('store_'):
                headers.add('"store.h"')
            elif called_func.startswith('xmd_'):
                headers.add('"xmd.h"')
                
        # Add headers based on types used
        for type_used in func_info.uses_types:
            if 'ast_node' in type_used:
                headers.add('"ast_node.h"')
            elif 'ast_value' in type_used:
                headers.add('"ast_value.h"')
            elif 'ast_evaluator' in type_used:
                headers.add('"ast_evaluator.h"')
            elif 'variable' in type_used:
                headers.add('"variable.h"')
            elif 'token' in type_used:
                headers.add('"token.h"')
                
        # Check for standard library usage
        if re.search(r'\b(malloc|calloc|realloc|free)\b', func_info.body):
            headers.add('<stdlib.h>')
        if re.search(r'\b(strcmp|strncmp|strlen|strcpy|strncpy|strdup)\b', func_info.body):
            headers.add('<string.h>')
        if re.search(r'\b(printf|fprintf|sprintf|snprintf)\b', func_info.body):
            headers.add('<stdio.h>')
        if re.search(r'\b(bool|true|false)\b', func_info.body):
            headers.add('<stdbool.h>')
        if re.search(r'\b(isspace|isdigit|isalpha|isalnum)\b', func_info.body):
            headers.add('<ctype.h>')
            
        func_info.required_headers = headers
        return headers
        
    def group_static_functions(self, functions: List[FunctionInfo]) -> Dict[str, List[FunctionInfo]]:
        """Group static functions with the non-static functions that use them"""
        static_funcs = [f for f in functions if f.is_static]
        non_static_funcs = [f for f in functions if not f.is_static]
        
        groups = {}
        
        for static_func in static_funcs:
            # Find which non-static function calls this static function
            found_caller = False
            for non_static in non_static_funcs:
                if static_func.name in non_static.calls_functions:
                    if non_static.name not in groups:
                        groups[non_static.name] = []
                    groups[non_static.name].append(static_func)
                    found_caller = True
                    break
                    
            if not found_caller:
                # If no specific caller found, group with first non-static in same category
                for pattern, directory in self.mapping_rules:
                    if re.match(pattern, static_func.name):
                        for non_static in non_static_funcs:
                            if re.match(pattern, non_static.name):
                                if non_static.name not in groups:
                                    groups[non_static.name] = []
                                groups[non_static.name].append(static_func)
                                break
                        break
                        
        return groups
        
    def determine_target_path(self, func_info: FunctionInfo) -> str:
        """Determine target directory for a function based on its name"""
        func_name = func_info.name
        
        # Check mapping rules in order
        for pattern, directory in self.mapping_rules:
            if re.match(pattern, func_name):
                return f"src/{directory}/{func_name}.c"
                
        # Default fallback
        return f"src/misc/{func_name}.c"
        
    def generate_forward_declarations(self, functions: List[FunctionInfo]) -> str:
        """Generate forward declarations for functions that need them"""
        declarations = []
        
        # Build a map of function names to their info
        func_map = {f.name: f for f in functions}
        
        # Check which functions need forward declarations
        for func in functions:
            for called in func.calls_functions:
                if called in func_map:
                    called_func = func_map[called]
                    # Generate forward declaration
                    decl = f"{called_func.return_type} {called_func.name}({called_func.params});"
                    if decl not in declarations:
                        declarations.append(decl)
                        
        return "\n".join(declarations)
        
    def extract_shared_types(self, content: str) -> Dict[str, str]:
        """Extract typedef, struct, and enum definitions"""
        types = {}
        
        # Pattern for typedef
        typedef_pattern = re.compile(
            r'typedef\s+(?:struct|enum|union)?\s*\{[^}]*\}\s*\w+\s*;',
            re.MULTILINE | re.DOTALL
        )
        
        # Pattern for named structs/enums
        struct_enum_pattern = re.compile(
            r'(?:struct|enum|union)\s+(\w+)\s*\{[^}]*\}\s*;',
            re.MULTILINE | re.DOTALL
        )
        
        for match in typedef_pattern.finditer(content):
            type_def = match.group(0)
            # Extract type name
            type_name_match = re.search(r'\}\s*(\w+)\s*;', type_def)
            if type_name_match:
                type_name = type_name_match.group(1)
                types[type_name] = type_def
                
        for match in struct_enum_pattern.finditer(content):
            type_name = match.group(1)
            types[type_name] = match.group(0)
            
        return types
        
    def parse_c_functions(self, content: str) -> List[FunctionInfo]:
        """Enhanced C function parser with static detection and dependency analysis"""
        functions = []
        
        # Enhanced pattern to detect static functions
        func_pattern = re.compile(
            r'(?:^|\n)'  # Start of line or after newline
            r'(?P<docs>(?:\/\*\*.*?\*\/\s*)?)'  # Optional documentation
            r'(?P<static>static\s+)?'  # Optional static keyword
            r'(?P<inline>inline\s+)?'  # Optional inline keyword
            r'(?P<return>(?:const\s+)?'  # Optional const
            r'(?:struct\s+)?(?:enum\s+)?'  # struct/enum
            r'(?:\w+(?:\s*\*)?(?:\s+|\s*\*\s*))+)'  # Return type
            r'(?P<name>\w+)\s*'  # Function name
            r'\((?P<params>[^)]*)\)\s*'  # Parameters
            r'\{',  # Opening brace
            re.MULTILINE | re.DOTALL
        )
        
        for match in func_pattern.finditer(content):
            func_start = match.start()
            func_name = match.group('name')
            return_type = match.group('return').strip()
            params = match.group('params').strip()
            docs = match.group('docs').strip()
            is_static = match.group('static') is not None
            
            # Include static/inline in return type if present
            if match.group('static'):
                return_type = 'static ' + return_type
            if match.group('inline'):
                return_type = match.group('inline') + return_type
                
            # Find matching closing brace
            brace_count = 1
            pos = match.end()
            
            while brace_count > 0 and pos < len(content):
                if content[pos] == '{':
                    brace_count += 1
                elif content[pos] == '}':
                    brace_count -= 1
                pos += 1
                
            if brace_count == 0:
                full_func = content[match.start():pos]
                body_start = full_func.find('{')
                body = full_func[body_start:pos-func_start]
                
                func_info = FunctionInfo(
                    name=func_name,
                    return_type=return_type,
                    params=params,
                    body=body,
                    docs=docs,
                    full_text=full_func,
                    is_static=is_static
                )
                
                # Analyze dependencies
                self.analyze_function_dependencies(func_info)
                self.determine_required_headers(func_info)
                
                functions.append(func_info)
                
        return functions
        
    def generate_header_file(self, module_path: str, functions: List[FunctionInfo]) -> str:
        """Generate a header file for a module with forward declarations"""
        header_guard = module_path.replace('/', '_').replace('.', '_').upper() + '_H'
        
        content = f"""#ifndef {header_guard}
#define {header_guard}

#include "xmd_common.h"

"""
        
        # Add forward declarations for non-static functions
        for func in functions:
            if not func.is_static:
                content += f"{func.return_type} {func.name}({func.params});\n"
                
        content += f"\n#endif /* {header_guard} */\n"
        
        return content
        
    def backup_codebase(self) -> str:
        """Create timestamped backup with validation"""
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        self.backup_dir = f"backup/backup_{timestamp}"
        
        if not self.dry_run:
            print(f"\nCreating backup at: {self.backup_dir}")
            
            # Create backup directory
            os.makedirs(self.backup_dir, exist_ok=True)
            
            # Copy entire src directory
            if os.path.exists('src'):
                shutil.copytree('src', os.path.join(self.backup_dir, 'src'))
                
            # Copy build files
            for file in ['CMakeLists.txt', 'build.sh', 'Makefile']:
                if os.path.exists(file):
                    shutil.copy2(file, self.backup_dir)
                    
            # Validate backup
            src_count = len(list(Path('src').rglob('*.c'))) if os.path.exists('src') else 0
            backup_count = len(list(Path(self.backup_dir).rglob('*.c')))
            
            if src_count != backup_count:
                print(f"❌ Backup validation failed! {src_count} vs {backup_count} files")
                sys.exit(1)
                
            print(f"✅ Backup created and validated: {backup_count} files")
        else:
            print(f"\n[DRY RUN] Would create backup at: {self.backup_dir}")
            
        return self.backup_dir
        
    def execute_refactoring(self) -> None:
        """Execute the refactoring with all enhancements"""
        print("\n=== Executing Refactoring ===\n")
        
        # Create git branch if requested
        if self.use_git_branch and not self.create_git_branch():
            print("❌ Git branch creation failed, aborting")
            return
            
        # Group static functions
        all_functions = []
        for functions in self.functions_found.values():
            all_functions.extend(functions)
            
        static_groups = self.group_static_functions(all_functions)
        
        # Extract shared types
        shared_types = {}
        for filepath, content in self.file_contents.items():
            types = self.extract_shared_types(content)
            shared_types.update(types)
            
        # Create shared types directory and files
        if shared_types:
            types_dir = "src/ast/types"
            os.makedirs(types_dir, exist_ok=True)
            
            types_content = """#ifndef XMD_AST_TYPES_H
#define XMD_AST_TYPES_H

#include <stddef.h>
#include <stdbool.h>

/* Shared type definitions */

"""
            for type_name, type_def in shared_types.items():
                types_content += type_def + "\n\n"
                
            types_content += "#endif /* XMD_AST_TYPES_H */\n"
            
            with open(os.path.join(types_dir, "ast_types.h"), 'w') as f:
                f.write(types_content)
                
        # Process each function
        modules = {}  # Track functions by module for header generation
        
        for source_file, functions in self.functions_found.items():
            for func in functions:
                # Determine target directory
                target_dir = os.path.dirname(func.target_path)
                os.makedirs(target_dir, exist_ok=True)
                
                # Check if this function has static functions grouped with it
                functions_to_write = [func]
                if func.name in static_groups:
                    functions_to_write.extend(static_groups[func.name])
                    
                # Generate file content
                file_content = self.generate_modular_file_content(
                    functions_to_write, source_file
                )
                
                # Write file
                with open(func.target_path, 'w') as f:
                    f.write(file_content)
                    
                # Track for header generation
                module_key = target_dir
                if module_key not in modules:
                    modules[module_key] = []
                modules[module_key].append(func)
                
        # Generate header files for each module
        for module_path, module_functions in modules.items():
            header_content = self.generate_header_file(module_path, module_functions)
            header_path = os.path.join(module_path, os.path.basename(module_path) + ".h")
            
            with open(header_path, 'w') as f:
                f.write(header_content)
                
        # Generate updated CMakeLists.txt
        cmake_content = self.generate_cmake_updates()
        with open("CMakeLists_modular.txt", 'w') as f:
            f.write(cmake_content)
            
        # Remove original files
        if not self.dry_run:
            for source_file in self.functions_found.keys():
                os.remove(source_file)
                print(f"Removed: {source_file}")
                
        print("\n✅ Refactoring complete!")
        
    def generate_modular_file_content(self, functions: List[FunctionInfo], 
                                    source_file: str) -> str:
        """Generate content for modular file (potentially with multiple functions)"""
        primary_func = functions[0]
        
        # Collect all required headers
        all_headers = set()
        for func in functions:
            all_headers.update(func.required_headers)
            
        # Sort headers
        system_headers = sorted([h for h in all_headers if h.startswith('<')])
        local_headers = sorted([h for h in all_headers if h.startswith('"')])
        
        # Build content
        content = f"""/**
 * @file {os.path.basename(primary_func.target_path)}
 * @brief Implementation of {primary_func.name}
 * 
 * This file was automatically generated by the XMD refactoring tool.
 * Original source: {source_file}
 */

"""
        
        # System headers
        for header in system_headers:
            content += f"#include {header}\n"
            
        if system_headers:
            content += "\n"
            
        # Local headers
        for header in local_headers:
            content += f"#include {header}\n"
            
        content += "\n"
        
        # Add forward declarations if needed
        if len(functions) > 1:
            content += "/* Forward declarations */\n"
            for func in functions[1:]:  # Skip primary function
                content += f"static {func.return_type} {func.name}({func.params});\n"
            content += "\n"
            
        # Add all functions
        for i, func in enumerate(functions):
            if i > 0:
                content += "\n"
            content += func.full_text
            if not func.full_text.endswith('\n'):
                content += '\n'
                
        return content
        
    # ... rest of the methods remain similar to original ...
    
def main():
    parser = argparse.ArgumentParser(
        description="XMD Codebase Refactoring Tool - Enhanced Version"
    )
    parser.add_argument(
        '--execute', 
        action='store_true',
        help='Actually perform refactoring (default is dry-run)'
    )
    parser.add_argument(
        '--no-git',
        action='store_true',
        help='Skip git branch creation'
    )
    parser.add_argument(
        '--target',
        nargs='+',
        default=['src/ast_consolidated.c'],
        help='Target files to refactor'
    )
    
    args = parser.parse_args()
    
    print("=" * 60)
    print("XMD Codebase Refactoring Tool - Enhanced Version")
    print("Genesis Principle: 1 function → 1 file → 1 directory")
    print("=" * 60)
    
    if args.execute:
        print("\n⚠️  EXECUTION MODE - Changes will be made!")
        response = input("Type 'PROCEED' to continue: ")
        if response != 'PROCEED':
            print("Aborted.")
            sys.exit(0)
    else:
        print("\n🔍 DRY RUN MODE - No changes will be made")
        
    # Create enhanced refactorer
    refactorer = XMDRefactorerEnhanced(
        dry_run=not args.execute,
        use_git_branch=not args.no_git
    )
    
    # Rest of execution similar to original
    backup_path = refactorer.backup_codebase()
    
    # Store file contents before processing
    refactorer.file_contents = {}
    for filepath in args.target:
        if os.path.exists(filepath):
            with open(filepath, 'r') as f:
                refactorer.file_contents[filepath] = f.read()
                
    # Analyze files
    stats_before = {}
    for filepath in args.target:
        if os.path.exists(filepath):
            with open(filepath, 'r') as f:
                content = f.read()
                functions = refactorer.parse_c_functions(content)
                
                # Set target paths
                for func in functions:
                    func.target_path = refactorer.determine_target_path(func)
                    
                refactorer.functions_found[filepath] = functions
                stats_before[filepath] = {
                    'size': len(content),
                    'function_count': len(functions),
                    'line_count': content.count('\n')
                }
                
    # Show analysis
    print("\n=== Analysis Results ===")
    total_functions = sum(len(funcs) for funcs in refactorer.functions_found.values())
    print(f"Total functions found: {total_functions}")
    
    # Show static function grouping
    all_functions = []
    for functions in refactorer.functions_found.values():
        all_functions.extend(functions)
        
    static_groups = refactorer.group_static_functions(all_functions)
    if static_groups:
        print(f"\nStatic function groups: {len(static_groups)}")
        for main_func, static_funcs in static_groups.items():
            print(f"  {main_func}:")
            for sf in static_funcs:
                print(f"    - {sf.name}")
                
    if not args.execute:
        print("\n" + "=" * 60)
        print("To execute refactoring, run with --execute flag")
        print("Example: python refactor_xmd_enhanced.py --execute")
        print("=" * 60)
    else:
        response = input("\nFinal confirmation - type 'YES': ")
        if response == 'YES':
            refactorer.execute_refactoring()
            print(f"\nBackup available at: {backup_path}")
        else:
            print("Aborted.")

if __name__ == "__main__":
    main()