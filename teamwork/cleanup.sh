#!/bin/bash
# Teamwork directory cleanup script
# Removes test files and redundant dashboard attempts

echo "🧹 Cleaning up teamwork directory..."

# Create backup directory
BACKUP_DIR="./tech_debt_backup"
mkdir -p "$BACKUP_DIR"

# Move test files to backup
echo "📦 Moving test files to backup..."
find . -maxdepth 1 -name "test_*.md" -exec mv {} "$BACKUP_DIR/" \; 2>/dev/null

# Move old dashboard attempts to backup (keep only dashboard.md and dashboard_fixed.md)
echo "📦 Moving old dashboard files to backup..."
find . -maxdepth 1 -name "dashboard_*.md" ! -name "dashboard_fixed.md" -exec mv {} "$BACKUP_DIR/" \; 2>/dev/null

# Count cleaned files
CLEANED=$(ls "$BACKUP_DIR" | wc -l)
echo "✅ Moved $CLEANED files to backup directory"

# Show remaining files
echo ""
echo "📁 Remaining files in teamwork directory:"
ls -la | grep -v "^d" | grep -v "^total"
echo ""
echo "📁 Team update files:"
ls -la update/

echo ""
echo "🎉 Cleanup complete! Backup saved in: $BACKUP_DIR"