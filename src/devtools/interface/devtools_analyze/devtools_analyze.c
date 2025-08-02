/**
 * @file devtools_analyze.c
 * @brief Run combined debugging and linting
 * 
 * This file contains ONLY the devtools_analyze function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/devtools_consolidated.c
 */

#include <stdio.h>
#include "../../../../include/devtools.h"
/**
 * @brief Run combined debugging and linting
 * @param input_file Input XMD file
 * @param trace_output Trace output file (NULL to skip)
 * @param lint_content Content to lint (NULL to skip)
 * @return 0 on success, -1 on error
  * /
 */
int devtools_analyze(const char* input_file, const char* trace_output, const char* lint_content) {
    printf("XMD Development Tools Analysis\n");
    printf("==============================\n\n");
    
    int result = 0;
    
    // Initialize debugging if trace requested
    if (trace_output) {
        if (debugger_init(trace_output) != 0) {
            fprintf(stderr, "Failed to initialize debugger\n");
            result = -1;
        } else {
            debugger_log(__FILE__, __LINE__, "Analysis started");
            
            if (input_file) {
                debugger_trace(input_file, NULL);
            }
        }
    }
    
    // Run linting if content provided
    if (lint_content) {
        if (linter_init(NULL) != 0) {
            fprintf(stderr, "Failed to initialize linter\n");
            result = -1;
        } else {
            int issues = linter_check(lint_content);
            linter_report(issues, input_file);
            
            if (issues > 0) {
                result = 1; // Non-zero for issues found
            }
        }
    }
    
    // Cleanup
    if (trace_output) {
        debugger_log(__FILE__, __LINE__, "Analysis completed");
        debugger_cleanup();
    }
    
    return result;
}
