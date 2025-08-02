/**
 * @file variable_new_string.c
 * @brief Create new string variable
 * 
 * This file contains ONLY the variable_new_string function.
 * One function per file - Genesis principle compliance.
 */

#include "../../../../include/variable.h"
#include "../../../utils/common/common_macros.h"
#include <stdlib.h>
#include <string.h>

/**
 * @brief Create new string variable
 * @param value String value
 * @return New variable or NULL on error
 */
xmd_variable* variable_new_string(const char* value) {
    XMD_VALIDATE_PTRS(NULL, value);
    
    xmd_variable* var = xmd_malloc(sizeof(xmd_variable));
    if (!var) {
        return NULL;
    }
    
    var->type = XMD_VAR_STRING;
    var->value.string_val = strdup(value);
    if (!var->value.string_val) {
        XMD_FREE_SAFE(var);
        return NULL;
    }
    
    var->name = NULL;
    var->ref_count = 1;
    
    return var;
}