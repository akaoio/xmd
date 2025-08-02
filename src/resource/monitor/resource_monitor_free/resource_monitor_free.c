/**
 * @file resource_monitor_free.c
 * @brief Free resource monitor
 */

#include <stdlib.h>
#include "../../../../include/resource.h"
void resource_monitor_free(ResourceMonitor* monitor) {
    if (!monitor) return;
    free(monitor->last_error);
    free(monitor);
}
