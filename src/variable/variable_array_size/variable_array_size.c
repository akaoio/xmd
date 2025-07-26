/**
 * @file variable_array_size.c
 * @brief Variable system implementation - array size getter
 * @author XMD Team
 *
 * Implementation of array size getter for the XMD variable system.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../../../include/variable_internal.h"
#include "../../../include/utils.h"

/**
 * @brief Get array size
 * @param array_var Array variable
 * @return Array size or 0 if not array/invalid
 */
size_t variable_array_size(const variable* array_var) {
    if (!array_var || array_var->type != VAR_ARRAY || !array_var->value.array_value) {
        return 0;
    }
    
    return array_var->value.array_value->count;
}
