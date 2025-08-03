
/**
 * @file variable_create_string.c
 * @brief Implementation of variable_create_string function
 * 
 * This file contains ONLY the variable_create_string function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/variable.c
 */

#include <stdlib.h>
#include <string.h>
#include "../../../../include/variable.h"
#include "../../../../include/variable_internal.h"
#include "../../../../include/utils.h"
#include "../../../utils/common/common_macros.h"

/**
 * @brief Create a new string variable
 * @return New string variable or NULL on failure
 */
variable* variable_create_string(const char* value) {
    XMD_CREATE_VALIDATED(var, variable, sizeof(variable), NULL);
    
    var->type = VAR_STRING;
    var->ref_count = 1;
    if (value == NULL) {
        XMD_MALLOC_DYNAMIC(var->value.string_value, 1, NULL);
        var->value.string_value[0] = '\0';
    } else {
        var->value.string_value = xmd_strdup(value);
        if (!var->value.string_value) {
            XMD_FREE_SAFE(var);
            return NULL;
        }
    }
    return var;
}
