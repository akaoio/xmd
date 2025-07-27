# Developer Guide

Development documentation for XMD contributors.

## Architecture

XMD follows a modular architecture:

```
xmd
├── lexer        - Tokenization and parsing
├── processor    - Directive processing
├── template     - Variable substitution
├── executor     - Command execution
├── store        - Variable storage
└── cli          - Command-line interface
```

## Development Rules

1. **One function per file**: Each function in its own file
2. **Folder structure**: `module_name/function_name/function_name.c`
3. **Max 200 lines per file**: Keep files focused and manageable
4. **Test-driven**: Write tests before implementation
5. **No external dependencies**: Self-contained implementation

## Building

```bash
# Clone repository
git clone https://github.com/akaoio/xmd
cd xmd

# Build
mkdir build && cd build
cmake ..
make

# Run tests
make test

# Install
sudo make install
```

## Testing

All tests must pass before merging:

```bash
# Run all tests
make test

# Run specific test
./test_xmd_processor
./test_truncate_fix
```

## Code Style

- C17 standard
- 4-space indentation
- Doxygen comments for all functions
- Clear variable names
- Error handling for all edge cases

## Adding Features

1. Create design doc in `docs/notes/`
2. Write tests in `test/`
3. Implement in appropriate module
4. Update documentation
5. Submit PR with tests passing

## Project Structure

```
xmd/
├── src/           - Source code
│   ├── lexer/     - Tokenization
│   ├── xmd_processor/ - Core processing
│   └── cli/       - CLI implementation
├── include/       - Header files
├── test/          - Test suites
├── docs/          - Documentation
└── examples/      - Example files
```

## Key Modules

### Lexer
Tokenizes XMD directives and markdown content.

### Processor
Handles directive execution and control flow.

### Template Engine
Variable substitution and template processing.

### Command Executor
Secure command execution with sandboxing.

## Contributing

1. Fork the repository
2. Create feature branch
3. Write tests first
4. Implement feature
5. Ensure all tests pass
6. Submit pull request

See [INSTRUCTIONS.md](INSTRUCTIONS.md) for detailed coding standards.