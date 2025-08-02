#!/usr/bin/env python3
"""
XMD Codebase Refactoring Tool
Genesis Principle: 1 function → 1 file → 1 directory

This tool safely refactors monolithic C files into modular structure.
Always runs in dry-run mode by default. Requires explicit confirmation.
"""

import os
import re
import sys
import shutil
from datetime import datetime
from pathlib import Path
from typing import List, Dict, Tuple, Optional
import argparse

class FunctionInfo:
    """Information about a parsed C function"""
    def __init__(self, name: str, return_type: str, params: str, body: str, 
                 docs: str = "", full_text: str = ""):
        self.name = name
        self.return_type = return_type
        self.params = params
        self.body = body
        self.docs = docs
        self.full_text = full_text
        self.target_path = ""
        
class XMDRefactorer:
    """Main refactoring tool for XMD codebase"""
    
    def __init__(self, dry_run: bool = True):
        self.dry_run = dry_run
        self.backup_dir = None
        self.functions_found = {}
        self.files_to_create = []
        self.directories_to_create = set()
        self.header_declarations = {}  # Maps function name to header file
        self.header_updates = {}       # Updates needed for header files
        self.type_definitions = {}     # Maps type names to their definitions
        self.include_dependencies = {} # Maps functions to required includes
        
        # Function to directory mapping rules
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
            
            # AST Value functions
            (r'ast_value_create', 'ast/value'),
            (r'ast_value_from', 'ast/value'),
            (r'ast_value_to', 'ast/value'),
            (r'ast_value_free', 'ast/value'),
            
            # AST utility functions
            (r'ast_free', 'ast/node/free'),
            (r'ast_add', 'ast/node/util'),
            (r'ast_process', 'ast/processor'),
            
            # Variable functions
            (r'variable_create', 'variable/create'),
            (r'variable_copy', 'variable/operations'),
            (r'variable_equals', 'variable/operations'),
            (r'variable_to', 'variable/operations'),
            (r'variable_get', 'variable/operations'),
            (r'variable_set', 'variable/operations'),
            (r'variable_ref', 'variable/memory'),
            (r'variable_unref', 'variable/memory'),
            (r'variable_array', 'variable/array'),
            (r'variable_object', 'variable/object'),
            (r'variable_new', 'variable/create'),
            
            # Lexer functions
            (r'lexer_create', 'lexer/core'),
            (r'lexer_advance', 'lexer/core'),
            (r'lexer_free', 'lexer/core'),
            (r'lexer_next', 'lexer/token'),
            (r'lexer_peek', 'lexer/token'),
            (r'lexer_read', 'lexer/read'),
            (r'lexer_skip', 'lexer/util'),
            (r'lexer_at', 'lexer/util'),
            (r'lexer_get', 'lexer/util'),
            
            # Token functions
            (r'token_create', 'token/create'),
            (r'token_free', 'token/memory'),
            (r'token_duplicate', 'token/operations'),
            (r'token_copy', 'token/operations'),
            (r'token_set', 'token/operations'),
            (r'token_get', 'token/operations'),
            (r'token_equals', 'token/operations'),
            (r'token_to', 'token/convert'),
            (r'token_type', 'token/type'),
            (r'token_list', 'token/list'),
            
            # Store functions
            (r'store_create', 'store/create'),
            (r'store_destroy', 'store/memory'),
            (r'store_get', 'store/operations'),
            (r'store_set', 'store/operations'),
            (r'store_has', 'store/operations'),
            (r'store_remove', 'store/operations'),
            (r'store_keys', 'store/operations'),
            (r'store_size', 'store/operations'),
            (r'store_clear', 'store/operations'),
            (r'store_entry', 'store/entry'),
            
            # Platform functions
            (r'xmd_', 'platform'),
            
            # Config functions
            (r'config_', 'config'),
            (r'xmd_internal_config', 'config/internal'),
            
            # Utils functions
            (r'memory_', 'utils/memory'),
            (r'string_', 'utils/string'),
            
            # Default for unmatched functions
            (r'.*', 'misc'),
        ]
        
    def create_git_branch(self) -> bool:
        """Create a git branch for safer refactoring"""
        if self.dry_run:
            print("Would create git branch: modular-refactoring")
            return True
            
        try:
            # Check if we're in a git repo
            result = os.system("git rev-parse --git-dir > /dev/null 2>&1")
            if result != 0:
                print("WARNING: Not in a git repository. Using file backup only.")
                return False
                
            # Create and checkout new branch
            timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
            branch_name = f"modular-refactoring-{timestamp}"
            
            print(f"Creating git branch: {branch_name}")
            os.system(f"git checkout -b {branch_name}")
            
            return True
        except Exception as e:
            print(f"WARNING: Could not create git branch: {e}")
            return False
            
    def backup_codebase(self) -> str:
        """Create timestamped backup of entire codebase"""
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        backup_path = f"backup/backup_{timestamp}"
        
        # Try git branch first
        self.create_git_branch()
        
        print(f"Creating file backup at {backup_path}...")
        
        if not self.dry_run:
            os.makedirs(backup_path, exist_ok=True)
            
            # Backup key directories
            for dir_name in ['src', 'include', 'test']:
                if os.path.exists(dir_name):
                    shutil.copytree(dir_name, f"{backup_path}/{dir_name}")
                    
            # Backup key files
            for file_name in ['CMakeLists.txt', 'build.sh', 'clean.sh']:
                if os.path.exists(file_name):
                    shutil.copy2(file_name, backup_path)
                    
        self.backup_dir = backup_path
        return backup_path
        
    def parse_header_declarations(self, header_path: str) -> Dict[str, str]:
        """Parse function declarations from header files"""
        declarations = {}
        
        if not os.path.exists(header_path):
            return declarations
            
        with open(header_path, 'r') as f:
            content = f.read()
            
        # Pattern to match function declarations in headers
        # Handles return types with *, const, etc.
        decl_pattern = re.compile(
            r'(?:^|\n)'  # Start of line
            r'(?!#|typedef|struct|enum)'  # Skip preprocessor and type definitions
            r'((?:static\s+)?(?:inline\s+)?(?:const\s+)?'  # Modifiers
            r'(?:struct\s+)?(?:enum\s+)?'  # struct/enum
            r'(?:\w+(?:\s*\*)?(?:\s+|\s*\*\s*))+)'  # Return type
            r'(\w+)\s*'  # Function name
            r'\([^)]*\)\s*;',  # Parameters and semicolon
            re.MULTILINE
        )
        
        for match in decl_pattern.finditer(content):
            func_name = match.group(2)
            full_decl = match.group(0).strip()
            declarations[func_name] = full_decl
            
        return declarations
        
    def extract_type_definitions(self, header_path: str) -> None:
        """Extract typedef, struct, and enum definitions from header"""
        with open(header_path, 'r') as f:
            content = f.read()
            
        # Extract typedefs
        typedef_pattern = re.compile(
            r'typedef\s+(struct|enum|union)?\s*\{[^}]+\}\s*(\w+)\s*;|'
            r'typedef\s+[^;]+\s+(\w+)\s*;',
            re.MULTILINE | re.DOTALL
        )
        
        for match in typedef_pattern.finditer(content):
            if match.group(2):  # struct/enum/union typedef
                type_name = match.group(2)
            else:  # simple typedef
                type_name = match.group(3)
            
            if type_name:
                self.type_definitions[type_name] = {
                    'definition': match.group(0),
                    'header': os.path.basename(header_path)
                }
                
        # Extract forward struct declarations
        struct_pattern = re.compile(
            r'(?:typedef\s+)?struct\s+(\w+)\s*;',
            re.MULTILINE
        )
        
        for match in struct_pattern.finditer(content):
            type_name = match.group(1)
            if type_name and type_name not in self.type_definitions:
                self.type_definitions[type_name] = {
                    'definition': match.group(0),
                    'header': os.path.basename(header_path),
                    'forward': True
                }
        
    def scan_all_headers(self) -> None:
        """Scan all header files to build declaration map and extract types"""
        include_dir = "include"
        
        if not os.path.exists(include_dir):
            print("Warning: No include directory found")
            return
            
        # First pass: Extract type definitions
        for header_file in os.listdir(include_dir):
            if header_file.endswith('.h'):
                header_path = os.path.join(include_dir, header_file)
                self.extract_type_definitions(header_path)
        
        # Second pass: Extract function declarations
        for header_file in os.listdir(include_dir):
            if header_file.endswith('.h'):
                header_path = os.path.join(include_dir, header_file)
                declarations = self.parse_header_declarations(header_path)
                
                for func_name, decl in declarations.items():
                    self.header_declarations[func_name] = {
                        'file': header_file,
                        'declaration': decl,
                        'header_path': header_path
                    }
                    
        print(f"Found {len(self.header_declarations)} function declarations in headers")
        print(f"Found {len(self.type_definitions)} type definitions")
        
    def parse_c_functions(self, filepath: str) -> List[FunctionInfo]:
        """Extract all functions from a C file"""
        functions = []
        
        with open(filepath, 'r') as f:
            content = f.read()
            
        # Pattern to match function definitions
        # Handles: static, inline, const, return types with *, etc.
        func_pattern = re.compile(
            r'(?:^|\n)'  # Start of line or after newline
            r'(?P<docs>(?:\/\*\*.*?\*\/\s*)?)'  # Optional documentation comment
            r'(?P<return>(?:static\s+)?(?:inline\s+)?(?:const\s+)?'  # Modifiers
            r'(?:struct\s+)?(?:enum\s+)?'  # struct/enum
            r'(?:\w+(?:\s*\*)?(?:\s+|\s*\*\s*))+)'  # Return type (with pointers)
            r'(?P<name>\w+)\s*'  # Function name
            r'\((?P<params>[^)]*)\)\s*'  # Parameters
            r'\{',  # Opening brace
            re.MULTILINE | re.DOTALL
        )
        
        # Find all function starts
        for match in func_pattern.finditer(content):
            func_start = match.start()
            func_name = match.group('name')
            return_type = match.group('return').strip()
            params = match.group('params').strip()
            docs = match.group('docs').strip()
            
            # Find the matching closing brace
            brace_count = 1
            pos = match.end()
            
            while brace_count > 0 and pos < len(content):
                if content[pos] == '{':
                    brace_count += 1
                elif content[pos] == '}':
                    brace_count -= 1
                pos += 1
                
            if brace_count == 0:
                # Extract complete function including the closing brace
                full_func = content[match.start():pos]
                # Extract just the body (between braces)
                body_start = full_func.find('{')
                body = full_func[body_start:pos-func_start]
                
                func_info = FunctionInfo(
                    name=func_name,
                    return_type=return_type,
                    params=params,
                    body=body,
                    docs=docs,
                    full_text=full_func
                )
                functions.append(func_info)
                
        return functions
        
    def determine_target_path(self, func_info: FunctionInfo) -> str:
        """Determine target directory for a function based on Genesis principle"""
        func_name = func_info.name
        
        # Genesis Principle: 1 function → 1 file → 1 directory
        # Structure: src/<logicgroup>/<childfunction>/<childfunction>.c
        # Check mapping rules in order
        for pattern, directory in self.mapping_rules:
            if re.match(pattern, func_name):
                return f"src/{directory}/{func_name}.c"
                
        # Default fallback
        return f"src/misc/{func_name}.c"
        
    def analyze_dependencies(self, func_info: FunctionInfo, all_functions: Dict[str, List[FunctionInfo]]) -> set:
        """Analyze function dependencies to determine required headers"""
        dependencies = set()
        
        # Extract all function calls from the body
        func_call_pattern = re.compile(r'\b(\w+)\s*\(')
        for match in func_call_pattern.finditer(func_info.body):
            called_func = match.group(1)
            # Skip standard C functions
            if called_func not in ['if', 'while', 'for', 'return', 'sizeof', 'switch']:
                dependencies.add(called_func)
                
        return dependencies
        
    def analyze_include_dependencies(self, func_info: FunctionInfo) -> set:
        """Analyze function to determine required includes"""
        includes = set()
        
        # Check for type usage in function signature and body
        full_content = func_info.return_type + ' ' + func_info.params + ' ' + func_info.body
        
        # Look for known types
        for type_name, type_info in self.type_definitions.items():
            if re.search(r'\b' + type_name + r'\b', full_content):
                includes.add(type_info['header'])
                
        # Check for function calls to determine dependencies
        func_call_pattern = re.compile(r'\b(\w+)\s*\(')
        for match in func_call_pattern.finditer(func_info.body):
            called_func = match.group(1)
            if called_func in self.header_declarations:
                orig_header = self.header_declarations[called_func]['file']
                # Don't include internal headers from other modules
                if not orig_header.endswith('_internal.h') or func_info.name.startswith(called_func.split('_')[0]):
                    includes.add(orig_header)
                    
        return includes
        
    def generate_modular_file_content(self, func_info: FunctionInfo, 
                                    source_file: str) -> str:
        """Generate content for a modular function file"""
        # Analyze dependencies first
        header_deps = self.analyze_include_dependencies(func_info)
        
        # Determine which headers to include based on function content
        headers = set()
        
        # Add specific headers based on function name patterns
        if 'ast_' in func_info.name:
            headers.add('"ast_node.h"')
            if 'parse' in func_info.name:
                headers.add('"ast_parser.h"')
            if 'evaluate' in func_info.name:
                headers.add('"ast_evaluator.h"')
            if 'create' in func_info.name or 'free' in func_info.name:
                headers.add('"ast_node.h"')
            if 'value' in func_info.name:
                headers.add('"ast_value.h"')
                
        if 'variable_' in func_info.name:
            headers.add('"variable.h"')
            headers.add('"variable_internal.h"')
            
        if 'lexer_' in func_info.name:
            headers.add('"lexer.h"')
            headers.add('"lexer_internal.h"')
            
        if 'token_' in func_info.name:
            headers.add('"token.h"')
            
        if 'store_' in func_info.name:
            headers.add('"store.h"')
            headers.add('"store_internal.h"')
            
        # Analyze function body for dependencies
        if 'variable' in func_info.body:
            headers.add('"variable.h"')
        if 'token' in func_info.body:
            headers.add('"token.h"')
        if 'lexer' in func_info.body and 'lexer_' not in func_info.name:
            headers.add('"lexer.h"')
        if 'error' in func_info.body:
            headers.add('"error.h"')
        if 'config' in func_info.body:
            headers.add('"config.h"')
        if 'utils' in func_info.body or 'xmd_strdup' in func_info.body:
            headers.add('"utils.h"')
            
        # Check for standard library usage
        if 'malloc' in func_info.body or 'free' in func_info.body or 'calloc' in func_info.body:
            headers.add('<stdlib.h>')
        if 'strcmp' in func_info.body or 'strlen' in func_info.body or 'strcpy' in func_info.body:
            headers.add('<string.h>')
        if 'printf' in func_info.body or 'fprintf' in func_info.body:
            headers.add('<stdio.h>')
        if 'bool' in func_info.return_type or 'true' in func_info.body or 'false' in func_info.body:
            headers.add('<stdbool.h>')
        if 'size_t' in func_info.params or 'size_t' in func_info.return_type:
            headers.add('<stddef.h>')
        if 'assert' in func_info.body:
            headers.add('<assert.h>')
            
        # Add headers from dependency analysis
        for header_file in header_deps:
            headers.add(f'"{header_file}"')
            
        # Sort headers: system headers first, then local
        system_headers = sorted([h for h in headers if h.startswith('<')])
        local_headers = sorted([h for h in headers if h.startswith('"')])
        
        # Build file content
        content = f"""/**
 * @file {os.path.basename(func_info.target_path)}
 * @brief Implementation of {func_info.name} function
 * 
 * This file contains ONLY the {func_info.name} function.
 * One function per file - Genesis principle compliance.
 * 
 * Extracted from: {source_file}
 */

"""
        # Add includes
        for h in system_headers:
            content += f"#include {h}\n"
        if system_headers and local_headers:
            content += "\n"
        for h in local_headers:
            content += f"#include {h}\n"
            
        content += "\n"
        
        # Add the function (with its documentation if present)
        if func_info.docs:
            content += func_info.docs + "\n"
            
        # Add the complete function
        content += func_info.full_text
        
        return content
        
    def analyze_file(self, filepath: str) -> Dict:
        """Analyze a C file and plan its refactoring"""
        file_stats = {
            'path': filepath,
            'size': os.path.getsize(filepath),
            'functions': [],
            'line_count': 0
        }
        
        with open(filepath, 'r') as f:
            file_stats['line_count'] = sum(1 for _ in f)
            
        # Parse functions
        functions = self.parse_c_functions(filepath)
        file_stats['function_count'] = len(functions)
        
        # Plan target paths for each function
        for func in functions:
            func.target_path = self.determine_target_path(func)
            self.directories_to_create.add(os.path.dirname(func.target_path))
            file_stats['functions'].append({
                'name': func.name,
                'target': func.target_path,
                'size_estimate': len(func.full_text)
            })
            
        self.functions_found[filepath] = functions
        return file_stats
        
    def update_existing_headers(self) -> None:
        """Update existing header files to remove moved declarations"""
        if self.dry_run:
            print("\nWould update existing headers to remove moved declarations")
            return
            
        headers_modified = 0
        
        # Track which functions have been moved
        moved_functions = set()
        for _, functions in self.functions_found.items():
            for func in functions:
                moved_functions.add(func.name)
                
        # Update each header that had declarations
        processed_headers = set()
        for func_name, info in self.header_declarations.items():
            if func_name in moved_functions:
                header_path = info['header_path']
                
                if header_path not in processed_headers:
                    processed_headers.add(header_path)
                    
                    with open(header_path, 'r') as f:
                        content = f.read()
                        
                    original_content = content
                    
                    # Remove function declarations that have been moved
                    for fname in moved_functions:
                        if fname in self.header_declarations and self.header_declarations[fname]['header_path'] == header_path:
                            decl = self.header_declarations[fname]['declaration']
                            # Remove the declaration and any preceding comment
                            pattern = re.compile(
                                r'(?:/\*\*.*?\*/\s*)?\n?' + re.escape(decl),
                                re.MULTILINE | re.DOTALL
                            )
                            content = pattern.sub('', content)
                            
                    # Clean up multiple blank lines
                    content = re.sub(r'\n\s*\n\s*\n', '\n\n', content)
                    
                    if content != original_content:
                        with open(header_path, 'w') as f:
                            f.write(content)
                        headers_modified += 1
                        
        print(f"Updated {headers_modified} existing header files")
        
    def generate_header_updates(self) -> Dict[str, str]:
        """Generate updates for existing header files based on refactoring"""
        updates = {}
        
        # Group functions by their original header file
        header_to_functions = {}
        for func_name, info in self.header_declarations.items():
            header_file = info['file']
            if header_file not in header_to_functions:
                header_to_functions[header_file] = []
            header_to_functions[header_file].append(func_name)
            
        # For each header, determine what needs to be updated
        for header_file, func_names in header_to_functions.items():
            header_path = os.path.join("include", header_file)
            
            with open(header_path, 'r') as f:
                content = f.read()
                
            new_content = content
            includes_to_add = set()
            
            # Check each function in this header
            for func_name in func_names:
                # Find where this function moved to
                for source_file, functions in self.functions_found.items():
                    for func in functions:
                        if func.name == func_name:
                            # Function found - determine new header location
                            module_path = os.path.dirname(func.target_path)
                            module_parts = module_path.split('/')
                            
                            if len(module_parts) >= 2:
                                # Create include for new module header
                                module_name = module_parts[1]  # e.g., 'ast', 'token'
                                includes_to_add.add(f'#include "{module_name}/{func_name}.h"')
                            break
                            
            # Add new includes after existing includes
            if includes_to_add:
                # Find last include line
                include_lines = []
                for line in new_content.split('\n'):
                    if line.strip().startswith('#include'):
                        include_lines.append(line)
                        
                if include_lines:
                    last_include = include_lines[-1]
                    # Add new includes after the last existing include
                    for new_include in sorted(includes_to_add):
                        new_content = new_content.replace(
                            last_include,
                            f"{last_include}\n{new_include}"
                        )
                        
            updates[header_path] = new_content
            
        return updates
        
    def generate_forward_declarations(self) -> Dict[str, str]:
        """Generate header files with forward declarations for each module"""
        headers = {}
        
        # Group functions by module
        module_functions = {}
        for source_file, functions in self.functions_found.items():
            for func in functions:
                # Extract module from target path
                parts = func.target_path.split('/')
                if len(parts) >= 3:
                    module = parts[1]  # e.g., 'ast', 'variable', 'token'
                    if module not in module_functions:
                        module_functions[module] = []
                    module_functions[module].append(func)
                    
        # Generate header content for each module
        for module, functions in module_functions.items():
            header_content = f"""/**
 * @file {module}.h
 * @brief Forward declarations for {module} module functions
 * 
 * Auto-generated during modular refactoring.
 * One function per file - Genesis principle compliance.
 */

#ifndef XMD_{module.upper()}_H
#define XMD_{module.upper()}_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used in this module */
"""
            # Add common types based on module
            if module == 'ast':
                header_content += """
typedef struct ast_node ast_node;
typedef struct ast_value ast_value;
typedef struct source_location source_location;
typedef enum ast_node_type ast_node_type;
typedef enum binary_operator binary_operator;
"""
            elif module == 'variable':
                header_content += """
typedef struct variable variable;
typedef enum variable_type variable_type;
"""
            elif module == 'token':
                header_content += """
typedef struct token token;
typedef enum token_type token_type;
"""
                
            header_content += "\n/* Function declarations */\n"
            
            # Add function declarations
            for func in sorted(functions, key=lambda f: f.name):
                # Clean up return type and build declaration
                return_type = func.return_type.strip()
                if not return_type.endswith('*'):
                    return_type += ' '
                    
                header_content += f"{return_type}{func.name}({func.params});\n"
                
            header_content += f"\n#endif /* XMD_{module.upper()}_H */\n"
            
            headers[f"include/{module}.h"] = header_content
            
        return headers
        
    def generate_cmake_updates(self) -> str:
        """Generate CMakeLists.txt content for Genesis principle structure"""
        # Genesis Principle: Each function has its own directory
        all_sources = []
        
        for source_file, functions in self.functions_found.items():
            for func in functions:
                all_sources.append(func.target_path)
                
        # Generate CMake content for Genesis principle
        cmake_content = "# Genesis Principle: 1 function → 1 file → 1 directory\n"
        cmake_content += "# Each function in its own isolated directory\n\n"
        
        cmake_content += "set(XMD_MODULAR_SOURCES\n"
        for source_path in sorted(all_sources):
            cmake_content += f"    {source_path}\n"
        cmake_content += ")\n\n"
        
        cmake_content += "# Add subdirectories for each function\n"
        for source_path in sorted(all_sources):
            # Extract directory name (function name)
            func_dir = source_path.split('/')[1]  # src/func_name/func_name.c -> func_name
            cmake_content += f"add_subdirectory(src/{func_dir})\n"
            
        return cmake_content
        
    def validate_refactoring(self, before_stats: Dict, after_stats: Dict) -> bool:
        """Validate that refactoring preserves all code"""
        print("\n=== Validation Report ===")
        
        # Check function count
        before_funcs = sum(s['function_count'] for s in before_stats.values())
        after_funcs = after_stats['total_functions']
        print(f"Functions before: {before_funcs}")
        print(f"Functions after: {after_funcs}")
        
        if before_funcs != after_funcs:
            print("❌ ERROR: Function count mismatch!")
            return False
            
        # Check line count (allowing some variance for added headers)
        before_lines = sum(s['line_count'] for s in before_stats.values())
        after_lines = after_stats['total_lines']
        line_diff = after_lines - before_lines
        print(f"Lines before: {before_lines}")
        print(f"Lines after: {after_lines}")
        print(f"Line difference: {line_diff} (added headers/comments)")
        
        if abs(line_diff) > before_lines * 0.2:  # Allow 20% increase for headers
            print("❌ WARNING: Significant line count change!")
            
        # Check file sizes
        max_size = after_stats['max_file_size']
        print(f"Largest new file: {max_size} bytes")
        
        if max_size > 2048:
            print("❌ WARNING: Some files exceed 2KB limit!")
            
        print("\n✅ Validation passed!")
        return True
        
    def run_analysis(self, target_files: List[str]) -> Dict:
        """Analyze all target files and generate refactoring plan"""
        print("=== Scanning Header Files ===\n")
        self.scan_all_headers()
        
        print("\n=== Analyzing Target Files ===\n")
        
        stats = {}
        for filepath in target_files:
            if os.path.exists(filepath):
                print(f"Analyzing: {filepath}")
                stats[filepath] = self.analyze_file(filepath)
                print(f"  - Size: {stats[filepath]['size']:,} bytes")
                print(f"  - Functions: {stats[filepath]['function_count']}")
                
        return stats
        
    def show_dry_run_report(self, stats: Dict):
        """Display what would be done without making changes"""
        print("\n=== DRY RUN REPORT ===\n")
        
        total_functions = sum(len(funcs) for funcs in self.functions_found.values())
        print(f"Total functions to extract: {total_functions}")
        print(f"Directories to create: {len(self.directories_to_create)}")
        print(f"Backup location: {self.backup_dir}")
        
        print("\nPlanned directory structure:")
        for dir_path in sorted(self.directories_to_create)[:20]:  # Show first 20
            print(f"  {dir_path}/")
        if len(self.directories_to_create) > 20:
            print(f"  ... and {len(self.directories_to_create) - 20} more directories")
            
        print("\nSample function mappings:")
        sample_count = 0
        for source_file, functions in self.functions_found.items():
            for func in functions[:5]:  # Show first 5 from each file
                print(f"  {func.name} -> {func.target_path}")
                sample_count += 1
                if sample_count >= 10:
                    break
            if sample_count >= 10:
                break
                
        print("\nCMake updates will be generated")
        print("Original consolidated files will be removed")
        
        # Show header updates needed
        if self.header_declarations:
            print(f"\nHeader declarations found: {len(self.header_declarations)}")
            print("Headers will be updated to reference new module structure")
        
    def execute_refactoring(self):
        """Actually perform the refactoring"""
        if self.dry_run:
            print("\n❌ Cannot execute in dry-run mode!")
            return
            
        print("\n=== EXECUTING REFACTORING ===\n")
        
        # Create all directories
        for dir_path in self.directories_to_create:
            os.makedirs(dir_path, exist_ok=True)
            print(f"Created directory: {dir_path}")
            
        # Extract and write all functions
        total_written = 0
        for source_file, functions in self.functions_found.items():
            print(f"\nProcessing {source_file}...")
            
            for func in functions:
                content = self.generate_modular_file_content(func, source_file)
                
                with open(func.target_path, 'w') as f:
                    f.write(content)
                    
                total_written += 1
                if total_written % 10 == 0:
                    print(f"  Written {total_written} files...")
                    
        print(f"\nTotal files written: {total_written}")
        
        # Generate individual header files for each function
        print("\nGenerating header files...")
        header_count = 0
        for source_file, functions in self.functions_found.items():
            for func in functions:
                # Generate header path from target path
                header_path = func.target_path.replace('.c', '.h')
                header_dir = os.path.dirname(header_path)
                
                if not os.path.exists(header_dir):
                    os.makedirs(header_dir, exist_ok=True)
                    
                # Find original declaration if it exists
                original_decl = None
                if func.name in self.header_declarations:
                    original_decl = self.header_declarations[func.name]['declaration']
                else:
                    # Generate declaration from function signature
                    original_decl = f"{func.return_type}{func.name}({func.params});"
                    
                # Generate header content
                header_content = f"""/**
 * @file {os.path.basename(header_path)}
 * @brief Declaration for {func.name} function
 * 
 * This file contains ONLY the {func.name} declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef {func.name.upper()}_H
#define {func.name.upper()}_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */
"""
                # Add type-specific includes based on function
                if 'ast_' in func.name:
                    header_content += """
typedef struct ast_node ast_node;
typedef struct ast_value ast_value;
"""
                elif 'variable' in func.name:
                    header_content += """
typedef struct variable variable;
"""
                elif 'token' in func.name:
                    header_content += """
typedef struct token token;
"""
                    
                header_content += f"""
/* Function declaration */
{original_decl}

#endif /* {func.name.upper()}_H */
"""
                
                with open(header_path, 'w') as f:
                    f.write(header_content)
                header_count += 1
                
        print(f"Generated {header_count} header files")
        
        # Generate module-level header files
        module_headers = self.generate_forward_declarations()
        for header_path, content in module_headers.items():
            header_dir = os.path.dirname(header_path)
            if not os.path.exists(header_dir):
                os.makedirs(header_dir, exist_ok=True)
            with open(header_path, 'w') as f:
                f.write(content)
        print(f"Generated {len(module_headers)} module header files")
        
        # Update existing headers to remove moved declarations
        self.update_existing_headers()
        
        # Generate CMake updates
        cmake_content = self.generate_cmake_updates()
        with open("CMakeLists_modular.txt", 'w') as f:
            f.write(cmake_content)
        print("Generated CMakeLists_modular.txt")
        
        # Remove original consolidated files
        print("\nRemoving original consolidated files...")
        for source_file in self.functions_found.keys():
            os.remove(source_file)
            print(f"  Removed: {source_file}")
            
        print("\n✅ Refactoring complete!")


def main():
    parser = argparse.ArgumentParser(
        description="XMD Codebase Refactoring Tool - Modularize consolidated C files"
    )
    parser.add_argument(
        '--execute', 
        action='store_true',
        help='Actually perform refactoring (default is dry-run)'
    )
    parser.add_argument(
        '--target',
        nargs='+',
        default=['src/ast_consolidated.c'],
        help='Target files to refactor'
    )
    
    args = parser.parse_args()
    
    # Header
    print("=" * 60)
    print("XMD Codebase Refactoring Tool")
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
        
    # Create refactorer
    refactorer = XMDRefactorer(dry_run=not args.execute)
    
    # Create backup
    backup_path = refactorer.backup_codebase()
    
    # Validate input files exist
    for target in args.target:
        if not os.path.exists(target):
            print(f"\n❌ ERROR: Target file not found: {target}")
            sys.exit(1)
            
    # Analyze files
    stats_before = refactorer.run_analysis(args.target)
    
    # Show dry run report
    refactorer.show_dry_run_report(stats_before)
    
    if not args.execute:
        print("\n" + "=" * 60)
        print("To execute refactoring, run with --execute flag")
        print("Example: python refactor_xmd.py --execute")
        print("=" * 60)
    else:
        # Execute refactoring
        response = input("\nFinal confirmation - type 'YES': ")
        if response == 'YES':
            refactorer.execute_refactoring()
            
            # Validate results
            # TODO: Implement after_stats collection
            print("\nRefactoring completed!")
            print(f"Backup available at: {backup_path}")
        else:
            print("Aborted.")


if __name__ == "__main__":
    main()