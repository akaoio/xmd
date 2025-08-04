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
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"
/**
 * @brief Create result structure helper
 * @param error_code Error code
 * @param output Output string (will be copied)
 * @param error_message Error message (will be copied)
 * @return New result structure or NULL on error
 */
xmd_result* c_api_create_result(int error_code, const char* output, const char* error_message) {
    XMD_CREATE_VALIDATED(result, xmd_result, sizeof(xmd_result), NULL);
    
    result->error_code = error_code;
    result->processing_time_ms = 0.0;
    result->output = NULL;
    result->error_message = NULL;
    
    // Copy output string
    if (output) {
        result->output = xmd_strdup(output);
        if (!result->output) {
            XMD_FREE_SAFE(result);
            return NULL;
        }
    }
    
    // Copy error message
    if (error_message) {
        result->error_message = xmd_strdup(error_message);
        if (!result->error_message) {
            XMD_FREE_SAFE(result->output);
            XMD_FREE_SAFE(result);
            return NULL;
        }
    }
    
    return result;
}
