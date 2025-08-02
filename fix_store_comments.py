#!/usr/bin/env python3
import os
import re

store_files = [
    "src/store/create/store_create.c",
    "src/store/memory/store_destroy.c",
    "src/store/operations/store_set.c",
    "src/store/operations/store_get.c",
    "src/store/operations/store_has.c",
    "src/store/operations/store_remove.c",
    "src/store/operations/store_size.c",
    "src/store/operations/store_clear.c",
    "src/store/operations/store_keys.c"
]

for filepath in store_files:
    if not os.path.exists(filepath):
        continue
        
    with open(filepath, 'r') as f:
        content = f.read()
    
    # Replace the pattern of include followed by " */" and function declaration
    content = re.sub(
        r'(#include [^\n]+)\n \*/\n([a-zA-Z])',
        r'\1\n\n/**\n * @brief Function implementation\n */\n\2',
        content
    )
    
    with open(filepath, 'w') as f:
        f.write(content)
    
    print(f"Fixed {filepath}")