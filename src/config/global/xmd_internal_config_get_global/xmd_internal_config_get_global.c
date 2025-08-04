/**
 * @file xmd_internal_config_get_global.c
 * @brief Get global internal configuration instance
 * 
 * This file contains ONLY the xmd_internal_config_get_global function.
 * One function per file - Genesis principle compliance.
 */

#include "../../../../include/config.h"
#include "../../../../include/config_internal.h"
#include "../../../../include/platform.h"
#include "utils/common/common_macros.h"

// Global configuration instance with thread safety
static xmd_internal_config* global_config = NULL;
static xmd_mutex_t config_mutex = {0};
static bool mutex_initialized = false;

/**
 * @brief Get global internal configuration instance
 * @return Global configuration instance or NULL if not initialized
 */
xmd_internal_config* xmd_internal_config_get_global(void) {
    // Initialize mutex on first use (thread-safe once-only initialization)
    if (!mutex_initialized) {
        static xmd_mutex_t init_mutex = {0};
        xmd_mutex_init(&init_mutex);
        xmd_mutex_lock(&init_mutex);
        if (!mutex_initialized) {
            xmd_mutex_init(&config_mutex);
            mutex_initialized = true;
        }
        xmd_mutex_unlock(&init_mutex);
    }
    
    xmd_mutex_lock(&config_mutex);
    xmd_internal_config* result = global_config;
    xmd_mutex_unlock(&config_mutex);
    
    return result;
}