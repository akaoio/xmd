#define _GNU_SOURCE  // For strdup - must be before includes

/**
 * @file xmd_set_config.c
 * @brief XMD configuration setter
 * @author XMD Team
 *
 * Implementation of XMD configuration setting for the C API.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../include/c_api_internal.h"

/**
 * @brief Set configuration option
 * @param handle XMD context handle
 * @param key Configuration key
 * @param value Configuration value
 * @return 0 on success, -1 on error
 */
int c_api_xmd_set_config(void* handle, const char* key, const char* value) {
    if (!handle || !key || !value) {
        return -1;
    }
    
    xmd_context_internal* ctx = (xmd_context_internal*)handle;
    if (!ctx->initialized || !ctx->config) {
        return -1;
    }
    
    config_value* config_val = malloc(sizeof(config_value));
    if (!config_val) {
        return -1;
    }
    
    config_val->type = CONFIG_STRING;
    config_val->data.string_val = strdup(value);
    
    return config_set(ctx->config, key, config_val);
}
