/**
 * @file create_default_precision.c
 * @brief Create default precision settings
 * 
 * This file contains ONLY the create_default_precision function.
 * One function per file - Genesis principle compliance.
 * Extracted from: backup/backup_20250801_184028/src/config_consolidated.c
 */

#include "../../../../include/config_internal.h"

/**
 * @brief Create default precision settings
 * @return Default precision configuration
 */
xmd_precision_config create_default_precision(void) {
    xmd_precision_config precision;
    
    precision.float_epsilon = 1e-10;   // Floating point comparison epsilon
    precision.number_format = "%.6g";  // Number format string
    precision.int_min_value = -2147483648.0; // Minimum integer value
    precision.int_max_value = 2147483647.0;  // Maximum integer value
    
    return precision;
}
