#!/bin/bash
# Script to add error messages to return NULL statements
# DEBTHUNTER automated error message addition

echo "Starting error message addition campaign..."
echo "Target: 329 missing error messages"
echo ""

COUNTER=0
FILES_UPDATED=0

# Priority 1: Parser functions
echo "=== PHASE 1: Parser Functions ==="
for file in src/ast/parser/loop/*.c src/ast/parser/control/*.c src/ast/parser/literal/*.c; do
    if [ -f "$file" ]; then
        # Check if file has return NULL without error message
        if grep -q "return NULL;" "$file" && ! grep -q "XMD_ERROR_RETURN" "$file"; then
            echo "Processing: $file"
            FILENAME=$(basename "$file" .c)
            
            # Add XMD_ERROR_RETURN for common patterns
            sed -i.bak 's/return NULL;/XMD_ERROR_RETURN(NULL, "'$FILENAME': Operation failed");/g' "$file"
            
            ADDED=$(diff "$file.bak" "$file" | grep "^>" | wc -l)
            COUNTER=$((COUNTER + ADDED))
            FILES_UPDATED=$((FILES_UPDATED + 1))
            echo "  Added $ADDED error messages"
            rm "$file.bak"
        fi
    fi
done

# Priority 2: Evaluator functions
echo ""
echo "=== PHASE 2: Evaluator Functions ==="
for file in src/ast/evaluator/*/*.c src/ast/evaluator/*/*/*.c; do
    if [ -f "$file" ]; then
        if grep -q "return NULL;" "$file" && ! grep -q "XMD_ERROR_RETURN" "$file"; then
            echo "Processing: $file"
            FILENAME=$(basename "$file" .c)
            
            # Add error messages for evaluator patterns
            sed -i.bak 's/return NULL;/XMD_ERROR_RETURN(NULL, "'$FILENAME': Evaluation failed");/g' "$file"
            
            ADDED=$(diff "$file.bak" "$file" | grep "^>" | wc -l)
            COUNTER=$((COUNTER + ADDED))
            FILES_UPDATED=$((FILES_UPDATED + 1))
            echo "  Added $ADDED error messages"
            rm "$file.bak"
        fi
    fi
done

# Priority 3: Variable operations
echo ""
echo "=== PHASE 3: Variable Operations ==="
for file in src/variable/*/*.c; do
    if [ -f "$file" ]; then
        if grep -q "return NULL;" "$file" && ! grep -q "XMD_ERROR_RETURN" "$file"; then
            echo "Processing: $file"
            FILENAME=$(basename "$file" .c)
            
            sed -i.bak 's/return NULL;/XMD_ERROR_RETURN(NULL, "'$FILENAME': Variable operation failed");/g' "$file"
            
            ADDED=$(diff "$file.bak" "$file" | grep "^>" | wc -l)
            COUNTER=$((COUNTER + ADDED))
            FILES_UPDATED=$((FILES_UPDATED + 1))
            echo "  Added $ADDED error messages"
            rm "$file.bak"
        fi
    fi
done

echo ""
echo "=== SUMMARY ==="
echo "Files updated: $FILES_UPDATED"
echo "Error messages added: $COUNTER"
echo "Remaining target: $((329 - COUNTER))"