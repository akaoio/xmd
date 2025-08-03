#!/bin/bash

# Remove all DEBUG printf statements from source files
echo "Removing DEBUG printf statements..."

# Count before
BEFORE=$(grep -r "printf.*DEBUG" src/ | wc -l)
echo "Found $BEFORE debug statements"

# Remove debug printf lines
find src/ -type f -name "*.c" -exec sed -i '/printf.*DEBUG/d' {} \;

# Also remove standalone printf statements used for debugging
find src/ -type f -name "*.c" -exec sed -i '/printf("DEBUG:/d' {} \;

# Count after
AFTER=$(grep -r "printf.*DEBUG" src/ | wc -l)
echo "Removed $(($BEFORE - $AFTER)) debug statements"
echo "$AFTER debug statements remaining"

echo "Debug removal complete!"