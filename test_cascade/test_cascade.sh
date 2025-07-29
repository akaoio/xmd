#!/bin/bash

echo "=== XMD Cascade Testing ==="
echo "Testing the complete mission scenario:"
echo "1. core/comment.md → index/comment.md → dashboard.md"
echo ""

cd teamwork

# Initial processing
echo "📝 Initial processing..."
../xmd process dashboard.md > ../output/initial_dashboard.html
../xmd process index/comment.md > ../output/initial_index.html

echo "📄 Initial dashboard content:"
head -5 ../output/initial_dashboard.html

echo ""
echo "🔧 Modifying core/comment.md..."
# Simulate the change that should trigger cascade
cat > core/comment.md << 'EOF'
# Core Comment

This is the base comment file - UPDATED VERSION!

Date: 2025-07-29  
Status: Modified at $(date)
Updated: This change should cascade through the entire chain
EOF

echo ""
echo "📝 Processing files after change..."
../xmd process dashboard.md > ../output/updated_dashboard.html
../xmd process index/comment.md > ../output/updated_index.html

echo "📄 Updated dashboard content:"
head -8 ../output/updated_dashboard.html

echo ""
echo "🔍 Checking if cascade worked..."
if grep -q "UPDATED VERSION" ../output/updated_dashboard.html; then
    echo "✅ SUCCESS: Cascade worked! Core change propagated to dashboard"
else
    echo "❌ FAILED: Core change did not propagate to dashboard"
fi

echo ""
echo "📊 File comparison:"
echo "Before:"
grep -A1 "This is the base" ../output/initial_dashboard.html
echo "After:"
grep -A1 "This is the base" ../output/updated_dashboard.html

echo ""
echo "=== Test completed ===" 