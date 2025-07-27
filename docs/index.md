# XMD Documentation

Welcome to XMD - eXtended MarkDown processor.

## Getting Started

- [Quick Start Guide](quick-start.md) - Get up and running in 5 minutes
- [Installation](quick-start.md#installation) - Installation options
- [Basic Usage](quick-start.md#basic-usage) - Your first XMD document

## User Guide

- [CLI Reference](cli-reference.md) - Command-line options and examples
- [Multiline Directives](multiline-directives.md) - Advanced syntax features
- [Examples](../examples/) - Real-world use cases

## Language Reference

### Variables
- Set variables with `set`
- Use variables with `{{variable}}`
- Support for strings, numbers, booleans, arrays, objects

### Commands
- Execute with `exec`
- Capture output with `set var = exec command`
- Security controls with `--no-exec`

### Functions
- `print(variable)` - Output variable value
- `cmd("command")` - Execute and return output

### Control Flow
- `if/elif/else/endif` - Conditional execution
- `for/endfor` - Loop over arrays and ranges
- Logical operators: `&&`, `||`, `!`

### Multiline Blocks
```markdown
<!-- xmd:
multiple
directives
here
-->
```

## Developer Guide

- [Developer Documentation](dev/) - Architecture and contribution guide
- [API Reference](dev/api/) - Function documentation
- [Testing Guide](dev/testing.md) - How to run and write tests

## Support

- [GitHub Issues](https://github.com/akaoio/xmd/issues) - Bug reports
- [Discussions](https://github.com/akaoio/xmd/discussions) - Q&A and ideas