# Changelog

All notable changes to this project will be documented in this file.

## [0.0.2] - 2025-07-28

### Added
- **Comprehensive Test Suite**: Complete test coverage for all advanced scripting features
- **Array Literal Tests**: Validate `["item1", "item2"]` parsing and processing
- **For Loop Tests**: Test multi-line loop bodies with proper iteration
- **String Concatenation Tests**: Verify `"string1" + "string2"` expressions
- **Dynamic Import Tests**: Test `import variable` where variable contains filename
- **Compound Assignment Tests**: Validate `variable += "content"` operations
- **Script Block Detection Tests**: Ensure automatic syntax detection works correctly
- **Integration Tests**: End-to-end scenarios combining multiple advanced features
- **Memory Management Tests**: Verify proper cleanup and resource handling

### Fixed
- **Critical CTest Issue**: Fixed "FORTIFY: fwrite: null FILE*" error in test environment
- **Context Management**: Added proper `destroy_context()` function for memory cleanup
- **Working Directory**: Set correct working directories for tests to run from project root
- **Test Reliability**: All 37 tests now pass consistently (100% success rate)

### Improved
- **Test Coverage**: Comprehensive coverage of all advanced XMD scripting features
- **Error Handling**: Better error detection and graceful handling in edge cases
- **Memory Safety**: Proper resource cleanup and leak prevention
- **Build System**: Enhanced CMake configuration for reliable test execution

## [0.0.1] - 2025-07-28

### Added
- **Advanced Scripting Language**: Complete script-like syntax in multiline blocks
- **Array Literals**: Support for `["item1", "item2", "item3"]` syntax
- **For Loops with Bodies**: Multi-line indented loop bodies with full iteration
- **String Concatenation**: Use `+` operator for combining strings and expressions
- **Dynamic Imports**: `import variable_name` where variable contains filename
- **Compound Assignment**: `+=` operator for accumulating content
- **Expression Evaluation**: Complex expressions like `"prefix " + import file + " suffix"`
- **Script Block Detection**: Automatic detection of advanced syntax features
- **Watch Mode**: Real-time file processing with `xmd watch src/ dist/`

### Fixed
- **For Loop Iteration**: Fixed bug where only first array element was processed
- **String Parsing**: Replaced `strtok()` with custom parser to avoid state corruption
- **Multiline Directive Line Breaks**: Eliminated empty lines from directive blocks
- **Import Path Resolution**: Enhanced path resolution for watch mode and relative imports

### Changed
- **Enhanced Multiline Processor**: Script blocks use dedicated processor for advanced features
- **Expression Parser**: Custom expression evaluator for string concatenation
- **Documentation**: Comprehensive update of all docs with advanced scripting examples

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