/**
 * @file create_default_timing.c
 * @brief Default timing configuration creation function
 * @author XMD Team
 *
 * Implementation of default timing configuration creation for the XMD config system.
 */

#include "../../../include/config_internal.h"

/**
 * @brief Create default timing configuration
 * @return Default timing configuration
 */
xmd_timing_config create_default_timing(void) {
    xmd_timing_config timing = {
        .graceful_shutdown_wait_us = 100000,  // 100ms
        .process_check_interval_us = 10000,   // 10ms
        .cache_ttl_ms = 5 * 60 * 1000        // 5 minutes
    };
    return timing;
}