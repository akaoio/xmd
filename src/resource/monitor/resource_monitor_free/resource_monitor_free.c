/**
 * @file resource_monitor_free.c
 * @brief Free resource monitor
 */

#include <stdlib.h>
#include "../../../../include/resource.h"
void resource_monitor_XMD_FREE_SAFE(ResourceMonitor* monitor) {
    if (!monitor) return;
    XMD_FREE_SAFE(monitor->last_error);
    XMD_FREE_SAFE(monitor);
}
