/**
 * @file variable_create_number.c
 * @brief Variable system implementation - number creation
 * @author XMD Team
 *
 * Implementation of number variable creation for the XMD variable system.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../../../include/variable_internal.h"
#include "../../../include/utils.h"

/**
 * @brief Create a new number variable
 * @param value Numeric value
 * @return New number variable or NULL on failure
 */
variable* variable_create_number(double value) {
    variable* var = malloc(sizeof(variable));
    if (var == NULL) {
        return NULL;
    }
    
    var->type = VAR_NUMBER;
    var->value.number_value = value;
    var->ref_count = 1;
    
    return var;
}
