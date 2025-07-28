<!-- xmd:
set simple_cmd = "find src -name \"*.c\" | head -2"
set grep_cmd = "grep -l debug src/main/main.c || echo 'not found'"
set result1 = exec simple_cmd
set result2 = exec grep_cmd
-->

Simple find: {{result1}}
Grep result: {{result2}}