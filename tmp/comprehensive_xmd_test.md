# Comprehensive XMD Feature Test

This document tests all possible XMD features and directives for complete compliance testing.

## 1. Variable Management

### Basic Variable Setting and Referencing
<!-- xmd:set name="XMD" -->
<!-- xmd:set version="1.0.0" -->
<!-- xmd:set author="Test Suite" -->
<!-- xmd:set year=2025 -->
<!-- xmd:set pi=3.14159 -->
<!-- xmd:set enabled=true -->
<!-- xmd:set disabled=false -->

Welcome to {{name}} version {{version}} by {{author}} in {{year}}.
Mathematical constant pi: {{pi}}
Boolean values: enabled={{enabled}}, disabled={{disabled}}

### Complex Data Types
<!-- xmd:set config={"env": "production", "debug": false, "timeout": 30} -->
<!-- xmd:set servers=["web1", "web2", "db1"] -->
<!-- xmd:set metadata={"tags": ["test", "demo"], "priority": "high", "nested": {"level": 2}} -->

Environment: {{config.env}}
Debug mode: {{config.debug}}
Timeout: {{config.timeout}} seconds
Servers: {{servers}}
Tags: {{metadata.tags}}
Nested level: {{metadata.nested.level}}

### Environment Variables
<!-- xmd:set home_dir="${HOME}" -->
<!-- xmd:set user="${USER}" -->
<!-- xmd:set path="${PATH}" -->

Home directory: {{home_dir}}
Current user: {{user}}
System PATH: {{path}}

## 2. Control Flow - Conditionals

### Basic If Statements
<!-- xmd:if enabled -->
This content is shown because enabled is true.
<!-- xmd:endif -->

<!-- xmd:if disabled -->
This should never be shown.
<!-- xmd:else -->
This is shown because disabled is false.
<!-- xmd:endif -->

### Complex Conditionals
<!-- xmd:if config.env == "production" -->
## Production Environment Detected

Running in production mode with the following settings:
- Debug: {{config.debug}}
- Timeout: {{config.timeout}}s
<!-- xmd:elif config.env == "staging" -->
## Staging Environment
<!-- xmd:else -->
## Development Environment
<!-- xmd:endif -->

### Nested Conditionals
<!-- xmd:if year >= 2025 -->
<!-- xmd:if pi > 3 -->
Both conditions are true: year={{year}} and pi={{pi}}
<!-- xmd:endif -->
<!-- xmd:endif -->

### Complex Boolean Logic
<!-- xmd:if (enabled && !disabled) || (year > 2020 && version == "1.0.0") -->
Complex boolean logic evaluation successful.
<!-- xmd:endif -->

## 3. Loops and Iterations

### Basic For Loop
<!-- xmd:for server in servers -->
- Server: {{server}}
<!-- xmd:endfor -->

### For Loop with Index
<!-- xmd:for item, index in metadata.tags -->
{{index + 1}}. Tag: {{item}}
<!-- xmd:endfor -->

### Range-based For Loop
<!-- xmd:for i in range(1, 6) -->
Count: {{i}}
<!-- xmd:endfor -->

### Nested Loops
<!-- xmd:for env in ["dev", "staging", "prod"] -->
### {{env}} Environment
<!-- xmd:for server in servers -->
- {{env}}-{{server}}
<!-- xmd:endfor -->
<!-- xmd:endfor -->

### While Loop
<!-- xmd:set counter=0 -->
<!-- xmd:while counter < 3 -->
Counter value: {{counter}}
<!-- xmd:set counter=counter+1 -->
<!-- xmd:endwhile -->

## 4. Command Execution

### Basic Command Execution
Current date: <!-- xmd:exec date -->

Current working directory: <!-- xmd:exec pwd -->

System information: <!-- xmd:exec uname -a -->

### Command with Output Formatting
Available disk space:
```
<!-- xmd:exec df -h -->
```

### Command with Variable Substitution
<!-- xmd:set filename="test.txt" -->
<!-- xmd:exec echo "Creating file {{filename}}" -->

### Command with Error Handling
<!-- xmd:try -->
<!-- xmd:exec ls /nonexistent/path -->
<!-- xmd:catch -->
Command failed as expected - directory does not exist.
<!-- xmd:endtry -->

### Conditional Command Execution
<!-- xmd:if config.env == "production" -->
Production status: <!-- xmd:exec echo "System is in production mode" -->
<!-- xmd:endif -->

## 5. Import and Module System

### Import JSON Data
<!-- xmd:import server_list from "config/servers.json" -->
<!-- xmd:import app_config from "config/app.json" -->

### Import Markdown Modules
<!-- xmd:include "modules/header.md" -->
<!-- xmd:include "modules/footer.md" -->

### Conditional Imports
<!-- xmd:if config.env == "production" -->
<!-- xmd:include "modules/prod-warnings.md" -->
<!-- xmd:endif -->

## 6. Template Processing

### Variable Interpolation in Text
The {{name}} system version {{version}} was created by {{author}} in {{year}}.

### Variable Interpolation in URLs
Documentation: [{{name}} Docs](https://docs.example.com/{{name|lower}}/{{version}})

### Variable Interpolation in Code Blocks
```bash
#!/bin/bash
echo "Welcome to {{name}} {{version}}"
export APP_ENV="{{config.env}}"
export DEBUG_MODE={{config.debug}}
```

### Variable Interpolation in HTML
```html
<h1>{{name}} Dashboard</h1>
<meta name="version" content="{{version}}">
<div class="environment-{{config.env}}">
  <p>Running in {{config.env}} mode</p>
</div>
```

## 7. Advanced Features

### Mathematical Expressions
<!-- xmd:set radius=5 -->
<!-- xmd:set area=pi * radius * radius -->
Circle with radius {{radius}} has area: {{area|round(2)}}

### String Operations
<!-- xmd:set message="Hello World" -->
- Original: {{message}}
- Uppercase: {{message|upper}}
- Lowercase: {{message|lower}}
- Length: {{message|length}}
- Reversed: {{message|reverse}}

### Array Operations
<!-- xmd:set numbers=[1, 2, 3, 4, 5] -->
- Original array: {{numbers}}
- Length: {{numbers|length}}
- First element: {{numbers[0]}}
- Last element: {{numbers[-1]}}
- Sum: {{numbers|sum}}
- Average: {{numbers|avg|round(2)}}

### Date and Time Operations
<!-- xmd:set current_time="2025-07-25T10:30:00Z" -->
- ISO time: {{current_time}}
- Formatted: {{current_time|date("%Y-%m-%d %H:%M")}}
- Year: {{current_time|date("%Y")}}
- Month: {{current_time|date("%B")}}

## 8. Error Handling and Edge Cases

### Try-Catch Blocks
<!-- xmd:try -->
<!-- xmd:set result=10/0 -->
Result: {{result}}
<!-- xmd:catch error -->
Caught division by zero error: {{error.message}}
<!-- xmd:endtry -->

### Undefined Variable Handling
<!-- xmd:try -->
Value: {{undefined_variable}}
<!-- xmd:catch -->
Undefined variable handled gracefully.
<!-- xmd:endtry -->

### Null and Empty Value Handling
<!-- xmd:set null_value=null -->
<!-- xmd:set empty_string="" -->
<!-- xmd:set empty_array=[] -->

<!-- xmd:if null_value == null -->
Null value detected and handled.
<!-- xmd:endif -->

<!-- xmd:if empty_string == "" -->
Empty string detected and handled.
<!-- xmd:endif -->

<!-- xmd:if empty_array|length == 0 -->
Empty array detected and handled.
<!-- xmd:endif -->

## 9. Security and Sandboxing

### Safe Command Execution
<!-- xmd:exec echo "This is a safe command" -->

### File System Access (Read-only)
<!-- xmd:exec ls -la . -->

### Network Access Test
<!-- xmd:try -->
<!-- xmd:exec ping -c 1 localhost -->
<!-- xmd:catch -->
Network access restricted or command failed.
<!-- xmd:endtry -->

## 10. Performance and Optimization

### Large Data Processing
<!-- xmd:set large_array=range(1, 1001) -->
Processing {{large_array|length}} items...

<!-- xmd:for i in large_array -->
<!-- xmd:if i % 100 == 0 -->
Processed {{i}} items
<!-- xmd:endif -->
<!-- xmd:endfor -->

### Caching Test
<!-- xmd:cache key="expensive_operation" ttl=3600 -->
<!-- xmd:exec sleep 1 && echo "Expensive operation completed" -->
<!-- xmd:endcache -->

## 11. Formatting and Output

### Tables with Dynamic Data
| Server | Environment | Status |
|--------|-------------|--------|
<!-- xmd:for server in servers -->
| {{server}} | {{config.env}} | <!-- xmd:exec echo "Online" --> |
<!-- xmd:endfor -->

### Lists with Dynamic Content
<!-- xmd:for tag in metadata.tags -->
- **{{tag|title}}**: Important tag for classification
<!-- xmd:endfor -->

### Code Generation
```python
# Auto-generated configuration
CONFIG = {
    "name": "{{name}}",
    "version": "{{version}}",
    "environment": "{{config.env}}",
    "debug": {{config.debug|lower}},
    "servers": {{servers|json}},
    "metadata": {{metadata|json}}
}

def get_server_count():
    return {{servers|length}}

def is_production():
    return CONFIG["environment"] == "production"
```

## 12. Multi-language Support

### Internationalization
<!-- xmd:set locale="en_US" -->
<!-- xmd:set messages={"en": {"hello": "Hello", "goodbye": "Goodbye"}, "es": {"hello": "Hola", "goodbye": "Adiós"}} -->

Greeting: {{messages[locale[:2]].hello}} {{name}}!

### Unicode Support
<!-- xmd:set unicode_text="Hello 世界! 🌍 Здравствуй мир!" -->
Unicode test: {{unicode_text}}

## 13. Advanced Templating

### Macros and Functions
<!-- xmd:macro server_status(name, env) -->
**{{name}}** ({{env}}): <!-- xmd:exec echo "Status OK" -->
<!-- xmd:endmacro -->

<!-- xmd:for server in servers -->
<!-- xmd:call server_status(server, config.env) -->
<!-- xmd:endfor -->

### Template Inheritance
<!-- xmd:extends "templates/base.md" -->
<!-- xmd:block content -->
This is the main content block.
<!-- xmd:endblock -->

## 14. Comments and Documentation

### XMD Comments (should not appear in output)
<!-- xmd:comment This is an XMD comment that should be stripped -->

### Regular HTML Comments (preserved based on config)
<!-- This is a regular HTML comment -->

### Inline Documentation
<!-- xmd:doc
This section demonstrates inline documentation
that can be used for explaining XMD directives
-->

## 15. Final Validation

### System Summary
Generated on: <!-- xmd:exec date "+%Y-%m-%d %H:%M:%S" -->
By: XMD {{version}}
For: {{author}}
Environment: {{config.env}}
Feature test status: ✅ Complete

### Variable Dump (Debug)
<!-- xmd:if config.debug -->
```json
<!-- xmd:dump_vars -->
```
<!-- xmd:endif -->

---

**End of Comprehensive XMD Test Document**

*This document has tested all major XMD features including variables, conditionals, loops, command execution, imports, templates, error handling, security, performance, formatting, internationalization, and advanced templating features.*