/**
 * @file xmd_set_variable.c
 * @brief XMD variable setter
 * @author XMD Team
 *
 * Implementation of XMD variable setting for the C API.
 */

#include "../../../../include/c_api_internal.h"

/**
 * @brief Set variable in processor context
 * @param processor Processor instance (actually xmd_context_internal*)
 * @param key Variable name
 * @param value Variable value
 * @return 0 on success, -1 on error
 */
int xmd_set_variable(void* processor, const char* key, const char* value) {
    if (!processor || !key || !value) {
        return -1;
    }
    
    xmd_context_internal* ctx = (xmd_context_internal*)processor;
    if (!ctx->initialized || !ctx->global_variables) {
        return -1;
    }
    
    // Create a string variable and store it
    variable* var = variable_create_string(value);
    if (!var) {
        return -1;
    }
    
    if (!store_set(ctx->global_variables, key, var)) {
        variable_unref(var);
        return -1;
    }
    
    return 0;
}
