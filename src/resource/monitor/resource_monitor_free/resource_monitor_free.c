/**
 * @file resource_monitor_free.c
 * @brief Free resource monitor
 */

#include <stdlib.h>
#include "../../../../include/resource.h"
#include "../../../../utils/common/common_macros.h"
void resource_monitor_free(ResourceMonitor* monitor) {
    XMD_ENTRY_VALIDATE_VOID(monitor);
    XMD_FREE_SAFE(monitor->last_error);
    XMD_FREE_SAFE(monitor);
}
