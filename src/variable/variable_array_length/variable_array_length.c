/**
 * @file variable_array_length.c
 * @brief Variable system implementation - array length getter
 * @author XMD Team
 *
 * Implementation of array length getter for the XMD variable system.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../../../include/variable_internal.h"
#include "../../../include/utils.h"

/**
 * @brief Get array length
 * @param var Array variable
 * @return Array length or 0 if not array
 */
size_t variable_array_length(const variable* var) {
    return variable_array_size(var);
}
