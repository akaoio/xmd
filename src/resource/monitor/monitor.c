/**
 * @file monitor.c
 * @brief Resource monitor implementation
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/resource.h"

/**
 * @brief Create a new resource monitor
 * @return New resource monitor or NULL on error
 */
ResourceMonitor* resource_monitor_new(void) {
    ResourceMonitor* monitor = malloc(sizeof(ResourceMonitor));
    if (!monitor) {
        return NULL;
    }
    
    monitor->start_time = (xmd_time_t){0, 0};
    monitor->is_monitoring = 0;
    monitor->last_error = NULL;
    
    return monitor;
}
