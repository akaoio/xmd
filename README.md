# XMD - eXtended MarkDown

A powerful markdown preprocessor that adds programming capabilities to markdown files.

## Features

- **Variables & Templates**: Define and use variables throughout your markdown
- **Command Execution**: Run shell commands and embed their output  
- **Control Flow**: If/else conditions and for loops
- **Functions**: Built-in print() and cmd() functions
- **Multiline Support**: Clean syntax for complex operations
- **Dynamic Content**: Generate content programmatically

## Quick Start

```bash
# Install
curl -fsSL https://raw.githubusercontent.com/akaoio/xmd/main/install.sh | bash

# Process a file
xmd input.md -o output.md

# Process to stdout
xmd input.md
```

## Syntax Examples

### Variables
```markdown
<!-- xmd: set name = "World" -->
Hello, {{name}}!
```

### Command Execution
```markdown
<!-- xmd: exec date -->

<!-- xmd:
set files = exec ls -la
-->
Files: {{files}}
```

### Functions
```markdown
<!-- xmd:
set user = exec whoami
print(user)
-->
```

### Control Flow
```markdown
<!-- xmd: if exists("DEBUG") -->
Debug mode is ON
<!-- xmd: else -->
Debug mode is OFF  
<!-- xmd: endif -->
```

### Loops
```markdown
<!-- xmd: for file in *.md -->
- Processing {{file}}
<!-- xmd: endfor -->
```

## Documentation

- [Quick Start Guide](docs/quick-start.md)
- [CLI Reference](docs/cli-reference.md)
- [Multiline Directives](docs/multiline-directives.md)
- [Developer Guide](docs/dev/index.md)

## License

MIT License - see [LICENSE](LICENSE) file for details.