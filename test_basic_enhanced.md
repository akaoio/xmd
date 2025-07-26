# Basic Enhanced XMD Test

## Test 1: Current XMD vs Expected Enhanced

### What current XMD outputs (wrong):
<!-- xmd:set role="admin" -->

<!-- xmd:if role == "admin" -->
**Admin Panel**
<!-- xmd:elif role == "editor" -->
**Editor Dashboard**
<!-- xmd:else -->
**Guest Access**
<!-- xmd:endif -->

### What we expect with Enhanced XMD:
Only "Admin Panel" should appear above (not all three options).

## Test 2: Simple Multiline Test

Try this with current XMD:
<!-- xmd:
set name="Alice"
set age=30
-->

Name: {{name}}, Age: {{age}}

Expected: Variables should be set and substituted.
Current XMD: Probably ignores multiline directives.

## Test 3: Import Test

Create a simple module first, then import it.

### Module (config.md):
```
<!-- xmd:set host="localhost" -->
<!-- xmd:set port=3000 -->
```

### Import usage:
<!-- xmd:import "config.md" -->

Server: {{host}}:{{port}}

Expected: Should show "Server: localhost:3000"
Current XMD: Probably shows "Server: :"