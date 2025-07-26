/**
 * @file xmd_validate.c
 * @brief XMD validation function
 * @author XMD Team
 *
 * Implementation of XMD validation for the C API.
 */

#include "../../../../include/c_api_internal.h"

/**
 * @brief Validate markdown syntax
 * @param handle XMD context handle
 * @param input Input markdown string
 * @param input_length Input string length
 * @return Validation result (must be freed with xmd_result_free)
 */
xmd_result* xmd_validate(void* handle, const char* input, size_t input_length) {
    if (!handle || !input) {
        return NULL; // Return NULL for invalid parameters
    }
    
    xmd_context_internal* ctx = (xmd_context_internal*)handle;
    if (!ctx->initialized) {
        return create_result(-1, NULL, "XMD context not initialized");
    }
    
    // Record start time
    clock_t start_time = clock();
    
    // Basic validation - check for balanced directives
    // In a full implementation, this would parse and validate the entire syntax
    int directive_balance = 0;
    const char* pos = input;
    const char* end = input + input_length;
    
    while (pos < end) {
        if (strncmp(pos, "<!-- xmd:", 9) == 0) {
            // Found XMD directive start
            if (strstr(pos, "if") || strstr(pos, "for") || strstr(pos, "while") || strstr(pos, "try")) {
                directive_balance++;
            } else if (strstr(pos, "endif") || strstr(pos, "endfor") || strstr(pos, "endwhile") || strstr(pos, "endtry")) {
                directive_balance--;
            }
        }
        pos++;
    }
    
    // Calculate processing time
    clock_t end_time = clock();
    double processing_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000.0;
    
    xmd_result* result;
    if (directive_balance == 0) {
        result = create_result(0, "Validation successful", NULL);
    } else {
        result = create_result(1, NULL, "Unbalanced XMD directives");
    }
    
    if (result) {
        result->processing_time_ms = processing_time;
    }
    
    return result;
}
