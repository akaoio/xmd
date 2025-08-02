#!/bin/bash
# Build Stability Check - DevOps Emergency Support
# Quick build verification during parser redesign crisis

echo "🔧 Build Stability Check - Parser Redesign Support"
echo "=================================================="

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Check build with error output
echo "Running compilation test..."
BUILD_OUTPUT=$(./build.sh 2>&1)
BUILD_EXIT_CODE=$?

if [ $BUILD_EXIT_CODE -eq 0 ]; then
    echo -e "${GREEN}✅ BUILD SUCCESS${NC}"
    echo "Binary created: $(ls -la build/xmd 2>/dev/null | awk '{print $5" bytes"}')"
    
    # Check for warnings
    WARNING_COUNT=$(echo "$BUILD_OUTPUT" | grep -c "warning:")
    if [ $WARNING_COUNT -gt 0 ]; then
        echo -e "${YELLOW}⚠️  Warnings: $WARNING_COUNT${NC}"
    else
        echo -e "${GREEN}✅ No warnings${NC}"
    fi
    
    # Quick runtime test 
    echo ""
    echo "Quick runtime test..."
    if ./build/xmd --version >/dev/null 2>&1; then
        echo -e "${GREEN}✅ Runtime: Basic functionality working${NC}"
    else
        echo -e "${RED}❌ Runtime: Basic test failed${NC}"
    fi
    
else
    echo -e "${RED}❌ BUILD FAILED${NC}"
    echo ""
    echo "Compilation errors:"
    echo "$BUILD_OUTPUT" | grep "error:" | head -10
    
    # Show specific parser-related errors
    echo ""
    echo "Parser-related issues:"
    echo "$BUILD_OUTPUT" | grep -i "ast\|parse\|function"
fi

echo ""
echo "Genesis Parser Redesign Status:"
echo "- Developer2: Working on parser disambiguation engine"
echo "- Three comma patterns need implementation"
echo "- NO PARENTHESES syntax must be enforced"

# Check for critical files
echo ""
echo "Critical parser files status:"
for file in "src/ast_consolidated.c" "src/parser_utils.c" "include/ast_node.h"; do
    if [ -f "$file" ]; then
        SIZE=$(stat -c%s "$file" 2>/dev/null || stat -f%z "$file" 2>/dev/null || echo "unknown")
        echo "✅ $file ($SIZE bytes)"
    else
        echo -e "${RED}❌ Missing: $file${NC}"
    fi
done