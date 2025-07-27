# Changelog

All notable changes to this project will be documented in this file.

## [1.0.1] - 2025-07-27

### Added
- **Function Support**: Built-in `print()` and `cmd()` functions for multiline blocks
- **Dynamic Buffer Allocation**: Automatic buffer growth for large command outputs (up to 1MB)
- **Test Suite**: Added `test_truncate_fix` to verify large output handling

### Fixed
- **Output Truncation**: Fixed exec commands and print() being truncated at ~770 lines
- **Multiline Function Output**: Fixed print() and cmd() not producing output in multiline blocks
- **Memory Management**: Improved buffer allocation strategy to handle large outputs

### Changed
- Increased multiline directive buffer from 32KB to 1MB
- Updated documentation to reflect current functionality
- Simplified documentation for better clarity

## [1.0.0] - 2025-07-26

### Added
- **Core Features**: Variables, control flow, command execution
- **Multiline Directives**: Clean syntax for complex operations
- **CLI Interface**: Full command-line processing
- **Output Formats**: Markdown, HTML, JSON
- **Security**: Sandboxed execution with --no-exec option

### Fixed
- Variable substitution in headers
- Control flow processing
- Memory management issues

### Testing
- 27 comprehensive tests all passing
- Stress tests for edge cases
- Memory leak validation

## License

MIT License - see [LICENSE](LICENSE) file for details.