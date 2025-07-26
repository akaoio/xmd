/**
 * @file create_default_precision.c
 * @brief Default precision configuration creation function
 * @author XMD Team
 *
 * Implementation of default precision configuration creation for the XMD config system.
 */

#include "../../../include/config_internal.h"

/**
 * @brief Create default precision configuration
 * @return Default precision configuration
 */
xmd_precision_config create_default_precision(void) {
    xmd_precision_config precision = {
        .float_epsilon = 1e-10,
        .number_format = "%.6g",
        .int_min_value = -2147483648.0,
        .int_max_value = 2147483647.0
    };
    return precision;
}