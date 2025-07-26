/**
 * @file xmd_get_config.c
 * @brief XMD configuration getter
 * @author XMD Team
 *
 * Implementation of XMD configuration getting for the C API.
 */

#include "../../../../include/c_api_internal.h"

/**
 * @brief Get configuration option
 * @param handle XMD context handle
 * @param key Configuration key
 * @return Configuration value or NULL if not found (must be freed)
 */
char* xmd_get_config(void* handle, const char* key) {
    if (!handle || !key) {
        return NULL;
    }
    
    xmd_context_internal* ctx = (xmd_context_internal*)handle;
    if (!ctx->initialized || !ctx->config) {
        return NULL;
    }
    
    config_value* value = config_get(ctx->config, key);
    if (value && value->type == CONFIG_STRING && value->data.string_val) {
        return strdup(value->data.string_val);
    }
    
    return NULL;
}
