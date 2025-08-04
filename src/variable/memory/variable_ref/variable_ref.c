
/**
 * @file variable_ref.c
 * @brief Implementation of variable_ref function
 * 
 * This file contains ONLY the variable_ref function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/variable.c
 */

#include "variable.h"
#include "variable_internal.h"
#include "../../../../utils/common/common_macros.h"

/**
 * @brief Increment reference count
 * @return Same variable pointer for chaining
 */
variable* variable_ref(variable* var) {
    if (!var) return NULL;
    
    var->ref_count++;
    return var;
}
