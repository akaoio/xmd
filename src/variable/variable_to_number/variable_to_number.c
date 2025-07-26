/**
 * @file variable_to_number.c
 * @brief Variable system implementation - number conversion
 * @author XMD Team
 *
 * Implementation of variable to number conversion for the XMD variable system.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../../../include/variable_internal.h"
#include "../../../include/utils.h"

/**
 * @brief Convert variable to number
 * @param var Variable to convert
 * @return Numeric representation
 */
double variable_to_number(const variable* var) {
    return xmd_variable_to_number(var);
}
