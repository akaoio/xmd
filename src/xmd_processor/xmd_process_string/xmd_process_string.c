/**
 * @file xmd_process_string.c
 * @brief Main API string processor implementation
 * @author XMD Team
 */

#define _GNU_SOURCE  // For strdup - must be before includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/xmd.h"
#include "../../../include/cli.h"
#include "../../../include/store.h"

// Forward declaration for AST processor
char* ast_process_xmd_content(const char* input, store* variables);

/**
 * @brief Process string through XMD main API
 */
xmd_result* xmd_process_string(xmd_processor* processor, 
                               const char* input, 
                               size_t input_length) {
    if (!processor || !input || input_length == 0) {
        return NULL;
    }
    
    // Create result structure
    xmd_result* result = malloc(sizeof(xmd_result));
    if (!result) {
        return NULL;
    }
    
    // Initialize result
    result->error_code = 0;
    result->output = NULL;
    result->error_message = NULL;
    
    // Process content using AST processor
    // Cast processor back to store* as that's how it's implemented
    store* variables = (store*)processor;
    char* output = ast_process_xmd_content(input, variables);
    if (output) {
        result->output = output;
        result->error_code = 0;
    } else {
        result->error_code = -1;
        result->error_message = strdup("Processing failed");
    }
    
    return result;
}