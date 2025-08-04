/**
 * @file set_monitor_error.c
 * @brief Set error message in monitor
 */

#include <stdlib.h>
#include "../../../../include/resource.h"
#include "../../../../include/utils.h"
#include "../../../../utils/common/common_macros.h"
void set_monitor_error(ResourceMonitor* monitor, const char* message) {
    XMD_ENTRY_VALIDATE_VOID(monitor, message);
    XMD_FREE_SAFE(monitor->last_error);
    monitor->last_error = xmd_strdup(message);
}
