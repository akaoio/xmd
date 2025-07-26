/**
 * @file create_result.c
 * @brief XMD result creation function
 * @author XMD Team
 *
 * Implementation of result structure creation for the XMD C API.
 */

#include "../../../../include/c_api_internal.h"

/**
 * @brief Create XMD result structure
 * @param error_code Error code
 * @param output Output content
 * @param error_message Error message
 * @return New result structure or NULL on error
 */
xmd_result* create_result(int error_code, const char* output, const char* error_message) {
    xmd_result* result = calloc(1, sizeof(xmd_result));
    if (!result) {
        return NULL;
    }
    
    result->error_code = error_code;
    
    if (output) {
        result->output = strdup(output);
        result->output_length = strlen(output);
    } else {
        result->output = NULL;
        result->output_length = 0;
    }
    
    if (error_message) {
        result->error_message = strdup(error_message);
    } else {
        result->error_message = NULL;
    }
    
    result->processing_time_ms = 0.0;
    
    return result;
}