#!/bin/bash

# Enhanced fix for all missing headers in AST modular files
# Genesis Leader - Phase 4 enhanced header dependency resolution

echo "🔧 Enhanced Genesis Header Dependency Fix - Phase 4"
echo "=================================================="

# Files that need ctype.h (using isspace, isalpha, etc.)
echo "Step 1: Adding #include <ctype.h> to files using character functions..."
find src/ast/ -name "*.c" -exec grep -l "isspace\|isalpha\|isdigit\|isalnum" {} \; | while read file; do
    if [ -f "$file" ]; then
        if ! grep -q "#include <ctype.h>" "$file"; then
            echo "  ✅ Adding ctype.h to $file"
            # Add ctype.h after stdlib.h
            if grep -q "#include <stdlib.h>" "$file"; then
                sed -i 's/#include <stdlib.h>/#include <stdlib.h>\n#include <ctype.h>/' "$file"
            else
                # Add at top after initial includes
                sed -i '/#include <stdio.h>/a #include <ctype.h>' "$file"
            fi
        else
            echo "  ⚪ $file already has ctype.h"
        fi
    fi
done

# Files that need additional string.h functions (strncpy, strncmp, strchr, etc.)  
echo ""
echo "Step 2: Adding #include <string.h> to files using more string functions..."
find src/ast/ -name "*.c" -exec grep -l "strncpy\|strncmp\|strchr\|strcpy\|strlen" {} \; | while read file; do
    if [ -f "$file" ]; then
        if ! grep -q "#include <string.h>" "$file"; then
            echo "  ✅ Adding string.h to $file"
            # Add string.h after stdlib.h
            if grep -q "#include <stdlib.h>" "$file"; then
                sed -i 's/#include <stdlib.h>/#include <stdlib.h>\n#include <string.h>/' "$file"
            else
                # Add at top after initial includes
                sed -i '/#include <stdio.h>/a #include <string.h>' "$file"
            fi
        else
            echo "  ⚪ $file already has string.h"
        fi
    fi
done

echo ""
echo "🎉 Enhanced header dependency fix complete!"