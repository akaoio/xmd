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

### `xmd watch <dir> [options]`

Watch directory for changes and auto-process files.

```bash
# Watch directory
xmd watch docs/

# Watch with output directory
xmd watch docs/ dist/
```

### `xmd --version`

Display version information.

```bash
xmd --version
# Output: XMD v1.0.0
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

### With Variables

```bash
# Template with variables
echo '# Hello {{name}}!' > template.md

# Process with variables
xmd template.md -v name="World"
# Output: # Hello World!
```

### Different Formats

```bash
# HTML output
xmd doc.md --format html > output.html

# JSON output
xmd doc.md --format json > output.json
```

### Watch Mode

```bash
# Watch single file
xmd doc.md --watch

# Watch directory
xmd watch docs/ dist/
```

## Exit Codes

- `0` - Success
- `1` - Error (invalid arguments, file not found, etc.)