/**
 * @file xmd_cleanup.c
 * @brief XMD cleanup function
 * @author XMD Team
 *
 * Implementation of XMD context cleanup for the C API.
 */

#include "../../../../include/c_api_internal.h"

/**
 * @brief Cleanup XMD processor
 * @param handle XMD context handle
 */
void xmd_cleanup(void* handle) {
    if (!handle) {
        return;
    }
    
    xmd_context_internal* ctx = (xmd_context_internal*)handle;
    
    if (ctx->config) {
        config_destroy(ctx->config);
    }
    if (ctx->global_variables) {
        store_destroy(ctx->global_variables);
    }
    free(ctx);
}