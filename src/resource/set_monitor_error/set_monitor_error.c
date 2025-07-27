#define _GNU_SOURCE  // For strdup - must be before includes

/**
 * @file set_monitor_error.c
 * @brief Resource monitor error setting function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/resource.h"

/**
 * @brief Set error message in monitor
 * @param monitor Resource monitor
 * @param message Error message
 */
void set_monitor_error(ResourceMonitor* monitor, const char* message) {
    if (!monitor || !message) {
        return;
    }
    
    free(monitor->last_error);
    monitor->last_error = strdup(message);
}