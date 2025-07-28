# Quick Start Guide

## Installation

```bash
# One-line install (downloads latest release)
curl -fsSL https://raw.githubusercontent.com/akaoio/xmd/main/install.sh | bash

# Verify installation
xmd version
```

## Updating XMD

```bash
# Upgrade to latest release
xmd upgrade

# Check current version
xmd version
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

# Watch mode for real-time updates
xmd watch src/ dist/

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

### Advanced Scripting Features

#### Array Literals and Iteration
```markdown
<!-- xmd:
set technologies = ["C", "JavaScript", "Python", "Go"]
set content = ""
for tech in technologies
    content += "- **" + tech + "** programming language\n"
-->
{{content}}
```

#### Dynamic Imports
```markdown
<!-- xmd:
set sections = ["intro.md", "setup.md", "usage.md"]
set documentation = ""
for section in sections
    documentation += import section + "\n\n"
-->
{{documentation}}
```

#### String Concatenation
```markdown
<!-- xmd:
set title = "XMD Guide"
set version = "v2.0"
set header = "# " + title + " " + version
-->
{{header}}
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

### Complex Multiline Scripts
```markdown
<!-- xmd:
set project_files = ["README.md", "CHANGELOG.md", "LICENSE.md"]
set toc = "# Table of Contents\n\n"
for file in project_files
    toc += "- [" + file + "](" + file + ")\n"
-->
{{toc}}
```

## Next Steps

- [CLI Reference](cli-reference.md) - All command options
- [Multiline Directives](multiline-directives.md) - Advanced syntax
- [Examples](../examples/) - Real-world use cases