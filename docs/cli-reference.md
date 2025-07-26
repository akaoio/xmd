# 🔧 XMD Command Line Reference

Complete reference for XMD command-line interface.

## Commands

### `xmd process <file> [options]`

Process an XMD file and output the result.

```bash
# Basic usage
xmd process document.md

# With output file
xmd process document.md -o output.md

# With variables
xmd process template.md -v env=production -v version=1.2.0
```

**Arguments:**
- `<file>` - Input XMD file to process (required)

### `xmd validate <file>`

Validate XMD syntax without processing.

```bash
xmd validate document.md
```

**Arguments:**
- `<file>` - Input XMD file to validate (required)

### `xmd version`

Display version information.

```bash
xmd version
# Output: XMD v1.0.0
```

### `xmd help`

Display help information.

```bash
xmd help
```

## Options

### `-o, --output <file>`

Specify output file. If not provided, output goes to stdout.

```bash
xmd process doc.md -o result.md
xmd process doc.md --output result.html
```

### `-v, --variable <key=value>`

Set variables that can be used in the document. Can be used multiple times.

```bash
# Single variable
xmd process doc.md -v name="Alice"

# Multiple variables
xmd process doc.md -v env="prod" -v region="us-east" -v debug=true

# Variables in document: {{name}}, {{env}}, {{region}}, {{debug}}
```

### `--config <file>`

Use a configuration file. The file must exist or an error will be shown.

```bash
xmd process doc.md --config settings.conf
```

### `--format <format>`

Specify output format. Valid formats: `markdown`, `html`, `json`

```bash
# Markdown (default)
xmd process doc.md --format markdown

# HTML with full document structure and CSS
xmd process doc.md --format html

# JSON with metadata
xmd process doc.md --format json
```

**Format Details:**

- **`markdown`**: Default format, outputs processed content as-is
- **`html`**: Complete HTML document with DOCTYPE, head, CSS styling
- **`json`**: Structured JSON with status, format, processor version, and content

### `--trace`  

Enable execution tracing. Creates a `.trace` file with detailed processing steps.

```bash
xmd process doc.md --trace
# Creates doc.md.trace

xmd process doc.md -o output.md --trace  
# Creates output.md.trace
```

The trace file contains:
- Line-by-line processing details
- Directive detection (variables, conditionals, loops)
- Variable interpolation tracking
- Processing summary

### `--debug`

Enable debug mode. Shows processing statistics on stderr.

```bash
xmd process doc.md --debug
# Output includes:
# Processing time: 15 ms
# Memory used: 2048 bytes
```

### `--no-exec`

Disable command execution for security. XMD directives like `<!-- xmd:exec -->` will be ignored.

```bash
xmd process untrusted.md --no-exec
```

## Examples

### Basic Processing

```bash
# Process and display to stdout
xmd process document.md

# Process to file
xmd process document.md -o output.md
```

### With Variables

```bash
# Template with variables
echo '# Hello {{name}}! Version: {{version}}' > template.md

# Process with variables
xmd process template.md -v name="World" -v version="1.0"
# Output: # Hello World! Version: 1.0
```

### Different Output Formats

```bash
# HTML output
xmd process doc.md --format html > output.html

# JSON output  
xmd process doc.md --format json > output.json

# Example JSON structure:
# {
#   "status": "success",
#   "format": "json",
#   "processor": "XMD v1.0.0", 
#   "content": "processed content"
# }
```

### Debugging

```bash
# Generate trace for debugging
xmd process complex.md --trace
cat complex.md.trace  # View detailed processing steps

# Debug mode with performance info
xmd process doc.md --debug

# Full debugging
xmd process doc.md --trace --debug --format json
```

### Security

```bash
# Safe processing (no command execution)
xmd process untrusted.md --no-exec

# With configuration file
xmd process doc.md --config secure.conf --no-exec
```

### Real-World Examples

```bash
# DevOps status report
xmd process status-template.md -v env="production" --format html -o status.html

# API documentation with live examples
xmd process api-template.md -v base_url="https://api.example.com" --trace

# System monitoring report  
xmd process monitoring.md --format json | jq .content

# Secure document processing
xmd process user-content.md --no-exec --format html
```

## Exit Codes

- `0` - Success
- `1` - Error (invalid arguments, file not found, processing failed, etc.)

## Error Handling

XMD provides clear error messages for common issues:

```bash
# Invalid format
$ xmd process doc.md --format invalid
Error: Invalid format 'invalid'. Valid formats: markdown, html, json

# Missing config file  
$ xmd process doc.md --config missing.conf
Error: Cannot open config file 'missing.conf'

# Missing argument
$ xmd process doc.md --variable
Error: --variable requires an argument

# Invalid variable format
$ xmd process doc.md -v invalid
Error: Variable must be in key=value format
```

## Performance Notes

- XMD is optimized for speed - most documents process in under 100ms
- Use `--debug` to see actual processing time and memory usage
- Large documents or complex logic may benefit from `--trace` for optimization
- The `--no-exec` option improves performance by skipping command execution

## Security Considerations

- Always use `--no-exec` when processing untrusted content
- Validate input files with `xmd validate` before processing
- Use configuration files to set detailed security policies
- Review trace files to understand what commands would be executed