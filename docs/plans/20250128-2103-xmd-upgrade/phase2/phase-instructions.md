# Phase 2: Upgrade Command Implementation

## Goal
Implement `xmd upgrade` command to upgrade XMD to the latest release.

## Tasks
1. Add upgrade command to CLI:
   - Parse `upgrade` command argument
   - Handle upgrade process flow
   - Show progress and status

2. Implement upgrade logic:
   - Check current version
   - Query GitHub API for latest release
   - Compare versions
   - Download and install if newer

3. Create upgrade functions:
   - `check_for_updates()` - Compare versions
   - `download_release()` - Get latest release binary
   - `install_upgrade()` - Replace current binary
   - `verify_upgrade()` - Confirm successful upgrade

## Implementation Details
- Use GitHub API: https://api.github.com/repos/akaoio/xmd/releases/latest
- Download appropriate binary for platform
- Backup current binary before replacement
- Atomic replacement to avoid corruption

## Success Criteria
- `xmd upgrade` successfully updates to latest release
- Shows current and new version during upgrade
- Handles errors gracefully (network, permissions, etc)
- Works across different platforms