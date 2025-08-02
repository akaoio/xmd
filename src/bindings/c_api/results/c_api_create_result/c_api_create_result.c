/**
 * @file c_api_create_result.c
 * @brief Create result structure helper
 * 
 * This file contains ONLY the c_api_create_result function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/bindings_consolidated.c (with syntax fixes)
 */

#include <string.h>
#include <stdlib.h>
#include "../../../../../include/xmd.h"
#include "../../../../../include/utils.h"
/**
 * @brief Create result structure helper
 * @param error_code Error code
 * @param output Output string (will be copied)
 * @param error_message Error message (will be copied)
 * @return New result structure or NULL on error
  * /
 */
xmd_result* c_api_create_result(int error_code, const char* output, const char* error_message) {
    xmd_result* result = xmd_malloc(sizeof(xmd_result));
    if (!result) {
        return NULL;
    }
    
    result->error_code = error_code;
    result->processing_time_ms = 0.0;
    
    // Copy output string
    if (output) {
        result->output = xmd_malloc(strlen(output) + 1);
        if (result->output) {
            strcpy(result->output, output);
        } else {
            free(result);
            return NULL;
        }
    } else {
        result->output = NULL;
    }
    
    // Copy error message
    if (error_message) {
        result->error_message = xmd_malloc(strlen(error_message) + 1);
        if (result->error_message) {
            strcpy(result->error_message, error_message);
        } else {
            free(result->output);
            free(result);
            return NULL;
        }
    } else {
        result->error_message = NULL;
    }
    
    return result;
}
