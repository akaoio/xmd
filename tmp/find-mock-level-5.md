IMPLEMENT:

<!-- xmd:
set arr = ["debug","for now","in real","in a real","mock"]
set keywords1 = join arr ", "
set keywords2 = join arr "|"
set pattern = keywords2
set files = exec "find src -type f -exec grep -liE \"{{pattern}}\" {} +"
-->

SHOW OR NOT SHOW: {{keywords1}}
keywords2: {{keywords2}}

FILES:
{{files}}