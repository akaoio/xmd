/**
 * @file resource_monitor_stop.c
 * @brief Resource monitor stop function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include "../../../include/resource.h"

/**
 * @brief Stop monitoring resource usage
 * @param monitor Resource monitor
 * @return ResourceResult indicating success/failure
 */
int resource_monitor_stop(ResourceMonitor* monitor) {
    if (!monitor) {
        return RESOURCE_ERROR;
    }
    
    if (!monitor->is_monitoring) {
        set_monitor_error(monitor, "Monitor is not running");
        return RESOURCE_ERROR;
    }
    
    monitor->is_monitoring = 0;
    return RESOURCE_SUCCESS;
}