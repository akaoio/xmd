#!/bin/bash

# Get all C files that use strdup but don't have _GNU_SOURCE
FILES=$(grep -r "strdup" src/ --include="*.c" -l | xargs grep -L "_GNU_SOURCE")

for file in $FILES; do
    echo "Fixing $file"
    # Create temp file with _GNU_SOURCE added after the first comment block
    awk '
    BEGIN { added_define = 0 }
    /^\*\// && !added_define {
        print $0
        print ""
        print "#define _GNU_SOURCE"
        added_define = 1
        next
    }
    /^#include/ && !added_define {
        print "#define _GNU_SOURCE"
        print $0
        added_define = 1
        next
    }
    { print $0 }
    ' "$file" > "$file.tmp" && mv "$file.tmp" "$file"
done
