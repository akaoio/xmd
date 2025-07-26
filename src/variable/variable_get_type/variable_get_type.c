/**
 * @file variable_get_type.c
 * @brief Variable system implementation - type getter
 * @author XMD Team
 *
 * Implementation of variable type getter for the XMD variable system.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../../../include/variable_internal.h"
#include "../../../include/utils.h"

/**
 * @brief Get variable type
 * @param var Variable to check
 * @return Variable type or VAR_NULL if var is NULL
 */
variable_type variable_get_type(const variable* var) {
    return var ? var->type : VAR_NULL;
}
