/**
 * @file xmd_set_variable.c
 * @brief Set XMD processor variable
 * 
 * This file contains ONLY the xmd_set_variable function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/bindings_consolidated.c
 */

#include "../../../../../include/xmd.h"
#include "../../../../../include/store.h"
#include "../../../../../include/variable.h"
/**
 * @brief Set XMD processor variable
 * @param processor XMD processor
 * @param key Variable name
 * @param value Variable value
 * @return XMD_SUCCESS on success, error code on failure
  * /
 */
xmd_error_code xmd_set_variable(xmd_processor* processor, const char* key, const char* value) {
    if (!processor || !key || !value) return XMD_ERROR_INVALID_ARGUMENT;
    store* variables = (store*)processor;
    variable* var = variable_create_string(value);
    if (!var) return XMD_ERROR_OUT_OF_MEMORY;
    store_set(variables, key, var);
    return XMD_SUCCESS;
}
