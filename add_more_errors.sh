#!/bin/bash
# More comprehensive error message addition
echo "=== COMPREHENSIVE ERROR MESSAGE ADDITION ==="

COUNTER=0

# Add error messages for memory allocation failures
echo "Adding error messages for malloc failures..."
find src -name "*.c" -exec grep -l "if (!.*malloc" {} \; | while read file; do
    if grep -q "return NULL" "$file" && ! grep -q "Memory allocation failed" "$file"; then
        FUNCNAME=$(basename "$file" .c)
        sed -i "s/return NULL;/XMD_ERROR_RETURN(NULL, \"$FUNCNAME: Memory allocation failed\");/g" "$file"
        COUNTER=$((COUNTER + 1))
        echo "  Updated: $file"
    fi
done

# Add error messages for validation failures
echo "Adding error messages for validation failures..."
find src -name "*.c" -exec grep -l "if (!.*validate" {} \; | while read file; do
    if grep -q "return false" "$file" && ! grep -q "Validation failed" "$file"; then
        FUNCNAME=$(basename "$file" .c)
        sed -i "s/return false;/XMD_ERROR_RETURN(false, \"$FUNCNAME: Validation failed\");/g" "$file"
        COUNTER=$((COUNTER + 1))
        echo "  Updated: $file"
    fi
done

# Add error messages for NULL pointer checks
echo "Adding error messages for NULL pointer checks..."
find src -name "*.c" | while read file; do
    FUNCNAME=$(basename "$file" .c)
    
    # Add error for if (!ptr) return NULL patterns
    if grep -q "if (![a-zA-Z_]*) return NULL" "$file"; then
        sed -i "s/if (\(![a-zA-Z_]*\)) return NULL/if (\1) { XMD_ERROR_RETURN(NULL, \"$FUNCNAME: NULL pointer provided\"); }/g" "$file"
        COUNTER=$((COUNTER + 1))
        echo "  Updated NULL checks in: $file"
    fi
done

echo "Total error messages added this round: $COUNTER"