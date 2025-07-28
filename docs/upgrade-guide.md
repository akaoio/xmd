# XMD Upgrade Guide

This guide explains how to keep your XMD installation up to date with the latest features and improvements.

## Installation vs Upgrade

XMD provides two ways to get the latest version:

### Initial Installation
For first-time installation, use the install script which downloads the latest release:

```bash
curl -fsSL https://raw.githubusercontent.com/akaoio/xmd/main/install.sh | bash
```

### Upgrading Existing Installation
If you already have XMD installed, use the built-in upgrade command:

```bash
xmd upgrade
```

## How the Upgrade System Works

### Dynamic Version Detection
XMD now uses dynamic version detection that extracts version information from git tags at build time. This means:

- No more hardcoded version numbers
- Version information is always accurate
- Build information includes git commit and tag details

### Version Command
Check your current version with complete build information:

```bash
xmd version
# Output:
# XMD version 0.0.2
# Built on Jul 28 2025
```

### Upgrade Command
The upgrade command:

1. **Checks current version**: Uses dynamic version detection
2. **Queries GitHub API**: Fetches latest release information
3. **Compares versions**: Determines if upgrade is needed
4. **Downloads safely**: Downloads the latest release binary
5. **Installs atomically**: Replaces the binary with backup/restore

```bash
xmd upgrade
# Output:
# XMD Upgrade Tool
# ================
# 
# Current version: 0.0.2
# Checking for updates...
# ✓ You are already running the latest version (0.0.2)
```

## Upgrade Command Options

### Basic Upgrade
```bash
# Check for updates and upgrade if available
xmd upgrade
```

### Help Information
```bash
# Show upgrade command help
xmd upgrade --help
```

## Install Script Updates

The `install.sh` script has been updated to:

- **Download from releases**: Instead of building from source by default
- **Faster installation**: No build dependencies required for most installations
- **Fallback building**: Still builds from source if no pre-built binary available
- **Version consistency**: Uses same GitHub API as upgrade command

### Installation Dependencies
The install script now only requires:
- `curl` or `wget` (for downloads)
- `tar` (for extraction)

Build dependencies are only needed as fallback:
- `cmake`, `gcc`/`clang`, `make` (only if building from source)

## Version Information Architecture

### Components
1. **CMake Configuration**: Extracts git information at build time
2. **Generated Headers**: Creates version_info.h with current version
3. **Dynamic Functions**: `get_version()` and `xmd_get_version()` return real version
4. **CLI Integration**: All version displays use dynamic detection

### Build-Time Version Generation
During build, CMake:
```cmake
# Get git tag
execute_process(COMMAND git describe --tags --exact-match ...)

# Generate version header
configure_file(version_info.h.in version_info.h @ONLY)
```

This ensures version information is always current and accurate.

## Troubleshooting

### Common Issues

#### Network Connectivity
If upgrade fails with network errors:
```bash
# Check GitHub API accessibility
curl -s https://api.github.com/repos/akaoio/xmd/releases/latest

# Manual upgrade via install script
curl -fsSL https://raw.githubusercontent.com/akaoio/xmd/main/install.sh | bash
```

#### Permission Issues
If installation fails due to permissions:
```bash
# Check install directory permissions
ls -la $(dirname $(which xmd))

# May need sudo for system-wide installation
sudo xmd upgrade  # Not recommended - use install script instead
```

#### Version Detection Issues
If version shows incorrectly:
```bash
# Check if xmd binary is in PATH
which xmd

# Verify version functions
xmd version
```

### Getting Help

If you encounter issues:

1. **Check version**: `xmd version`
2. **View help**: `xmd upgrade --help`
3. **GitHub Issues**: [Report problems](https://github.com/akaoio/xmd/issues)
4. **Discussions**: [Ask questions](https://github.com/akaoio/xmd/discussions)

## Best Practices

### Regular Updates
- Check for updates periodically: `xmd upgrade`
- Subscribe to release notifications on GitHub
- Test upgrades in development environments first

### Version Management
- Always verify version after upgrade: `xmd version`
- Keep track of version changes in your projects
- Use version consistency across development team

### Security
- Upgrade regularly for security patches
- Use release versions for production deployments
- Verify checksums when available

## Related Documentation

- [Quick Start Guide](quick-start.md) - Basic installation and usage
- [CLI Reference](cli-reference.md) - All command options
- [Installation Guide](quick-start.md#installation) - Initial setup