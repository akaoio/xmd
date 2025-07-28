#!/bin/bash
# XMD Release Script
# Usage: ./scripts/release.sh [--dry-run] <version>
# Example: ./scripts/release.sh 0.0.2
# Example: ./scripts/release.sh --dry-run 0.0.2

set -e

# Parse arguments
DRY_RUN=false
VERSION=""

while [[ $# -gt 0 ]]; do
    case $1 in
        --dry-run)
            DRY_RUN=true
            shift
            ;;
        *)
            VERSION=$1
            shift
            ;;
    esac
done

if [ -z "$VERSION" ]; then
    echo "Usage: $0 [--dry-run] <version>"
    echo "Example: $0 0.0.2"
    echo "Example: $0 --dry-run 0.0.2"
    exit 1
fi
MAJOR=$(echo $VERSION | cut -d. -f1)
MINOR=$(echo $VERSION | cut -d. -f2)
PATCH=$(echo $VERSION | cut -d. -f3)

if [ "$DRY_RUN" = true ]; then
    echo "DRY RUN: Preparing release $VERSION..."
else
    echo "Preparing release $VERSION..."
fi

# Create temporary files for dry run
if [ "$DRY_RUN" = true ]; then
    cp CMakeLists.txt CMakeLists.txt.tmp
    cp include/xmd.h include/xmd.h.tmp
    CMAKE_FILE="CMakeLists.txt.tmp"
    HEADER_FILE="include/xmd.h.tmp"
else
    CMAKE_FILE="CMakeLists.txt"
    HEADER_FILE="include/xmd.h"
fi

# Update CMakeLists.txt
sed -i "s/project(xmd VERSION [0-9]\+\.[0-9]\+\.[0-9]\+/project(xmd VERSION $VERSION/" "$CMAKE_FILE"

# Update include/xmd.h
sed -i "s/#define XMD_VERSION_MAJOR [0-9]\+/#define XMD_VERSION_MAJOR $MAJOR/" "$HEADER_FILE"
sed -i "s/#define XMD_VERSION_MINOR [0-9]\+/#define XMD_VERSION_MINOR $MINOR/" "$HEADER_FILE"
sed -i "s/#define XMD_VERSION_PATCH [0-9]\+/#define XMD_VERSION_PATCH $PATCH/" "$HEADER_FILE"
sed -i "s/#define XMD_VERSION_STRING \"[0-9]\+\.[0-9]\+\.[0-9]\+\"/#define XMD_VERSION_STRING \"$VERSION\"/" "$HEADER_FILE"

if [ "$DRY_RUN" = true ]; then
    echo "DRY RUN: Version would be updated to $VERSION in source files"
else
    echo "Version updated to $VERSION in source files"
fi

# Show the changes
if [ "$DRY_RUN" = true ]; then
    echo ""
    echo "DRY RUN: Changes that would be made:"
    diff -u CMakeLists.txt "$CMAKE_FILE" || true
    diff -u include/xmd.h "$HEADER_FILE" || true
    
    # Clean up temp files
    rm -f "$CMAKE_FILE" "$HEADER_FILE"
    
    echo ""
    echo "DRY RUN: No actual changes were made."
    echo "Run without --dry-run to apply these changes."
else
    echo "Changes made:"
    git diff CMakeLists.txt include/xmd.h
    
    echo ""
    echo "Next steps:"
    echo "1. Review the changes above"
    echo "2. git add CMakeLists.txt include/xmd.h"
    echo "3. git commit -m \"Bump version to $VERSION\""
    echo "4. git tag $VERSION"
    echo "5. Build the project"
    echo "6. git push origin main --tags"
    echo "7. Create GitHub release with: gh release create $VERSION xmd-linux-arm64 --title \"Release $VERSION\" --notes \"Release notes here\""
fi