# 🔢 XMD Range Syntax Guide

XMD supports powerful range expressions in for loops, allowing you to iterate over numeric sequences without defining arrays.

## Basic Range Syntax  

### Simple Numeric Ranges

```markdown
<!-- xmd for i in 1..5 -->
Item {{i}}
<!-- xmd endfor -->
```

**Output:**
```
Item 1
Item 2  
Item 3
Item 4
Item 5
```

### Reverse Ranges

```markdown
<!-- xmd for i in 5..1 -->
Countdown: {{i}}
<!-- xmd endfor -->
```

**Output:**
```
Countdown: 5
Countdown: 4
Countdown: 3
Countdown: 2
Countdown: 1
```

## Variable-Based Ranges

### Variables as Range Bounds

```markdown
<!-- xmd set start=3 -->
<!-- xmd set end=7 -->

<!-- xmd for i in start..end -->
Port 808{{i}}: Checking...
<!-- xmd endfor -->
```

**Output:**
```
Port 8083: Checking...
Port 8084: Checking...
Port 8085: Checking...
Port 8086: Checking...
Port 8087: Checking...
```

### Mixed Variable and Literal

```markdown
<!-- xmd set max=4 -->

<!-- Left variable, right literal -->
<!-- xmd for i in max..10 -->
Step {{i}}
<!-- xmd endfor -->

<!-- Left literal, right variable -->
<!-- xmd for i in 1..max -->
Phase {{i}}
<!-- xmd endfor -->
```

## Advanced Patterns

### Dynamic Range Generation

```markdown
<!-- xmd set servers=3 -->
<!-- xmd set start_port=8080 -->

## Server Configuration

<!-- xmd for i in 1..servers -->
### Server {{i}}
- Port: {{start_port + i - 1}}
- Config: server{{i}}.conf
<!-- xmd endfor -->
```

### Nested Ranges

```markdown
<!-- xmd for cluster in 1..2 -->
## Cluster {{cluster}}

<!-- xmd for node in 1..3 -->
### Node cluster{{cluster}}-node{{node}}
- IP: 192.168.{{cluster}}.{{node}}
- Status: Active
<!-- xmd endfor -->
<!-- xmd endfor -->
```

**Output:**
```
## Cluster 1

### Node cluster1-node1
- IP: 192.168.1.1
- Status: Active

### Node cluster1-node2  
- IP: 192.168.1.2
- Status: Active

### Node cluster1-node3
- IP: 192.168.1.3
- Status: Active

## Cluster 2

### Node cluster2-node1
- IP: 192.168.2.1
- Status: Active
...
```

## Practical Examples

### Port Scanning Report

```markdown
<!-- xmd set base_port=8080 -->
<!-- xmd set port_count=5 -->

# Port Status Report

<!-- xmd for i in 0..port_count -->
<!-- xmd set current_port=base_port + i -->
- Port {{current_port}}: <!-- xmd exec netstat -ln | grep :{{current_port}} >/dev/null && echo "🟢 Open" || echo "🔴 Closed" -->
<!-- xmd endfor -->
```

### Numbered List Generation

```markdown
<!-- xmd set total_items=10 -->

# Top {{total_items}} Issues

<!-- xmd for rank in 1..total_items -->
{{rank}}. Issue #{{rank * 100}} - Priority: <!-- xmd if rank <= 3 -->🔴 High<!-- xmd elif rank <= 7 -->🟡 Medium<!-- xmd else -->🟢 Low<!-- xmd endif -->
<!-- xmd endfor -->
```

### Load Balancer Configuration

```markdown
<!-- xmd set lb_count=3 -->
<!-- xmd set backend_per_lb=4 -->

# Load Balancer Configuration

<!-- xmd for lb in 1..lb_count -->
## Load Balancer {{lb}}

### Backends
<!-- xmd for backend in 1..backend_per_lb -->
- Backend {{backend}}: 10.{{lb}}.0.{{backend}}:8080
<!-- xmd endfor -->
<!-- xmd endfor -->
```

## Range Limits and Validation

### Safety Limits

XMD includes safety limits to prevent infinite loops:

- **Maximum range size**: 1000 items
- **Automatic validation**: Invalid ranges are skipped
- **Memory protection**: Large ranges are handled efficiently

### Error Handling

```markdown
<!-- This will be skipped safely -->
<!-- xmd for i in 1..10000 -->
This won't process - range too large
<!-- xmd endfor -->

<!-- This will work -->  
<!-- xmd for i in 1..100 -->
Item {{i}}
<!-- xmd endfor -->
```

## Range Syntax Rules

### Valid Patterns

✅ **Supported:**
- `1..5` - Literal numbers
- `start..end` - Variable bounds  
- `var..10` - Mixed variable/literal
- `5..var` - Mixed literal/variable
- `a..z` - Character ranges (future)

### Whitespace Handling

All of these are equivalent:

```markdown
<!-- xmd for i in 1..5 -->
<!-- xmd for i in 1 .. 5 -->  
<!-- xmd for i in 1.. 5 -->
<!-- xmd for i in 1 ..5 -->
```

### Invalid Patterns

❌ **Not supported:**
- `1...5` - Triple dots
- `1-5` - Dash notation
- `1,2,3,4,5` - Comma separated (use arrays instead)
- `1:5` - Colon notation

## Comparison with Arrays

### When to Use Ranges

**Use ranges for:**
- Sequential numbers
- Simple iterations
- Port/ID generation  
- Countdown timers
- Numbered lists

```markdown
<!-- Good: Simple sequence -->
<!-- xmd for i in 1..10 -->
Step {{i}}
<!-- xmd endfor -->
```

### When to Use Arrays

**Use arrays for:**
- Non-sequential data
- String collections
- Complex objects
- Mixed data types

```markdown
<!-- Good: Non-sequential data -->
<!-- xmd set servers=["web1", "api2", "db3"] -->
<!-- xmd for server in servers -->
Server: {{server}}
<!-- xmd endfor -->
```

## Command-Line Integration

Ranges work seamlessly with command-line variables:

```bash
# Set range bounds from command line
xmd process report.md -v start=1 -v end=10

# Document uses variables in range
<!-- xmd for i in start..end -->
Report item {{i}}
<!-- xmd endfor -->
```

## Performance Notes

- Ranges are converted to arrays internally for processing
- Small ranges (< 100 items) have minimal overhead
- Large ranges use memory proportional to size
- Variable resolution happens once per range

## Best Practices

1. **Keep ranges reasonable** - Under 100 items for best performance
2. **Use variables for dynamic ranges** - Makes templates reusable
3. **Validate bounds** - Ensure start <= end for predictable behavior
4. **Consider arrays for complex data** - Don't force ranges for non-sequential data
5. **Test with tracing** - Use `--trace` to debug range processing

```bash
# Debug range processing
xmd process template.md --trace -v start=5 -v end=10
```

This generates detailed trace information showing how ranges are processed and converted.