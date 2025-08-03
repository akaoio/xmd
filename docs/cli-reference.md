# CLI Reference

## Commands

### `xmd <file> [options]`

Process an XMD file and output the result.

```bash
# Basic usage
xmd document.md

# With output file
xmd document.md -o output.md

# With variables
xmd template.md -v env=production -v version=1.2.0
```

### `xmd watch <source_dir> <output_dir> [options]`

Watch source directory for changes and auto-process files to output directory.

```bash
# Watch source directory and output to dist/
xmd watch src/ dist/

# Watch with file patterns
xmd watch docs/ build/ --pattern "*.md"

# Watch with custom file monitoring
xmd watch .xmd/src/ .xmd/dist/
```

### `xmd version`

Display version information with build details.

```bash
xmd version
# Output: XMD version 0.0.2
#         Built on Jul 28 2025
```

### `xmd upgrade`

Upgrade XMD to the latest release from GitHub.

```bash
# Check for updates and upgrade if available
xmd upgrade

# Show help for upgrade command
xmd upgrade --help
```

### `xmd --help`

Display help information.

```bash
xmd --help
```

## Options

### `-o, --output <file>`

Specify output file. Default: stdout.

```bash
xmd doc.md -o result.md
```

### `-v, --variable <key=value>`

Set variables. Can be used multiple times.

```bash
xmd doc.md -v name="Alice" -v debug=true
```

### `--watch`

Watch mode for live development.

```bash
xmd doc.md --watch
```

### `--format <format>`

Output format: `markdown` (default), `html`, `json`.

```bash
xmd doc.md --format html
```

### `--no-exec`

Disable command execution for security.

```bash
xmd untrusted.md --no-exec
```

## Examples

### Basic Processing

```bash
# Process to stdout
xmd document.md

# Process to file  
xmd document.md -o output.md
```

### Advanced Scripting

```bash
# Template with array processing
cat > template.md << 'EOF'
<!-- xmd 
set technologies = ["C", "JavaScript", "Go"]
set content = ""
for tech in technologies
    content += "- " + tech + " support\n"
-->
{{content}}
EOF

xmd template.md
# Output: 
# - C support
# - JavaScript support  
# - Go support
```

### With Variables

```bash
# Template with variables
echo '# Hello {{name}}!' > template.md

# Process with variables
xmd template.md -v name="World"
# Output: # Hello World!
```

### Watch Mode for Development

```bash
# Watch source directory for real-time updates
xmd watch src/ dist/

# Watch with automatic reload
xmd watch .xmd/src/ .xmd/dist/

# Combined with web server for live development
xmd watch docs/ build/ &
cd build && python -m http.server 8000
```

### Dynamic Documentation

```bash
# Multi-file documentation generation
cat > docs.md << 'EOF'
<!-- xmd 
set sections = ["intro.md", "api.md", "examples.md"] 
set guide = "# Complete Guide\n\n"
for section in sections
    guide += import section + "\n\n"
-->
{{guide}}
EOF

xmd docs.md -o complete-guide.md
```

## Exit Codes

- `0` - Success
- `1` - Error (invalid arguments, file not found, etc.)