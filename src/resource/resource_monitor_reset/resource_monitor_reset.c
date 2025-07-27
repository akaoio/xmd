/**
 * @file resource_monitor_reset.c
 * @brief Resource monitor reset function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include "../../../include/platform.h"
#include "../../../include/resource.h"

/**
 * @brief Reset resource monitoring counters
 * @param monitor Resource monitor
 * @return ResourceResult indicating success/failure
 */
int resource_monitor_reset(ResourceMonitor* monitor) {
    if (!monitor) {
        return RESOURCE_ERROR;
    }
    
    if (!monitor->is_monitoring) {
        set_monitor_error(monitor, "Monitor is not running");
        return RESOURCE_ERROR;
    }
    
    if (xmd_get_time(&monitor->start_time) != 0) {
        set_monitor_error(monitor, "Failed to reset start time");
        return RESOURCE_ERROR;
    }
    
    return RESOURCE_SUCCESS;
}