
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
#include "variable.h"
#include "variable_internal.h"
#include "utils.h"
#include "utils/common/common_macros.h"

/**
 * @brief Create a new string variable
 * @return New string variable or NULL on failure
 */
variable* variable_create_string(const char* value) {
    variable* var;
    XMD_MALLOC_CHECK(var, sizeof(variable));
    
    var->type = VAR_STRING;
    var->ref_count = 1;
    if (value == NULL) {
        XMD_MALLOC_CHECK(var->value.string_value, 1);
        var->value.string_value[0] = '\0';
    } else {
        XMD_STRDUP_CHECK(var->value.string_value, value);
    }
    return var;
}
