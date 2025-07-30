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
