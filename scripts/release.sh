#!/bin/bash
# XMD Release Script - Fully Automated
# Usage: ./scripts/release.sh [--dry-run] [--auto] <version>
# Example: ./scripts/release.sh 0.0.2
# Example: ./scripts/release.sh --dry-run 0.0.2
# Example: ./scripts/release.sh --auto 0.0.2  (fully automated)

set -e

# Parse arguments
DRY_RUN=false
AUTO_MODE=false
VERSION=""

while [[ $# -gt 0 ]]; do
    case $1 in
        --dry-run)
            DRY_RUN=true
            shift
            ;;
        --auto)
            AUTO_MODE=true
            shift
            ;;
        *)
            VERSION=$1
            shift
            ;;
    esac
done

if [ -z "$VERSION" ]; then
    echo "Usage: $0 [--dry-run] [--auto] <version>"
    echo "Example: $0 0.0.2"
    echo "Example: $0 --dry-run 0.0.2"
    echo "Example: $0 --auto 0.0.2  (fully automated)"
    exit 1
fi

# Validate version format (semver: major.minor.patch)
if ! echo "$VERSION" | grep -qE '^[0-9]+\.[0-9]+\.[0-9]+$'; then
    echo "Error: Invalid version format '$VERSION'. Must be semver format (e.g., 1.2.3)"
    exit 1
fi
MAJOR=$(echo $VERSION | cut -d. -f1)
MINOR=$(echo $VERSION | cut -d. -f2)
PATCH=$(echo $VERSION | cut -d. -f3)

# Auto-detect platform for binary naming
detect_platform() {
    local os=$(uname -s | tr '[:upper:]' '[:lower:]')
    local arch=$(uname -m)
    
    case "$arch" in
        x86_64) arch="x64" ;;
        aarch64|arm64) arch="arm64" ;;
        armv7l) arch="arm" ;;
        i386|i686) arch="x86" ;;
    esac
    
    echo "xmd-${os}-${arch}"
}

BINARY_NAME=$(detect_platform)

if [ "$DRY_RUN" = true ]; then
    echo "DRY RUN: Preparing release $VERSION..."
    echo "DRY RUN: Target binary: $BINARY_NAME"
elif [ "$AUTO_MODE" = true ]; then
    echo "AUTO MODE: Preparing fully automated release $VERSION..."
    echo "Target binary: $BINARY_NAME"
else
    echo "Preparing release $VERSION..."
    echo "Target binary: $BINARY_NAME"
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
    
    if [ "$AUTO_MODE" = true ]; then
        echo ""
        echo "🚀 AUTO MODE: Executing automated release process..."
        
        # Step 1: Build the project
        echo "Step 1/6: Building project..."
        rm -rf build/
        mkdir -p build
        cd build
        cmake ..
        make -j$(nproc) xmd
        cd ..
        
        # Copy binary with platform-specific name
        cp build/xmd "$BINARY_NAME"
        echo "✅ Binary built: $BINARY_NAME"
        
        # Step 2: Git operations
        echo "Step 2/6: Adding files to git..."
        git add CMakeLists.txt include/xmd.h "$BINARY_NAME"
        
        echo "Step 3/6: Creating commit..."
        git commit -m "Bump version to $VERSION"
        
        echo "Step 4/6: Creating tag..."
        git tag "$VERSION"
        
        echo "Step 5/6: Pushing to remote..."
        git push origin main --tags
        
        # Step 6: Create GitHub release
        echo "Step 6/6: Creating GitHub release..."
        if command -v gh >/dev/null 2>&1; then
            gh release create "$VERSION" "$BINARY_NAME" \
                --title "Release $VERSION" \
                --notes "Automated release $VERSION

## What's New
- Version bumped to $VERSION
- Platform-specific binary: $BINARY_NAME

## Installation
Download the binary for your platform and make it executable:
\`\`\`bash
chmod +x $BINARY_NAME
./$BINARY_NAME --help
\`\`\`"
            echo "✅ GitHub release created successfully!"
        else
            echo "⚠️  gh CLI not found. Please install it and create the release manually:"
            echo "gh release create $VERSION $BINARY_NAME --title \"Release $VERSION\" --notes \"Release notes here\""
        fi
        
        echo ""
        echo "🎉 AUTOMATED RELEASE COMPLETE!"
        echo "Version: $VERSION"
        echo "Binary: $BINARY_NAME"
        echo "Tag: $VERSION"
        echo "Release: https://github.com/$(git config --get remote.origin.url | sed 's/.*github.com[:/]//; s/.git$//')/releases/tag/$VERSION"
        
    else
        echo ""
        echo "Next steps (run with --auto to automate):"
        echo "1. Review the changes above"
        echo "2. git add CMakeLists.txt include/xmd.h"
        echo "3. git commit -m \"Bump version to $VERSION\""
        echo "4. git tag $VERSION"
        echo "5. Build: rm -rf build && mkdir build && cd build && cmake .. && make xmd && cd .. && cp build/xmd $BINARY_NAME"
        echo "6. git add $BINARY_NAME && git commit --amend --no-edit"
        echo "7. git push origin main --tags"
        echo "8. gh release create $VERSION $BINARY_NAME --title \"Release $VERSION\" --notes \"Release notes here\""
        echo ""
        echo "Or run: ./scripts/release.sh --auto $VERSION"
    fi
fi