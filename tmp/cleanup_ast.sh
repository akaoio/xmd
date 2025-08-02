#!/bin/bash
# Script to clean up ast_consolidated.c by removing everything after line 1706

# Create backup
cp src/ast_consolidated.c src/ast_consolidated.c.backup

# Use sed to delete everything after line 1706
sed -i '1707,$d' src/ast_consolidated.c

echo "Cleaned up ast_consolidated.c - removed everything after line 1706"
echo "Backup saved as ast_consolidated.c.backup"