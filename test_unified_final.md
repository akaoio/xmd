# XMD Unified Parser Test

## Test 1: Basic Variables
<!-- xmd:set name="World" -->
Hello {{name}}!

## Test 2: If/Elif/Else
<!-- xmd:set user_level="admin" -->

<!-- xmd:if user_level == "admin" -->
### Admin Access Granted
You have full permissions.
<!-- xmd:elif user_level == "user" -->
### User Access
Limited permissions.
<!-- xmd:else -->
### Guest Access
Read-only mode.
<!-- xmd:endif -->

## Test 3: Multiline Directives
<!-- xmd:
set project="XMD Parser"
set version="1.0"
set status="unified"
-->

**Project:** {{project}}  
**Version:** {{version}}  
**Status:** {{status}}

## Test 4: Command Execution
<!-- xmd:exec echo "Hello from unified parser!" -->