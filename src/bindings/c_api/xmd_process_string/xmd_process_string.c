/**
 * @file xmd_process_string.c
 * @brief Process string through XMD
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../../../../include/cli.h"
#include "../../../../include/store.h"
#include "../../../../include/c_api_internal.h"

// Forward declaration of XMD processor function
char* process_xmd_content_enhanced(const char* input, store* variables);

/**
 * @brief Process string through XMD
 * @param handle XMD handle
 * @param input Input string
 * @param input_length Length of input string
 * @return XMD result or NULL on error
 */
xmd_result* xmd_process_string(void* handle, const char* input, size_t input_length) {
    if (!handle || !input || input_length == 0) {
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
    result->output_length = 0;
    result->processing_time_ms = 0.0;
    
    // Start timing
    clock_t start_time = clock();
    
    // Create a store for variables
    store* variables = store_create();
    if (!variables) {
        free(result);
        return NULL;
    }
    
    // Convert input to null-terminated string for processing
    char* input_str = malloc(input_length + 1);
    if (!input_str) {
        store_destroy(variables);
        free(result);
        return NULL;
    }
    memcpy(input_str, input, input_length);
    input_str[input_length] = '\0';
    
    // Use the proper API that includes preprocessing
    free(input_str);
    store_destroy(variables);
    xmd_result_free(result);
    return xmd_process_string_api(handle, input, input_length);
    
    // Calculate processing time
    clock_t end_time = clock();
    result->processing_time_ms = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000.0;
    
    return result;
}