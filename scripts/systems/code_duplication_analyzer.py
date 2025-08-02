#!/usr/bin/env python3
"""
XMD Code Duplication Analyzer - EVIDENCE-BASED VERIFICATION
Created by Systems Engineer for Leader verification request
Provides REAL metrics instead of estimated progress
"""

import os
import re
import hashlib
from collections import defaultdict
from pathlib import Path

class CodeDuplicationAnalyzer:
    def __init__(self, src_dir="src"):
        self.src_dir = Path(src_dir)
        self.total_lines = 0
        self.unique_lines = 0
        self.duplicated_lines = 0
        self.line_hashes = defaultdict(list)
        self.function_patterns = defaultdict(list)
        
    def normalize_line(self, line):
        """Normalize line for comparison (remove whitespace, comments)"""
        # Remove leading/trailing whitespace
        line = line.strip()
        # Remove single-line comments
        line = re.sub(r'//.*$', '', line)
        # Remove empty lines
        if not line:
            return None
        # Normalize whitespace
        line = re.sub(r'\s+', ' ', line)
        return line
        
    def analyze_file(self, file_path):
        """Analyze a single C file for duplicated patterns"""
        try:
            with open(file_path, 'r', encoding='utf-8') as f:
                lines = f.readlines()
                
            file_lines = []
            for i, line in enumerate(lines):
                normalized = self.normalize_line(line)
                if normalized:
                    line_hash = hashlib.md5(normalized.encode()).hexdigest()
                    self.line_hashes[line_hash].append((file_path, i+1, normalized))
                    file_lines.append(normalized)
                    self.total_lines += 1
                    
            # Look for function patterns
            self._analyze_function_patterns(file_path, file_lines)
            
        except Exception as e:
            print(f"Error analyzing {file_path}: {e}")
            
    def _analyze_function_patterns(self, file_path, lines):
        """Look for common function implementation patterns"""
        patterns = {
            'null_check': r'if\s*\(\s*!\s*\w+\s*\)',
            'malloc_safe': r'\w+\s*=\s*\w*malloc\s*\(',
            'strdup_safe': r'\w+\s*=\s*\w*strdup\s*\(',
            'free_safe': r'free\s*\(\s*\w+\s*\)',
            'macro_usage': r'XMD_\w+'
        }
        
        for line in lines:
            for pattern_name, pattern in patterns.items():
                if re.search(pattern, line):
                    self.function_patterns[pattern_name].append((file_path, line))
    
    def scan_codebase(self):
        """Scan entire codebase for duplication"""
        print("🔍 EVIDENCE-BASED CODE DUPLICATION ANALYSIS")
        print("=" * 50)
        
        if not self.src_dir.exists():
            print(f"❌ Source directory {self.src_dir} not found!")
            return
            
        c_files = list(self.src_dir.rglob("*.c"))
        print(f"📁 Found {len(c_files)} C files")
        
        for c_file in c_files:
            self.analyze_file(c_file)
            
        self._calculate_duplication()
        self._generate_report()
        
    def _calculate_duplication(self):
        """Calculate actual duplication percentage"""
        duplicated_hashes = 0
        for line_hash, occurrences in self.line_hashes.items():
            if len(occurrences) > 1:
                # This line appears multiple times
                duplicated_hashes += len(occurrences) - 1
                
        self.duplicated_lines = duplicated_hashes
        self.unique_lines = self.total_lines - self.duplicated_lines
        
    def _generate_report(self):
        """Generate evidence-based duplication report"""
        if self.total_lines == 0:
            duplication_percent = 0
        else:
            duplication_percent = (self.duplicated_lines / self.total_lines) * 100
            
        print(f"\n📊 ACTUAL DUPLICATION METRICS:")
        print(f"Total Lines of Code: {self.total_lines}")
        print(f"Unique Lines: {self.unique_lines}")
        print(f"Duplicated Lines: {self.duplicated_lines}")
        print(f"Duplication Percentage: {duplication_percent:.1f}%")
        
        print(f"\n🔧 MACRO USAGE ANALYSIS:")
        macro_count = len(self.function_patterns.get('macro_usage', []))
        print(f"XMD_* Macro Uses: {macro_count}")
        
        print(f"\n🎯 PATTERN ANALYSIS:")
        for pattern, occurrences in self.function_patterns.items():
            print(f"{pattern}: {len(occurrences)} occurrences")
            
        # Most duplicated lines
        print(f"\n⚠️ TOP DUPLICATED PATTERNS:")
        duplicated_patterns = [(hash_val, len(occurrences)) 
                             for hash_val, occurrences in self.line_hashes.items() 
                             if len(occurrences) > 2]
        duplicated_patterns.sort(key=lambda x: x[1], reverse=True)
        
        for i, (hash_val, count) in enumerate(duplicated_patterns[:5]):
            example = self.line_hashes[hash_val][0][2]  # Get example line
            print(f"{i+1}. '{example[:60]}...' ({count} times)")
            
        return duplication_percent

def main():
    analyzer = CodeDuplicationAnalyzer()
    analyzer.scan_codebase()
    
    # Calculate duplication percentage
    if analyzer.total_lines == 0:
        duplication_percent = 0
    else:
        duplication_percent = (analyzer.duplicated_lines / analyzer.total_lines) * 100
    
    # Save results for verification
    results_file = Path("scripts/systems/duplication_results.txt")
    with open(results_file, 'w') as f:
        f.write(f"EVIDENCE-BASED DUPLICATION ANALYSIS\n")
        f.write(f"Timestamp: {os.popen('date').read().strip()}\n")
        f.write(f"Total Lines: {analyzer.total_lines}\n")
        f.write(f"Duplicated Lines: {analyzer.duplicated_lines}\n")
        f.write(f"Duplication Percentage: {duplication_percent:.1f}%\n")
        f.write(f"Macro Uses: {len(analyzer.function_patterns.get('macro_usage', []))}\n")
    
    print(f"\n✅ Results saved to {results_file}")
    return duplication_percent

if __name__ == "__main__":
    main()