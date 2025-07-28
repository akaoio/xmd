# XMD - eXtended MarkDown

A powerful markdown preprocessor that adds programming capabilities to markdown files with advanced scripting features.

## Features

- **Advanced Scripting**: Array literals, for loops, string concatenation with `+` operator
- **Dynamic Imports**: Import files using variables and expressions
- **Variables & Templates**: Define and use variables throughout your markdown
- **Command Execution**: Run shell commands and embed their output with dynamic buffer allocation
- **Control Flow**: If/else conditions and array iteration loops
- **Functions**: Built-in print() and cmd() functions
- **Multiline Support**: Clean syntax for complex operations with script-like blocks
- **Dynamic Content**: Generate content programmatically with full expression evaluation
- **Watch Mode**: Real-time file processing and monitoring

## Quick Start

```bash
# Install (downloads latest release)
curl -fsSL https://raw.githubusercontent.com/akaoio/xmd/main/install.sh | bash

# Verify installation
xmd version

# Process a file
xmd input.md -o output.md

# Process to stdout
xmd input.md

# Upgrade to latest version
xmd upgrade
```

## Syntax Examples

### Variables
```markdown
<!-- xmd: set name = "World" -->
Hello, {{name}}!
```

### Advanced Scripting with Arrays
```markdown
<!-- xmd:
set items = ["apple", "banana", "cherry"]
set result = ""
for item in items
    result += "- " + item + "\n"
-->
{{result}}
```

### Dynamic Imports
```markdown
<!-- xmd:
set files = ["config.md", "setup.md", "deploy.md"]
set content = ""
for file in files
    content += "## " + import file + "\n\n"
-->
{{content}}
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

### Watch Mode
```bash
# Watch source directory and output to dist/
xmd watch src/ dist/

# Watch with custom patterns
xmd watch docs/ build/ --pattern "*.md"
```

## Documentation

- [Quick Start Guide](docs/quick-start.md)
- [CLI Reference](docs/cli-reference.md)
- [Multiline Directives](docs/multiline-directives.md)
- [Developer Guide](docs/dev/index.md)

## License

MIT License - see [LICENSE](LICENSE) file for details.