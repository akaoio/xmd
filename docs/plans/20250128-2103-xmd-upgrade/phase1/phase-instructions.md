# Phase 1: Dynamic Version Detection

## Goal
Implement dynamic version detection from git tags or embedded version info instead of hardcoded values.

## Tasks
1. Create version detection function that checks:
   - Git tags if in git repository
   - Embedded version string from build time
   - Fallback to CMake version

2. Embed version at build time:
   - Generate version header during CMake configure
   - Include git tag/commit info if available
   - Store in generated header file

3. Update version display:
   - Replace hardcoded version strings
   - Use dynamic version detection
   - Show commit hash for non-release builds

## Implementation Details
- Create `get_version()` function
- Generate `version_info.h` at build time
- Update `print_version()` to use dynamic version

## Success Criteria
- `xmd version` shows actual version from git tag/build
- Version matches release tags when built from release
- Shows dev version with commit hash for non-release builds