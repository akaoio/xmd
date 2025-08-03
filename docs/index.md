# XMD Documentation

Welcome to XMD - eXtended MarkDown processor with advanced scripting capabilities.

## Getting Started

- [Quick Start Guide](quick-start.md) - Get up and running in 5 minutes
- [Installation](quick-start.md#installation) - Installation options
- [Basic Usage](quick-start.md#basic-usage) - Your first XMD document
- [Updating XMD](quick-start.md#updating-xmd) - Keep your installation current

## User Guide

- [CLI Reference](cli-reference.md) - Command-line options and examples
- [Upgrade Guide](upgrade-guide.md) - Keep your installation current
- [Multiline Directives](multiline-directives.md) - Advanced scripting features
- [Watch Mode](cli-reference.md#watch-mode-for-development) - Real-time file processing
- [Examples](../examples/) - Real-world use cases

## Language Reference

### Variables
- Set variables with `set`
- Use variables with `{{variable}}`
- Support for strings, numbers, booleans, arrays, objects
- Array literals: `["item1", "item2", "item3"]`
- Variable initialization: `set varname` (without assignment)

### Advanced Scripting
- **Array Processing**: Iterate over arrays with `for item in array`
- **String Concatenation**: Use `+` operator for string combination
- **Compound Assignment**: Use `+=` for accumulating content
- **Dynamic Imports**: `import variable_name` where variable contains filename
- **Expression Evaluation**: Complex expressions like `"prefix " + import file + " suffix"`

### Commands
- Execute with `exec`
- Capture output with `set var = exec command`
- Dynamic buffer allocation for large command outputs
- Security controls with `--no-exec`

### Functions
- `print(variable)` - Output variable value
- `cmd("command")` - Execute and return output

### Control Flow
- `if/elif/else/endif` - Conditional execution
- `for/endfor` - Loop over arrays and ranges
- Advanced for loops with bodies and indentation
- Logical operators: `&&`, `||`, `!`

### Script Blocks
```markdown
<!-- xmd 
set files = ["config.md", "setup.md", "deploy.md"]
set documentation = ""
for file in files
    documentation += "## " + import file + "\n\n"
-->
{{documentation}}
```

## Developer Guide

- [Developer Documentation](dev/) - Architecture and contribution guide
- [API Reference](dev/api/) - Function documentation
- [Testing Guide](dev/testing.md) - How to run and write tests

## Support

- [GitHub Issues](https://github.com/akaoio/xmd/issues) - Bug reports
- [Discussions](https://github.com/akaoio/xmd/discussions) - Q&A and ideas