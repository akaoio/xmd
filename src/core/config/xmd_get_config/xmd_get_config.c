/**
 * @file xmd_get_config.c
 * @brief XMD configuration getter function - Genesis compliant
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../../include/xmd.h"
#include "../../../utils/common/common_macros.h"

/**
 * @brief Get XMD configuration parameter
 * @param key Configuration key
 * @return Configuration value string, or NULL if not found
 */
const char* xmd_get_config(const char* key) {
    XMD_VALIDATE_PTRS(NULL, key);
    
    // Get configuration parameter
    // This would typically query a global config structure
    // For basic functionality, return default values for known keys
    
    if (strcmp(key, "version") == 0) {
        return "0.0.2";
    } else if (strcmp(key, "syntax") == 0) {
        return "XMD";
    } else if (strcmp(key, "debug") == 0) {
        return "false";
    }
    
    return NULL; // Key not found
}
