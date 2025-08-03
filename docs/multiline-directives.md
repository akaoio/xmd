# Multiline Directives

XMD supports clean multiline syntax for complex operations, including advanced scripting features like array literals, for loops with bodies, and dynamic imports.

## Basic Syntax

```markdown
<!-- xmd 
directive1
directive2
directive3
-->
```

## Advanced Script Blocks

XMD now supports script-like syntax with arrays, loops, and string concatenation:

```markdown
<!-- xmd 
set items = ["file1.md", "file2.md", "file3.md"]
set content = ""
for item in items
    content += "### " + import item + "\n\n"
-->
{{content}}
```

## Examples

### Variable Declaration

```markdown
<!-- xmd 
set name = "Project X"
set version = "2.0.0"
set author = "Development Team"
set date = exec date +"%Y-%m-%d"
-->
```

### Command Execution

```markdown
<!-- xmd 
set hostname = exec hostname
set kernel = exec uname -r
set uptime = exec uptime -p
-->

System: {{hostname}} ({{kernel}})
Uptime: {{uptime}}
```

### Functions

```markdown
<!-- xmd 
set user = exec whoami
set home = exec echo $HOME
print(user)
print(home)
-->
```

### Control Flow

```markdown
<!-- xmd 
set env = "production"
set debug = false
-->

<!-- xmd if env == "production" -->
⚠️ Production Environment
<!-- xmd endif -->

<!-- xmd if debug -->
Debug output enabled
<!-- xmd else -->
Debug output disabled
<!-- xmd endif -->
```

### Advanced Array Processing

```markdown
<!-- xmd 
set services = ["nginx", "mysql", "redis", "postgresql"]
set report = "# Service Status Report\n\n"
for service in services
    set status = exec systemctl is-active service 2>/dev/null || echo "inactive"
    report += "- **" + service + "**: " + status + "\n"
-->
{{report}}
```

### Dynamic Documentation Generation

```markdown
<!-- xmd 
set chapters = ["introduction.md", "setup.md", "usage.md", "api.md"]
set documentation = "# Complete Guide\n\n"
for chapter in chapters
    documentation += import chapter + "\n\n---\n\n"
-->
{{documentation}}
```

## Advanced Examples

### Project Status Report

```markdown
<!-- xmd 
set project = "MyApp"
set branch = exec git branch --show-current
set commits = exec git rev-list --count HEAD
set lastCommit = exec git log -1 --pretty=format:"%h - %s"
-->

# {{project}} Status

- Branch: {{branch}}
- Total commits: {{commits}}
- Last commit: {{lastCommit}}

<!-- xmd 
print("Generated at: ")
cmd("date '+%Y-%m-%d %H:%M:%S'")
-->
```

### Dynamic Configuration

```markdown
<!-- xmd 
set config = {
  "app": "WebServer",
  "port": 8080,
  "ssl": true,
  "workers": 4
}
-->

<!-- xmd for key in ["app", "port", "ssl", "workers"] -->
{{key}}: {{config[key]}}
<!-- xmd endfor -->
```

## Best Practices

1. **Group Related Operations**: Keep related directives together in multiline blocks
2. **Use Functions for Output**: `print()` and `cmd()` work great in multiline blocks
3. **Combine with Loops**: Multiline blocks inside loops for complex iterations
4. **Clear Variable Names**: Use descriptive names for better readability

## Supported Features

### Core Directives
- `set` - Variable assignment with array literals
- `exec` - Command execution with dynamic buffer allocation
- `if/elif/else/endif` - Conditionals
- `print()` - Output function
- `cmd()` - Command function
- `import` - Module imports with variable support

### Advanced Scripting Features
- **Array Literals**: `["item1", "item2", "item3"]`
- **For Loops with Bodies**: Multi-line loop bodies with indentation
- **String Concatenation**: Use `+` operator to combine strings
- **Dynamic Imports**: `import variable_name` where variable contains filename
- **Variable Initialization**: `set varname` without assignment
- **Compound Assignment**: `variable += "additional content"`

### Script Block Detection
XMD automatically detects advanced script syntax and uses the enhanced processor when:
- Array literals are present: `["item1", "item2"]`
- For loops with bodies are used: `for item in array`
- Compound assignment operators are used: `+=`

### Expression Evaluation
- String literals with escape sequences: `"Hello\nWorld"`
- Variable references in expressions
- Import calls within concatenation: `"### " + import filename + "\n"`
- Complex expressions: `result += prefix + import file + suffix`