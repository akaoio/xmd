/**
 * @file resource_monitor_reset.c
 * @brief Reset resource monitor
 */

#include <string.h>
#include <stdlib.h>
#include "../../../../include/resource.h"
#include "../../../../include/platform.h"
#include "../../../utils/common/common_macros.h"
int resource_monitor_reset(ResourceMonitor* monitor) {
    XMD_VALIDATE_PTRS(-1, monitor);
    memset(&monitor->start_time, 0, sizeof(xmd_time_t));
    monitor->is_monitoring = 0;
    XMD_FREE_SAFE(monitor->last_error);
    monitor->last_error = NULL;
    return 0;
}
