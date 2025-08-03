/**
 * @file xmd_get_variable.c
 * @brief Get XMD processor variable
 * 
 * This file contains ONLY the xmd_get_variable function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/bindings_consolidated.c
 */

#include "../../../../../include/xmd.h"
#include "../../../../../include/store.h"
#include "../../../../../include/variable.h"
#include "../../../../utils/common/common_macros.h"
/**
 * @brief Get XMD processor variable
 * @param processor XMD processor
 * @param key Variable name
 * @return Variable value string or NULL if not found
  * /
 */
char* xmd_get_variable(xmd_processor* processor, const char* key) {
    XMD_VALIDATE_PTRS(NULL, processor, key);
    store* variables = (store*)processor;
    variable* var = store_get(variables, key);
    return var ? variable_to_string(var) : NULL;
}
