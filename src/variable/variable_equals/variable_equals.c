/**
 * @file variable_equals.c
 * @brief Variable system implementation - equality comparison
 * @author XMD Team
 *
 * Implementation of variable equality comparison for the XMD variable system.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "../../../include/variable_internal.h"
#include "../../../include/utils.h"

/**
 * @brief Check if two variables are equal
 * @param a First variable
 * @param b Second variable
 * @return true if variables are equal, false otherwise
 */
bool variable_equals(const variable* a, const variable* b) {
    return xmd_variable_equals(a, b);
}
