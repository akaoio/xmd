/**
 * @file xmd_process_string.c
 * @brief Main XMD processor interface implementation
 * @author XMD Team
 * @date 2025-07-26
 */

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>

#include "../../../include/xmd_processor_internal.h"
#include "../../../include/ast_evaluator.h"

/**
 * @brief Main XMD processor interface
 * @param processor XMD processor instance (currently unused)
 * @param content Input content to process
 * @param length Length of input content (currently unused - uses strlen)
 * @return Processing result structure (caller must free with xmd_result_free)
 */
xmd_result* xmd_process_string(xmd_processor* processor, const char* content, size_t length) {
    (void)length; // Unused parameter - using strlen instead
    if (!processor || !content) {
        xmd_result* result = malloc(sizeof(xmd_result));
        result->error_code = XMD_ERROR_INVALID_ARGUMENT;
        result->error_message = strdup("Invalid arguments");
        result->output = NULL;
        result->output_length = 0;
        result->processing_time_ms = 0;
        result->memory_used_bytes = 0;
        return result;
    }
    
    // Treat processor as store for now
    store* variables = (store*)processor;
    
    // Process with AST-based parser
    char* processed_output = ast_process_xmd_content(content, variables);
    
    // Create result
    xmd_result* result = malloc(sizeof(xmd_result));
    result->error_code = XMD_SUCCESS;
    result->error_message = NULL;
    result->output = processed_output;
    result->output_length = processed_output ? strlen(processed_output) : 0;
    result->processing_time_ms = 0;
    result->memory_used_bytes = result->output_length + sizeof(xmd_result);
    
    return result;
}
