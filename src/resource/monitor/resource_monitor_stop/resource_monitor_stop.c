/**
 * @file resource_monitor_stop.c
 * @brief Stop resource monitoring
 */

#include "../../../../include/resource.h"
#include "../../../utils/common/common_macros.h"
int resource_monitor_stop(ResourceMonitor* monitor) {
    XMD_VALIDATE_PTRS(-1, monitor);
    monitor->is_monitoring = 0;
    return 0;
    // end_time is not a field in ResourceMonitor struct
    // final_memory is not a field in ResourceMonitor struct
}
