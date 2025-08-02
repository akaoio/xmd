#!/bin/bash

# Fix specific profiler files that have syntax errors

cd /data/data/com.termux/files/home/xmd

# List of files that need fixing based on build errors
files=(
    "src/performance/profiler/perf_profiler_start.c"
    "src/performance/profiler/perf_profiler_stop.c"
    "src/performance/profiler/perf_profiler_record_alloc.c"
)

for file in "${files[@]}"; do
    echo "Fixing $file"
    
    # Read the file content
    content=$(cat "$file")
    
    # Check if file has the problematic pattern (missing function comment)
    if ! echo "$content" | grep -q "@brief.*@param.*@return"; then
        # File is missing the function documentation, reconstruct it
        
        # Extract function name from filename
        func_name=$(basename "$file" .c)
        
        # Create proper file content
        cat > "$file" << 'EOF'
/**
 * @file FILENAME
 * @brief DESCRIPTION
 */

#include "../../../include/performance_internal.h"
#include "../../../include/platform.h"

/**
 * @brief FUNCTION_DESCRIPTION
 * @param profiler Performance profiler
 * @return 0 on success, -1 on error
 */
EOF
        
        # Replace placeholders
        sed -i "s/FILENAME/$(basename "$file")/g" "$file"
        
        # Add the actual function implementation based on file
        case "$file" in
            *perf_profiler_start.c)
                cat >> "$file" << 'EOF'
int perf_profiler_start(perf_profiler* profiler) {
    if (!profiler) return -1;
    xmd_get_time(&profiler->start_time);
    profiler->is_active = true;
    return 0;
}
EOF
                sed -i "s/DESCRIPTION/Start profiling session/g" "$file"
                sed -i "s/FUNCTION_DESCRIPTION/Start profiling session/g" "$file"
                ;;
                
            *perf_profiler_stop.c)
                cat >> "$file" << 'EOF'
int perf_profiler_stop(perf_profiler* profiler) {
    if (!profiler || !profiler->is_active) return -1;
    
    xmd_get_time(&profiler->end_time);
    profiler->is_active = false;
    
    // Calculate total time
    profiler->total_time_ns = (profiler->end_time.tv_sec - profiler->start_time.tv_sec) * 1000000000ULL +
                             (profiler->end_time.tv_nsec - profiler->start_time.tv_nsec);
    
    return 0;
}
EOF
                sed -i "s/DESCRIPTION/Stop profiling session/g" "$file"
                sed -i "s/FUNCTION_DESCRIPTION/Stop profiling session/g" "$file"
                ;;
                
            *perf_profiler_record_alloc.c)
                cat >> "$file" << 'EOF'
int perf_profiler_record_alloc(perf_profiler* profiler, size_t size) {
    if (!profiler) return -1;
    
    profiler->memory_allocated += size;
    profiler->allocation_count++;
    
    return 0;
}
EOF
                sed -i "s/DESCRIPTION/Record memory allocation/g" "$file"
                sed -i "s/FUNCTION_DESCRIPTION/Record memory allocation/g" "$file"
                sed -i "s/@param profiler Performance profiler/@param profiler Performance profiler\n * @param size Size of allocation/g" "$file"
                ;;
        esac
    fi
done

echo "Profiler files fixed!"