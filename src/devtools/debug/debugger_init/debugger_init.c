/**
 * @file debugger_init.c
 * @brief Initialize debugger functionality
 * 
 * This file contains ONLY the debugger_init function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/devtools_consolidated.c
 */

#include <stdio.h>
#include "../../../../include/devtools.h"
/**
 * @brief Initialize debugger
 * @param trace_file File to write trace output (NULL for stderr)
 * @return 0 on success, -1 on error
  * /
 */
int debugger_init(const char* trace_file) {
    printf("XMD Debugger initialized\n");
    if (trace_file) {
        printf("Trace output: %s\n", trace_file);
    }
    return 0;
}
