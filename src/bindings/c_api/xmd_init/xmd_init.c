/**
 * @file xmd_init.c
 * @brief XMD initialization function
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include "../../../../include/c_api_internal.h"

/**
 * @brief Initialize XMD processor (internal C API)
 * @param config_path Path to configuration file (optional)
 * @return XMD context handle or NULL on error
 */
void* c_api_xmd_init(const char* config_path) {
    xmd_context_internal* ctx = calloc(1, sizeof(xmd_context_internal));
    if (!ctx) {
        return NULL;
    }
    
    // Initialize configuration
    ctx->config = config_create();
    if (!ctx->config) {
        free(ctx);
        return NULL;
    }
    
    // Load configuration file if provided
    if (config_path) {
        if (config_load_file(ctx->config, config_path) != 0) {
            config_destroy(ctx->config);
            free(ctx);
            return NULL;
        }
    }
    
    // Load environment configuration
    config_load_env(ctx->config);
    
    // Initialize global variable store
    ctx->global_variables = store_create();
    if (!ctx->global_variables) {
        config_destroy(ctx->config);
        free(ctx);
        return NULL;
    }
    
    ctx->initialized = true;
    return ctx;
}

/**
 * @brief Initialize XMD system (main API)
 * @return Error code
 */
xmd_error_code xmd_init(void) {
    // Global initialization - in full implementation would set up
    // global state, register default functions, etc.
    return XMD_SUCCESS;
}
