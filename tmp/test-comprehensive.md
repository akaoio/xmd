<!-- xmd:
set arr = ["debug", "test", "mock"]
set keywords1 = join arr ", "
set keywords2 = join arr "|"
set command = "echo \"grep pattern: \\\"" + keywords2 + "\\\"\""
set result = exec command
-->

Array: {{arr}}
Keywords1: {{keywords1}}
Keywords2: {{keywords2}}
Command: {{command}}
Result: {{result}}