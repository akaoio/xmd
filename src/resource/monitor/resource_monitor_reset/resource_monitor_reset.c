/**
 * @file resource_monitor_reset.c
 * @brief Reset resource monitor
 */

#include <string.h>
#include <stdlib.h>
#include "../../../../include/resource.h"
#include "../../../../include/platform.h"
int resource_monitor_reset(ResourceMonitor* monitor) {
    if (!monitor) return -1;
    memset(&monitor->start_time, 0, sizeof(xmd_time_t));
    monitor->is_monitoring = 0;
    free(monitor->last_error);
    monitor->last_error = NULL;
    return 0;
}
