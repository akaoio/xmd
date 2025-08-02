/**
 * @file create_default_timing.c
 * @brief Create default timing settings
 * 
 * This file contains ONLY the create_default_timing function.
 * One function per file - Genesis principle compliance.
 * Extracted from: backup/backup_20250801_184028/src/config_consolidated.c
 */

#include "../../../../include/config_internal.h"

/**
 * @brief Create default timing settings
 * @return Default timing configuration
 */
xmd_timing_config create_default_timing(void) {
    xmd_timing_config timing;
    
    timing.graceful_shutdown_wait_us = 100000; // 100ms graceful shutdown wait
    timing.process_check_interval_us = 1000;   // 1ms process check interval
    timing.cache_ttl_ms = 3600000;             // 1 hour cache TTL
    
    return timing;
}
