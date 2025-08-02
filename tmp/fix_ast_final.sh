#!/bin/bash
# Final fix for ast_consolidated.c - remove everything after line 1765

cd /data/data/com.termux/files/home/xmd

# Keep only first 1765 lines (up to my END comment)
head -n 1765 src/ast_consolidated.c > src/ast_consolidated_clean.c
mv src/ast_consolidated_clean.c src/ast_consolidated.c

echo "Fixed ast_consolidated.c - removed all duplicate code after line 1765"
echo "File now ends with: '// END OF AST_CONSOLIDATED.C - Single source of truth per Genesis directive'"