#!/bin/bash

echo "🚀 Starting Team Dashboard Watch Demo"
echo "===================================="
echo ""

# Kill any existing watch processes
pkill -f "xmd.*watch" 2>/dev/null

# Process once to show initial state
echo "📊 Initial dashboard state:"
../xmd-release process dashboard_src.md -o dashboard.md
echo "Team members found: $(ls update/*.md 2>/dev/null | wc -l)"
echo ""

# Start watch in background
echo "👁️ Starting watch process..."
../xmd-release watch dashboard_src.md dashboard.md &
WATCH_PID=$!
echo "Watch PID: $WATCH_PID"
sleep 2

# Test 1: Modify existing role file
echo ""
echo "Test 1: Updating developer status"
echo "--------------------------------"
sed -i 's/Working on authentication module/Authentication module COMPLETED/' update/developer.md
sleep 2
grep -A1 "Status:" dashboard.md | grep developer -A1

# Test 2: Add new team member
echo ""
echo "Test 2: Adding new team member (DevOps)"
echo "---------------------------------------"
cat > update/devops.md << 'EOF'
### DevOps Update

**Role:** DevOps Engineer  
**Name:** David  
**Status:** Setting up CI/CD pipeline

#### Progress:
- Configured GitHub Actions
- Set up Docker containers
- Automated deployment process
EOF
sleep 2
echo "Team members now: $(grep "### " dashboard.md | wc -l)"

# Test 3: Modify another file
echo ""
echo "Test 3: Adding urgent issue to tester"
echo "------------------------------------"
echo -e "\n#### URGENT: Critical bug in payment module!" >> update/tester.md
sleep 2
grep "URGENT" dashboard.md

# Cleanup
echo ""
echo "🏁 Stopping watch process..."
kill $WATCH_PID 2>/dev/null

echo ""
echo "✅ Demo complete!"