/**
 * @file resource_monitor_free.c
 * @brief Resource monitor cleanup function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/resource.h"

/**
 * @brief Free a resource monitor
 * @param monitor Resource monitor to free
 */
void resource_monitor_free(ResourceMonitor* monitor) {
    if (!monitor) {
        return;
    }
    
    free(monitor->last_error);
    free(monitor);
}