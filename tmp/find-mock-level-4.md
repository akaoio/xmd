IMPLEMENT:

<!-- xmd:
set arr = ["debug","for now","in real","in a real","mock]
set keywords = arr[0]
for k in arr
    keywords += ", " + k
set files = exec find src -type f -exec grep -liE  {} +
-->

SHOW OR NOT SHOW: {{keywords}}

<!-- xmd: exec find src -type f -exec grep -liE "debug|for now|in real|in a real|mock" {} + -->