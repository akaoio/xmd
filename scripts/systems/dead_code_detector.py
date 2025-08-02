#!/usr/bin/env python3
"""
Dead Code Detector for XMD Project
Created by Systems Engineer per Genesis request

This tool scans the XMD codebase to find:
- Unused functions
- Dead/ghost functions  
- Duplicated functions
- Functions that are never called

Follows Genesis principle: Remove waste, keep only what's used.
"""

import os
import re
import json
from pathlib import Path
from collections import defaultdict

class XMDDeadCodeDetector:
    def __init__(self, root_dir):
        self.root_dir = Path(root_dir)
        self.src_dir = self.root_dir / "src"
        self.include_dir = self.root_dir / "include"
        
        # Track all functions and their usage
        self.defined_functions = {}  # function_name -> {file, line, type}
        self.called_functions = defaultdict(list)  # function_name -> [call_locations]
        self.file_dependencies = defaultdict(set)  # file -> set of functions it calls
        
        # Patterns for function detection
        self.function_def_pattern = re.compile(
            r'^(?:static\s+)?(?:inline\s+)?(\w+(?:\s*\*)*)\s+(\w+)\s*\([^)]*\)\s*(?:\{|;)',
            re.MULTILINE
        )
        self.function_call_pattern = re.compile(r'(\w+)\s*\(')
        
    def scan_codebase(self):
        """Scan entire codebase for function definitions and calls"""
        print("🔍 Scanning XMD codebase for functions...")
        
        # Scan all C files for function definitions
        for c_file in self.src_dir.rglob("*.c"):
            self._scan_file_definitions(c_file)
            
        # Scan all C and H files for function calls
        for file_path in list(self.src_dir.rglob("*.c")) + list(self.include_dir.rglob("*.h")):
            self._scan_file_calls(file_path)
            
        print(f"✅ Found {len(self.defined_functions)} function definitions")
        print(f"✅ Found {len(self.called_functions)} called functions")
        
    def _scan_file_definitions(self, file_path):
        """Scan a file for function definitions"""
        try:
            content = file_path.read_text(encoding='utf-8', errors='ignore')
            
            for match in self.function_def_pattern.finditer(content):
                return_type = match.group(1).strip()
                func_name = match.group(2).strip()
                
                # Skip main function and some common patterns
                if func_name in ['main']:
                    continue
                    
                # Calculate line number
                line_num = content[:match.start()].count('\n') + 1
                
                self.defined_functions[func_name] = {
                    'file': str(file_path.relative_to(self.root_dir)),
                    'line': line_num,
                    'return_type': return_type,
                    'is_static': 'static' in match.group(0),
                    'content_snippet': content[max(0, match.start()-20):match.end()+20]
                }
                
        except Exception as e:
            print(f"❌ Error scanning {file_path}: {e}")
            
    def _scan_file_calls(self, file_path):
        """Scan a file for function calls"""
        try:
            content = file_path.read_text(encoding='utf-8', errors='ignore')
            
            for match in self.function_call_pattern.finditer(content):
                func_name = match.group(1).strip()
                
                # Skip keywords and common patterns
                if func_name in ['if', 'while', 'for', 'switch', 'return', 'sizeof', 'include']:
                    continue
                    
                line_num = content[:match.start()].count('\n') + 1
                
                self.called_functions[func_name].append({
                    'file': str(file_path.relative_to(self.root_dir)),
                    'line': line_num
                })
                
                # Track file dependencies
                relative_path = str(file_path.relative_to(self.root_dir))
                self.file_dependencies[relative_path].add(func_name)
                
        except Exception as e:
            print(f"❌ Error scanning calls in {file_path}: {e}")
            
    def find_dead_functions(self):
        """Find functions that are defined but never called"""
        dead_functions = []
        
        for func_name, definition in self.defined_functions.items():
            if func_name not in self.called_functions:
                dead_functions.append({
                    'name': func_name,
                    'definition': definition,
                    'reason': 'Never called'
                })
                
        return dead_functions
        
    def find_ghost_functions(self):
        """Find functions that are called but never defined"""
        ghost_functions = []
        
        for func_name, call_locations in self.called_functions.items():
            if func_name not in self.defined_functions:
                # Filter out standard library and system functions
                if not self._is_system_function(func_name):
                    ghost_functions.append({
                        'name': func_name,
                        'calls': call_locations,
                        'reason': 'Called but not defined'
                    })
                    
        return ghost_functions
        
    def find_duplicate_functions(self):
        """Find functions with similar implementations"""
        duplicates = []
        
        # Group functions by similar patterns (simplified)
        function_patterns = defaultdict(list)
        
        for func_name, definition in self.defined_functions.items():
            # Create a simple signature pattern
            pattern = f"{definition['return_type']}_args"
            function_patterns[pattern].append((func_name, definition))
            
        # Find groups with multiple functions
        for pattern, functions in function_patterns.items():
            if len(functions) > 1:
                duplicates.append({
                    'pattern': pattern,
                    'functions': functions,
                    'count': len(functions)
                })
                
        return duplicates
        
    def _is_system_function(self, func_name):
        """Check if function is likely a system/library function"""
        system_prefixes = [
            'printf', 'sprintf', 'fprintf', 'snprintf',
            'malloc', 'calloc', 'realloc', 'free',
            'strlen', 'strcpy', 'strcat', 'strcmp', 'strdup',
            'memset', 'memcpy', 'memmove',
            'fopen', 'fclose', 'fread', 'fwrite', 'fseek', 'ftell',
            'atoi', 'atof', 'strtol', 'strtod',
            'isdigit', 'isalpha', 'isspace',
            'exit', 'abort', 'assert'
        ]
        
        for prefix in system_prefixes:
            if func_name.startswith(prefix):
                return True
                
        return False
        
    def generate_report(self):
        """Generate comprehensive dead code report"""
        self.scan_codebase()
        
        dead_functions = self.find_dead_functions()
        ghost_functions = self.find_ghost_functions()
        duplicate_functions = self.find_duplicate_functions()
        
        report = {
            'summary': {
                'total_defined_functions': len(self.defined_functions),
                'total_called_functions': len(self.called_functions),
                'dead_functions_count': len(dead_functions),
                'ghost_functions_count': len(ghost_functions),
                'potential_duplicates': len(duplicate_functions)
            },
            'dead_functions': dead_functions,
            'ghost_functions': ghost_functions,
            'duplicate_functions': duplicate_functions,
            'recommendations': self._generate_recommendations(dead_functions, ghost_functions)
        }
        
        return report
        
    def _generate_recommendations(self, dead_functions, ghost_functions):
        """Generate actionable recommendations"""
        recommendations = []
        
        if dead_functions:
            recommendations.append({
                'action': 'Remove dead functions',
                'count': len(dead_functions),
                'priority': 'high',
                'description': f'Remove {len(dead_functions)} unused functions to reduce codebase size'
            })
            
        if ghost_functions:
            recommendations.append({
                'action': 'Fix missing function definitions',
                'count': len(ghost_functions),
                'priority': 'medium',
                'description': f'Add definitions for {len(ghost_functions)} called but undefined functions'
            })
            
        return recommendations
        
    def save_report(self, output_file="dead_code_report.json"):
        """Save report to file"""
        report = self.generate_report()
        
        output_path = self.root_dir / output_file
        with open(output_path, 'w') as f:
            json.dump(report, f, indent=2)
            
        print(f"📊 Dead code report saved to: {output_path}")
        return report

def main():
    """Main entry point"""
    script_dir = Path(__file__).parent
    xmd_root = script_dir.parent.parent  # Go up to XMD root
    
    print("🚀 XMD Dead Code Detector - Genesis Request")
    print("=" * 50)
    
    detector = XMDDeadCodeDetector(xmd_root)
    report = detector.save_report()
    
    # Print summary
    summary = report['summary']
    print(f"")
    print(f"📊 ANALYSIS RESULTS:")
    print(f"• Total functions defined: {summary['total_defined_functions']}")
    print(f"• Total functions called: {summary['total_called_functions']}")
    print(f"• 💀 Dead functions: {summary['dead_functions_count']}")
    print(f"• 👻 Ghost functions: {summary['ghost_functions_count']}")
    print(f"• 🔄 Potential duplicates: {summary['potential_duplicates']}")
    
    if report['recommendations']:
        print(f"")
        print(f"🎯 RECOMMENDATIONS:")
        for rec in report['recommendations']:
            print(f"• {rec['action']}: {rec['count']} items ({rec['priority']} priority)")
            
    print(f"")
    print(f"✅ Report saved to dead_code_report.json")

if __name__ == "__main__":
    main()