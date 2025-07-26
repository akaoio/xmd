# 🔧 XMD Troubleshooting Guide

Common issues and solutions for XMD processing.

## Fixed Issues (v1.0.0)

### ✅ Segmentation Fault with --no-exec

**Issue:** Using `--no-exec` option caused segmentation fault.

**Solution:** Fixed in v1.0.0 with proper memory allocation and NULL checks.

```bash
# Now works correctly
xmd process document.md --no-exec
```

### ✅ Variables Not Working from Command Line

**Issue:** Variables set with `-v` option were not being used in document processing.

**Solution:** Fixed in v1.0.0 with proper variable storage and propagation.

```bash
# Now works correctly
xmd process template.md -v name="Alice" -v env="production"

# Variables {{name}} and {{env}} are properly substituted
```

### ✅ Config File Validation Missing

**Issue:** `--config` option accepted non-existent files without error.

**Solution:** Fixed in v1.0.0 with file existence validation.

```bash
# Now properly validates config file exists
xmd process doc.md --config missing.conf
# Error: Cannot open config file 'missing.conf'
```

### ✅ Output Formats Not Working

**Issue:** All `--format` options produced identical output.

**Solution:** Fixed in v1.0.0 with proper format-specific processing.

```bash
# Now produces different outputs
xmd process doc.md --format html    # HTML document with CSS
xmd process doc.md --format json    # Structured JSON response
xmd process doc.md --format markdown # Plain markdown (default)
```

### ✅ Trace Functionality Not Working

**Issue:** `--trace` option was parsed but did nothing.

**Solution:** Fixed in v1.0.0 with integration to debugger trace system.

```bash
# Now generates detailed trace files
xmd process doc.md --trace
# Creates doc.md.trace with processing details
```

## Current Issues & Solutions

### Variables Not Substituted

**Symptoms:**
- `{{variable}}` appears literally in output
- No error messages

**Diagnosis:**
```bash
# Check if variable is set
xmd process doc.md -v debug=true --debug

# Use trace to see variable processing
xmd process doc.md --trace
```

**Solutions:**
1. **Check variable syntax:**
   ```markdown
   <!-- Correct -->
   <!-- xmd:set name="Alice" -->
   Hello {{name}}!
   
   <!-- Incorrect -->
   <!-- xmd:set name=Alice -->  <!-- Missing quotes for strings -->
   Hello {name}!               <!-- Wrong interpolation syntax -->
   ```

2. **Verify command-line variables:**
   ```bash
   # Correct format
   xmd process doc.md -v name="Alice" -v count=5
   
   # Incorrect
   xmd process doc.md -v name Alice    # Missing = 
   xmd process doc.md -v "name=Alice"  # Don't quote the whole thing
   ```

### Range Syntax Not Working

**Symptoms:**
- `<!-- xmd:for i in 1..5 -->` doesn't expand
- Loop variable appears literally

**Solutions:**
1. **Use correct HTML comment syntax:**
   ```markdown
   <!-- Correct -->
   <!-- xmd:for i in 1..3 -->
   Item {{i}}
   <!-- xmd:endfor -->
   
   <!-- Incorrect -->
   xmd:for i in 1..3    <!-- Missing HTML comment wrapper -->
   <!-- xmd:for i in 1...3 -->  <!-- Triple dots not supported -->
   ```

2. **Check range limits:**
   ```markdown
   <!-- This works (under 1000 limit) -->
   <!-- xmd:for i in 1..100 -->
   
   <!-- This is skipped (over limit) -->
   <!-- xmd:for i in 1..5000 -->
   ```

### Command Execution Not Working

**Symptoms:**
- `<!-- xmd:exec command -->` appears literally
- No command output

**Solutions:**
1. **Check if commands are disabled:**
   ```bash
   # Don't use --no-exec if you want commands to run
   xmd process doc.md              # Commands enabled
   xmd process doc.md --no-exec    # Commands disabled
   ```

2. **Verify command exists:**
   ```markdown
   <!-- Test with simple command -->
   <!-- xmd:exec echo "test" -->
   
   <!-- Check command exists -->
   <!-- xmd:exec which ls -->
   ```

### File Processing Errors

**Symptoms:**
- "Failed to process file" error
- Empty output

**Diagnosis:**
```bash
# Check file exists and is readable
ls -la document.md

# Validate syntax first
xmd validate document.md

# Use debug mode for details
xmd process document.md --debug
```

**Solutions:**
1. **File permissions:**
   ```bash
   # Ensure file is readable
   chmod +r document.md
   ```

2. **File encoding:**
   ```bash
   # Check for binary/encoding issues
   file document.md
   
   # Convert if needed
   iconv -f utf-8 -t utf-8 document.md
   ```

### Output Format Issues

**Symptoms:**
- Unexpected output format
- HTML tags in markdown output
- JSON parsing errors

**Solutions:**
1. **Specify format explicitly:**
   ```bash
   # Be explicit about desired format
   xmd process doc.md --format markdown
   xmd process doc.md --format html
   xmd process doc.md --format json
   ```

2. **Validate JSON output:**
   ```bash
   # Check JSON is valid
   xmd process doc.md --format json | jq .
   ```

## Performance Issues

### Slow Processing

**Symptoms:**
- Long processing times
- High memory usage

**Diagnosis:**
```bash
# Check processing stats
xmd process doc.md --debug

# Generate trace to find bottlenecks
xmd process doc.md --trace
```

**Solutions:**
1. **Optimize loops:**
   ```markdown
   <!-- Avoid large ranges -->
   <!-- xmd:for i in 1..10 -->     <!-- Good -->
   <!-- xmd:for i in 1..1000 -->   <!-- Slower -->
   ```

2. **Cache expensive operations:**
   ```markdown
   <!-- Cache command results -->
   <!-- xmd:set timestamp=now -->
   Time: {{timestamp}}  <!-- Reuse instead of multiple exec calls -->
   ```

3. **Reduce command execution:**
   ```bash
   # Use --no-exec for content-only processing
   xmd process doc.md --no-exec
   ```

## Debug Strategies

### General Debugging Steps

1. **Start simple:**
   ```bash
   # Test with minimal document
   echo "Hello {{name}}" | xmd process /dev/stdin -v name="World"
   ```

2. **Use validation:**
   ```bash
   # Check syntax first
   xmd validate document.md
   ```

3. **Enable tracing:**
   ```bash
   # See detailed processing
   xmd process document.md --trace
   cat document.md.trace
   ```

4. **Check debug output:**
   ```bash
   # View processing stats
   xmd process document.md --debug
   ```

### Systematic Debugging

1. **Isolate the problem:**
   - Comment out sections to find problematic code
   - Test with minimal examples
   - Check each directive individually

2. **Verify assumptions:**
   - Check variable values with debug output
   - Verify command execution with simple tests
   - Validate file paths and permissions

3. **Use incremental testing:**
   - Start with basic processing
   - Add complexity gradually
   - Test each new feature

## Getting Help

### Information to Include

When reporting issues, include:

1. **XMD version:**
   ```bash
   xmd version
   ```

2. **Command used:**
   ```bash
   xmd process document.md -v var=value --format html
   ```

3. **Input document (minimal example):**
   ```markdown
   <!-- xmd:set test="value" -->
   Result: {{test}}
   ```

4. **Expected vs actual output**

5. **Error messages**

6. **Debug information:**
   ```bash
   xmd process document.md --debug --trace
   ```

### Support Channels

- 📖 **Documentation**: [akaoio.github.io/xmd](https://akaoio.github.io/xmd/)
- 💬 **Discord**: [discord.gg/xmd](https://discord.gg/xmd)
- 🐛 **Issues**: [github.com/akaoio/xmd/issues](https://github.com/akaoio/xmd/issues)
- 💡 **Discussions**: [github.com/akaoio/xmd/discussions](https://github.com/akaoio/xmd/discussions)

### Before Reporting

1. Check this troubleshooting guide
2. Search existing issues on GitHub
3. Test with minimal example
4. Include all requested information