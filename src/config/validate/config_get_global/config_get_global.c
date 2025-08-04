/**
 * @file config_get_global.c
 * @brief Implementation of config_get_global function
 * 
 * This file contains ONLY the config_get_global function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/config_consolidated.c
 */

#include "../../../../include/config_internal.h"

// Global configuration instance declaration (defined in config_consolidated.c)
extern xmd_internal_config* g_config;
/**
 * @brief Get global configuration instance
 * @return Global configuration or NULL if not initialized
  * /
 */
xmd_internal_config* config_get_global(void) {
    return g_config;
}
