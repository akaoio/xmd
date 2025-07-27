# Multiline Directives

XMD supports clean multiline syntax for complex operations.

## Basic Syntax

```markdown
<!-- xmd:
directive1
directive2
directive3
-->
```

## Examples

### Variable Declaration

```markdown
<!-- xmd:
set name = "Project X"
set version = "2.0.0"
set author = "Development Team"
set date = exec date +"%Y-%m-%d"
-->
```

### Command Execution

```markdown
<!-- xmd:
set hostname = exec hostname
set kernel = exec uname -r
set uptime = exec uptime -p
-->

System: {{hostname}} ({{kernel}})
Uptime: {{uptime}}
```

### Functions

```markdown
<!-- xmd:
set user = exec whoami
set home = exec echo $HOME
print(user)
print(home)
-->
```

### Control Flow

```markdown
<!-- xmd:
set env = "production"
set debug = false
-->

<!-- xmd: if env == "production" -->
⚠️ Production Environment
<!-- xmd: endif -->

<!-- xmd: if debug -->
Debug output enabled
<!-- xmd: else -->
Debug output disabled
<!-- xmd: endif -->
```

### Loops with Functions

```markdown
<!-- xmd:
set services = ["nginx", "mysql", "redis"]
-->

<!-- xmd: for service in services -->
<!-- xmd:
set status = exec systemctl is-active {{service}} 2>/dev/null || echo "inactive"
print(service)
print(": ")
print(status)
-->
<!-- xmd: endfor -->
```

## Advanced Examples

### Project Status Report

```markdown
<!-- xmd:
set project = "MyApp"
set branch = exec git branch --show-current
set commits = exec git rev-list --count HEAD
set lastCommit = exec git log -1 --pretty=format:"%h - %s"
-->

# {{project}} Status

- Branch: {{branch}}
- Total commits: {{commits}}
- Last commit: {{lastCommit}}

<!-- xmd:
print("Generated at: ")
cmd("date '+%Y-%m-%d %H:%M:%S'")
-->
```

### Dynamic Configuration

```markdown
<!-- xmd:
set config = {
  "app": "WebServer",
  "port": 8080,
  "ssl": true,
  "workers": 4
}
-->

<!-- xmd: for key in ["app", "port", "ssl", "workers"] -->
{{key}}: {{config[key]}}
<!-- xmd: endfor -->
```

## Best Practices

1. **Group Related Operations**: Keep related directives together in multiline blocks
2. **Use Functions for Output**: `print()` and `cmd()` work great in multiline blocks
3. **Combine with Loops**: Multiline blocks inside loops for complex iterations
4. **Clear Variable Names**: Use descriptive names for better readability

## Supported Directives

All XMD directives work in multiline blocks:

- `set` - Variable assignment
- `exec` - Command execution  
- `if/elif/else/endif` - Conditionals
- `for/endfor` - Loops
- `print()` - Output function
- `cmd()` - Command function
- `import` - Module imports