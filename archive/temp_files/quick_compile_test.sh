#!/bin/bash
# Quick compilation test for fixed files
echo "=== QUICK COMPILATION TEST ==="

cd /data/data/com.termux/files/home/xmd

# Test one fixed file to verify build progress
echo "Testing ast_evaluate_assignment.c compilation..."
gcc -c -Iinclude src/ast/evaluator/assignment/ast_evaluate_assignment.c 2>&1

echo
echo "Testing ast_parse_single_value.c compilation..."  
gcc -c -Iinclude src/misc/ast_parse_single_value.c 2>&1

echo
echo "=== SUPPORTING DEVELOPER'S FINAL 38 FILES ==="