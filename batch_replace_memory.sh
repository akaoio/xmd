#!/bin/bash

# Batch replace memory operations with XMD macros
# Phase 1 optimization for Systems Engineer

echo "Starting batch memory replacement..."

# Count before
MALLOC_BEFORE=$(grep -r "malloc(" src/ast/ | wc -l)
FREE_BEFORE=$(grep -r "free(" src/ast/ | wc -l)
CALLOC_BEFORE=$(grep -r "calloc(" src/ast/ | wc -l)

echo "Before: malloc=$MALLOC_BEFORE, free=$FREE_BEFORE, calloc=$CALLOC_BEFORE"

# Add includes where needed
find src/ast -name "*.c" -type f | while read file; do
    # Check if common_macros.h already included
    if ! grep -q "common_macros.h" "$file"; then
        # Add include after last include line
        sed -i '/#include/h;$!d;x;s/.*/&\n#include "..\/..\/..\/..\/utils\/common\/common_macros.h"/' "$file" 2>/dev/null || \
        sed -i '/#include/h;$!d;x;s/.*/&\n#include "..\/..\/..\/utils\/common\/common_macros.h"/' "$file" 2>/dev/null || \
        sed -i '/#include/h;$!d;x;s/.*/&\n#include "..\/..\/utils\/common\/common_macros.h"/' "$file" 2>/dev/null
    fi
done

# Replace malloc with XMD_MALLOC_SAFE
find src/ast -name "*.c" -type f | xargs sed -i 's/malloc(/XMD_MALLOC_SAFE(/g'

# Replace free with XMD_FREE_SAFE  
find src/ast -name "*.c" -type f | xargs sed -i 's/free(/XMD_FREE_SAFE(/g'

# Replace calloc with XMD_CALLOC_SAFE
find src/ast -name "*.c" -type f | xargs sed -i 's/calloc(/XMD_CALLOC_SAFE(/g'

# Count after
MALLOC_AFTER=$(grep -r "malloc(" src/ast/ | wc -l)
FREE_AFTER=$(grep -r "free(" src/ast/ | wc -l)
CALLOC_AFTER=$(grep -r "calloc(" src/ast/ | wc -l)

echo "After: malloc=$MALLOC_AFTER, free=$FREE_AFTER, calloc=$CALLOC_AFTER"

# Count macro usage
MACRO_COUNT=$(grep -r "XMD_" src/ast/ | wc -l)
echo "Total XMD macro uses in src/ast: $MACRO_COUNT"

echo "Batch replacement complete!"