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
    
    // Clean up temporary result structure and use the proper API
    free(result);
    return xmd_process_string_api(handle, input, input_length);
}