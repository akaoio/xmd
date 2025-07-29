/**
 * @file xmd_result_free.c
 * @brief XMD result memory cleanup
 * @author XMD Team
 */

#include "../../../../include/c_api_internal.h"

/**
 * @brief Free XMD result structure
 * @param result Result to free
 */
void c_api_xmd_result_free(xmd_result* result) {
    if (!result) {
        return;
    }
    
    free(result->output);
    free(result->error_message);
    free(result);
}

/**
 * @brief Free XMD result structure (public API)
 * @param result Result to free
 */
void xmd_result_free(xmd_result* result) {
    c_api_xmd_result_free(result);
}