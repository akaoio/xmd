#!/bin/bash
# XMD Release Script - No hardcoded versions!
# Usage: ./scripts/release.sh <version>
# Example: ./scripts/release.sh 0.0.5

set -e

VERSION=$1
if [ -z "$VERSION" ]; then
    echo "Usage: $0 <version>"
    echo "Example: $0 0.0.5"
    exit 1
fi

echo "Creating release $VERSION..."

# Auto-detect platform
OS=$(uname -s | tr '[:upper:]' '[:lower:]')
ARCH=$(uname -m)
case "$ARCH" in
    x86_64) ARCH="x64" ;;
    aarch64|arm64) ARCH="arm64" ;;
    armv7l) ARCH="arm" ;;
esac
BINARY_NAME="xmd-${OS}-${ARCH}"

# Step 1: Commit any pending changes
echo "Checking for uncommitted changes..."
if ! git diff-index --quiet HEAD --; then
    echo "Committing pending changes..."
    git add -A
    git commit -m "Prepare for release $VERSION"
fi

# Step 2: Create git tag
echo "Creating git tag $VERSION..."
git tag -a "$VERSION" -m "Release $VERSION"

# Step 3: Build with the new tag
echo "Building with version $VERSION..."
# Clean everything
make clean 2>/dev/null || true
rm -rf CMakeCache.txt CMakeFiles/
rm -f xmd

# Reconfigure and build
cmake -DCMAKE_BUILD_TYPE=Release .
make -j$(nproc)

# Verify version
BUILT_VERSION=$(./xmd version | head -1 | awk '{print $3}')
# Handle dev suffix if present
BUILT_VERSION=$(echo "$BUILT_VERSION" | cut -d'-' -f1)
if [ "$BUILT_VERSION" != "$VERSION" ]; then
    echo "Error: Built version ($BUILT_VERSION) doesn't match tag ($VERSION)"
    echo "This might be a caching issue. Try:"
    echo "  rm -rf build/"
    echo "  git tag -d $VERSION"
    echo "  Then run this script again"
    git tag -d "$VERSION"
    exit 1
fi

# Step 4: Create release artifacts
mkdir -p release-artifacts
cp xmd "release-artifacts/$BINARY_NAME"

# Create quick install script
cat > release-artifacts/install.sh << 'EOF'
#!/bin/bash
set -e
OS=$(uname -s | tr '[:upper:]' '[:lower:]')
ARCH=$(uname -m)
case "$ARCH" in
    x86_64) ARCH="x64" ;;
    aarch64|arm64) ARCH="arm64" ;;
    armv7l) ARCH="arm" ;;
esac
BINARY="xmd-${OS}-${ARCH}"
INSTALL_DIR="${PREFIX:-/usr/local}/bin"
echo "Installing $BINARY to $INSTALL_DIR..."
curl -fsSL -o xmd "https://github.com/akaoio/xmd/releases/latest/download/$BINARY"
chmod +x xmd
[ -w "$INSTALL_DIR" ] || SUDO=sudo
$SUDO mv xmd "$INSTALL_DIR/"
echo "✅ XMD installed!"
xmd version
EOF
chmod +x release-artifacts/install.sh

# Step 5: Push changes and tag
echo "Pushing any unpushed commits..."
git push origin main

echo "Pushing tag..."
git push origin "$VERSION"

# Step 6: Create GitHub release
if command -v gh >/dev/null 2>&1; then
    echo "Creating GitHub release..."
    gh release create "$VERSION" release-artifacts/* \
        --title "Release $VERSION" \
        --generate-notes
    echo "✅ Release $VERSION created!"
else
    echo "Install GitHub CLI (gh) to automatically create releases"
    echo "Or manually upload files from release-artifacts/"
fi

# Cleanup
rm -rf release-artifacts/

# Restore version_info.h if it was modified
git checkout include/version_info.h 2>/dev/null || true

echo ""
echo "🎉 Release $VERSION complete!"
echo "Version comes from git tag - no hardcoding!"