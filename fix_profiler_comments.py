#!/usr/bin/env python3
import os
import re

files_to_fix = [
    "src/performance/profiler/perf_profiler_record_alloc.c",
    "src/performance/profiler/perf_profiler_create.c", 
    "src/performance/profiler/perf_profiler_start.c",
    "src/performance/profiler/perf_profiler_stop.c",
    "src/performance/profiler/perf_profiler_record_dealloc.c",
    "src/performance/profiler/perf_profiler_generate_report.c",
    "src/performance/profiler/perf_profiler_destroy.c",
    "src/performance/profiler/perf_profiler_record_cache_hit.c",
    "src/performance/profiler/perf_profiler_record_cache_miss.c",
    "src/performance/profiler/perf_profiler_get_metrics.c"
]

for filepath in files_to_fix:
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