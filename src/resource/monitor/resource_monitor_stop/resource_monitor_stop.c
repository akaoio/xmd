/**
 * @file resource_monitor_stop.c
 * @brief Stop resource monitoring
 */

#include "../../../../include/resource.h"
int resource_monitor_stop(ResourceMonitor* monitor) {
    if (!monitor) return -1;
    monitor->is_monitoring = 0;
    return 0;
    // end_time is not a field in ResourceMonitor struct
    // final_memory is not a field in ResourceMonitor struct
}
