#!/bin/bash

# Fix files with missing closing braces

echo "Fixing files with missing braces..."

# Function to check if a file has unmatched braces
check_braces() {
    local file="$1"
    local open_count=$(grep -c '{' "$file")
    local close_count=$(grep -c '}' "$file")
    
    if [ "$open_count" -ne "$close_count" ]; then
        echo "Unmatched braces in $file: { = $open_count, } = $close_count"
        return 1
    fi
    return 0
}

# List of files reported with brace errors
files=(
    "src/variable/create/variable_create_string.c"
    "src/variable/create/variable_create_object.c"
    "src/variable/create/variable_new_array.c"
)

for file in "${files[@]}"; do
    if [ -f "$file" ]; then
        if ! check_braces "$file"; then
            # Check for common pattern: missing return NULL after free
            if grep -q "free(var);" "$file" && ! grep -A 1 "free(var);" "$file" | grep -q "return NULL"; then
                echo "Fixing missing return after free in $file"
                sed -i '/free(var);/a\        return NULL;\n    }' "$file"
                # Remove extra closing brace at end if exists
                sed -i '$ { /^}$/d; }' "$file"
            fi
        fi
    fi
done

# Fix perf_profiler_stop.c specifically
if [ -f "src/performance/profiler/perf_profiler_stop.c" ]; then
    echo "Fixing perf_profiler_stop.c"
    cat > "src/performance/profiler/perf_profiler_stop.c" << 'EOF'
/**
 * @file perf_profiler_stop.c
 * @brief Stop profiling session
 */

#include "../../../include/performance_internal.h"
#include "../../../include/platform.h"

/**
 * @brief Stop profiling session
 * @param profiler Performance profiler
 * @return 0 on success, -1 on error
 */
int perf_profiler_stop(perf_profiler* profiler) {
    if (!profiler || !profiler->is_active) return -1;
    
    xmd_get_time(&profiler->end_time);
    profiler->is_active = false;
    
    return 0;
}
EOF
fi

echo "Brace fixes complete!"