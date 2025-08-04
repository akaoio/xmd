/**
 * @file config_set_global.c
 * @brief Implementation of config_set_global function
 * 
 * This file contains ONLY the config_set_global function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/config_consolidated.c
 */

#include "../../../../include/config_internal.h"
#include "../../../../utils/common/common_macros.h"

// Global configuration instance declaration (defined in config_consolidated.c)
extern xmd_internal_config* g_config;
/**
 * @brief Set global configuration instance
 * @param config Configuration to set as global (can be NULL to clear)
  * /
 */
void config_set_global(xmd_config* config) {
    // Allow NULL to clear global config, so no validation needed
    g_config = (xmd_internal_config*)config;
}
