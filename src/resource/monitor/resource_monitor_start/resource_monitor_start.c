/**
 * @file resource_monitor_start.c
 * @brief Start resource monitoring
 */

#include "../../../../include/resource.h"
#include "../../../../include/platform.h"
int resource_monitor_start(ResourceMonitor* monitor) {
    if (!monitor) {
        return -1;
    }
    xmd_get_time(&monitor->start_time);
    monitor->is_monitoring = 1;
    return 0;
}
