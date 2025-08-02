/**
 * @file xmd_process_string.c
 * @brief Core XMD string processing function
 * 
 * This file contains ONLY the xmd_process_string function.
 * One function per file - Genesis principle compliance.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../../../../include/xmd.h"
#include "../../../../../include/c_api_internal.h"

// Forward declaration for AST-based XMD processor
extern char* ast_process_xmd_content(const char* input, store* variables);

/**
 * @brief Process markdown string
 * @param processor XMD processor instance
 * @param input Input markdown string
 * @param input_length Input string length
 * @return Processing result (must be freed with xmd_result_free)
 */
xmd_result* xmd_process_string(xmd_processor* processor, 
                               const char* input, 
                               size_t input_length) {
    if (!processor || !input) {
        return NULL;
    }
    
    if (!processor->initialized) {
        return c_api_create_result(-1, NULL, "Processor not initialized");
    }
    
    // Record start time
    clock_t start_time = clock();
    
    // Use processor->variables to ensure persistence
    char* output = ast_process_xmd_content(input, processor->variables);
    
    // Calculate processing time
    clock_t end_time = clock();
    double processing_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000.0;
    
    xmd_result* result = c_api_create_result(0, output, NULL);
    if (result) {
        result->processing_time_ms = processing_time;
    }
    
    XMD_FREE_SAFE(output);
    return result;
}