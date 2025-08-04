/**
 * @file resource_monitor_start.c
 * @brief Start resource monitoring
 */

#include "../../../../include/resource.h"
#include "../../../../include/platform.h"
#include "utils/common/common_macros.h"
int resource_monitor_start(ResourceMonitor* monitor) {
    XMD_VALIDATE_PTRS(-1, monitor);
    xmd_get_time(&monitor->start_time);
    monitor->is_monitoring = 1;
    return 0;
}
