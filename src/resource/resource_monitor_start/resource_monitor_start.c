/**
 * @file resource_monitor_start.c
 * @brief Resource monitor start function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <string.h>
#include "../../../include/platform.h"
#include "../../../include/resource.h"

/**
 * @brief Start monitoring resource usage
 * @param monitor Resource monitor
 * @return ResourceResult indicating success/failure
 */
int resource_monitor_start(ResourceMonitor* monitor) {
    if (!monitor) {
        return RESOURCE_ERROR;
    }
    
    if (monitor->is_monitoring) {
        set_monitor_error(monitor, "Monitor is already running");
        return RESOURCE_ERROR;
    }
    
    if (xmd_get_time(&monitor->start_time) != 0) {
        set_monitor_error(monitor, "Failed to get start time");
        return RESOURCE_ERROR;
    }
    
    monitor->is_monitoring = 1;
    return RESOURCE_SUCCESS;
}