/**
 * @file xmd_config_create_default.c
 * @brief Create default XMD configuration
 * 
 * This file contains ONLY the xmd_config_create_default function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/bindings_consolidated.c
 */

#include "../../../../../include/xmd.h"
#include "../../../../../include/config_internal.h"

// Forward declaration for config_create
extern xmd_config* config_create(void);

/**
 * @brief Create default XMD configuration
 * @return Default configuration or NULL on error
 */
xmd_config* xmd_config_create_default(void) { 
    return config_create();
}
