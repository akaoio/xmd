/**
 * @file c_api_xmd_init.c
 * @brief Initialize XMD C API context
 * 
 * This file contains ONLY the c_api_xmd_init function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/bindings_consolidated.c
 */

#include <stdlib.h>
#include "../../../../../include/xmd.h"
#include "../../../../../include/c_api_internal.h"
#include "../../../../../include/config_internal.h"
#include "../../../../../include/store.h"
#include "../../../../../include/utils.h"
#include "utils/common/common_macros.h"
/**
 * @brief Initialize XMD C API context
 * @param config_path Path to configuration file (NULL for defaults)
 * @return Context handle or NULL on error
  * /
 */
void* c_api_xmd_init(const char* config_path) {
    XMD_CREATE_VALIDATED(ctx, xmd_context_internal, sizeof(xmd_context_internal), NULL);
    
    ctx->config = config_create();
    if (!ctx->config) { 
        XMD_FREE_SAFE(ctx); 
        return NULL; 
    }
    
    if (config_path && config_load_file(ctx->config, config_path) != 0) {
        config_destroy(ctx->config); 
        XMD_FREE_SAFE(ctx); 
        return NULL;
    }
    
    config_load_env(ctx->config);
    ctx->global_variables = store_create();
    if (!ctx->global_variables) { 
        config_destroy(ctx->config); 
        XMD_FREE_SAFE(ctx); 
        return NULL; 
    }
    
    ctx->initialized = true;
    return ctx;
}
