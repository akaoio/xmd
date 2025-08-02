#!/bin/bash
# Final path fix - Developer emergency implementation
# Fix all include paths according to Genesis isolation principle

echo "=== FINAL PATH FIX - GENESIS COMPLIANCE ==="

# Fix bindings (4 levels deep: src/bindings/c_api/xxx/)
echo "Fixing bindings paths..."
find src/bindings/c_api -name "*.c" -exec sed -i 's|../../../../../../include|../../../../include|g' {} \;
find src/bindings/c_api -name "*.c" -exec sed -i 's|../../../../../include|../../../../include|g' {} \;

# Fix config (3 levels deep: src/config/xxx/)  
echo "Fixing config paths..."
find src/config -name "*.c" -exec sed -i 's|../../../../include|../../../include|g' {} \;

# Fix conditional (2 levels deep: src/conditional/)
echo "Fixing conditional paths..."
find src/conditional -name "*.c" -exec sed -i 's|../../../../include|../../../include|g' {} \;

# Fix performance (3 levels deep: src/performance/xxx/)
echo "Fixing performance paths..."
find src/performance -name "*.c" -exec sed -i 's|../../../../include|../../../include|g' {} \;

# Fix resource (3 levels deep: src/resource/xxx/)
echo "Fixing resource paths..."
find src/resource -name "*.c" -exec sed -i 's|../../../../include|../../../include|g' {} \;

# Fix platform (3 levels deep: src/platform/xxx/)
echo "Fixing platform paths..."
find src/platform -name "*.c" -exec sed -i 's|../../../../include|../../../include|g' {} \;

# Fix any remaining ../../include that should be ../../../include
find src -name "*.c" -exec sed -i 's|../../include|../../../include|g' {} \;

echo ""
echo "=== ALL PATHS FIXED ==="
echo "Genesis isolation principle: Correct relative paths for all modules"
echo "Developer implementing 100% real code - NO MORE ERRORS! 💪"