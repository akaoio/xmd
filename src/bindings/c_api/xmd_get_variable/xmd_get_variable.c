/**
 * @file xmd_get_variable.c
 * @brief XMD variable getter
 * @author XMD Team
 *
 * Implementation of XMD variable getting for the C API.
 */

#include "../../../../include/c_api_internal.h"

/**
 * @brief Get variable from processor context (internal C API)
 * @param processor Processor instance
 * @param key Variable name
 * @return Variable value or NULL if not found
 */
char* c_api_xmd_get_variable(void* processor, const char* key) {
    if (!processor || !key) {
        return NULL;
    }
    
    // Cast to internal context type
    xmd_context_internal* ctx = (xmd_context_internal*)processor;
    if (!ctx->initialized) {
        return NULL;
    }
    
    // In a full implementation, would lookup from variable context
    // For now, return NULL (not found)
    return NULL;
}

/**
 * @brief Get variable from processor context (main API)
 * @param processor Processor instance
 * @param key Variable name
 * @return Variable value or NULL if not found
 */
char* xmd_get_variable(xmd_processor* processor, const char* key) {
    return c_api_xmd_get_variable(processor, key);
}
