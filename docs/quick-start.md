# Quick Start Guide

## Installation

```bash
# One-line install
curl -fsSL https://raw.githubusercontent.com/akaoio/xmd/main/install.sh | bash

# Verify installation
xmd --version
```

## Basic Usage

### 1. Create a simple XMD file

Create `example.md`:
```markdown
<!-- xmd:
set name = "Developer"
set date = exec date +"%Y-%m-%d"
-->

# Hello {{name}}!

Today is {{date}}.

<!-- xmd: for i in 1..3 -->
- Item {{i}}
<!-- xmd: endfor -->
```

### 2. Process the file

```bash
# Output to stdout
xmd example.md

# Save to file
xmd example.md -o output.md

# Use with variables
xmd example.md -v name="Alice"
```

## Key Concepts

### Variables
```markdown
<!-- xmd: set user = "John" -->
<!-- xmd: set count = 42 -->
<!-- xmd: set active = true -->
```

### Command Execution
```markdown
<!-- xmd: exec ls -la -->
<!-- xmd: set files = exec find . -name "*.md" -->
```

### Functions
```markdown
<!-- xmd:
set data = "Hello World"
print(data)
-->

<!-- xmd: cmd("echo 'Hello from cmd!'") -->
```

### Multiline Blocks
```markdown
<!-- xmd:
set name = "Project"
set version = "1.0.0"
set author = exec git config user.name
print(name)
print(version)
print(author)
-->
```

## Next Steps

- [CLI Reference](cli-reference.md) - All command options
- [Multiline Directives](multiline-directives.md) - Advanced syntax
- [Examples](../examples/) - Real-world use cases