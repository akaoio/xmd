/**
 * @file variable_ref.c
 * @brief Variable system implementation - reference counting
 * @author XMD Team
 *
 * Implementation of variable reference increment for the XMD variable system.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../../../include/variable_internal.h"
#include "../../../include/utils.h"

/**
 * @brief Increment reference count
 * @param var Variable to reference (can be NULL)
 * @return Same variable pointer for chaining
 */
variable* variable_ref(variable* var) {
    if (var == NULL) {
        return NULL;
    }
    
    var->ref_count++;
    return var;
}
