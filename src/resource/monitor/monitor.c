/**
 * @file monitor.c
 * @brief Resource monitor implementation
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/platform.h"
#include "../../../include/resource.h"

/**
 * @brief Resource monitor context structure
 */
struct resource_monitor {
    xmd_time_t start_time;      /**< Monitoring start time */
    int is_monitoring;          /**< Whether monitoring is active */
    char* last_error;           /**< Last error message */
};

/**
 * @brief Create a new resource monitor
 * @return New resource monitor or NULL on error
 */
ResourceMonitor* resource_monitor_new(void) {
    ResourceMonitor* monitor = malloc(sizeof(ResourceMonitor));
    if (!monitor) {
        return NULL;
    }
    
    monitor->is_monitoring = 0;
    monitor->last_error = NULL;
    memset(&monitor->start_time, 0, sizeof(xmd_time_t));
    
    return monitor;
}

/**
 * @brief Free a resource monitor
 * @param monitor Resource monitor to free
 */
void resource_monitor_free(ResourceMonitor* monitor) {
    if (!monitor) {
        return;
    }
    
    free(monitor->last_error);
    free(monitor);
}

/**
 * @brief Set error message in monitor
 * @param monitor Resource monitor
 * @param message Error message
 */
static void set_monitor_error(ResourceMonitor* monitor, const char* message) {
    if (!monitor || !message) {
        return;
    }
    
    free(monitor->last_error);
    monitor->last_error = strdup(message);
}

/**
 * @brief Get current memory usage using platform-specific method
 * @return Memory usage in bytes, or -1 on error
 */
static long get_memory_usage(void) {
    return xmd_get_memory_usage();
}

/**
 * @brief Count open file descriptors using platform-specific method
 * @return Number of open file descriptors, or -1 on error
 */
static int count_file_descriptors(void) {
    return xmd_get_fd_count();
}

/**
 * @brief Get elapsed time in milliseconds
 * @param start_time Start time
 * @return Elapsed time in milliseconds
 */
static long get_elapsed_time_ms(const xmd_time_t* start_time) {
    xmd_time_t current_time;
    xmd_get_time(&current_time);
    
    long elapsed_sec = current_time.seconds - start_time->seconds;
    long elapsed_nsec = current_time.nanoseconds - start_time->nanoseconds;
    
    return (elapsed_sec * 1000) + (elapsed_nsec / 1000000);
}

/**
 * @brief Start monitoring resource usage
 * @param monitor Resource monitor
 * @return ResourceResult indicating success/failure
 */
int resource_monitor_start(ResourceMonitor* monitor) {
    if (!monitor) {
        return RESOURCE_ERROR;
    }
    
    if (monitor->is_monitoring) {
        set_monitor_error(monitor, "Monitor is already running");
        return RESOURCE_ERROR;
    }
    
    if (xmd_get_time(&monitor->start_time) != 0) {
        set_monitor_error(monitor, "Failed to get start time");
        return RESOURCE_ERROR;
    }
    
    monitor->is_monitoring = 1;
    return RESOURCE_SUCCESS;
}

/**
 * @brief Stop monitoring resource usage
 * @param monitor Resource monitor
 * @return ResourceResult indicating success/failure
 */
int resource_monitor_stop(ResourceMonitor* monitor) {
    if (!monitor) {
        return RESOURCE_ERROR;
    }
    
    if (!monitor->is_monitoring) {
        set_monitor_error(monitor, "Monitor is not running");
        return RESOURCE_ERROR;
    }
    
    monitor->is_monitoring = 0;
    return RESOURCE_SUCCESS;
}

/**
 * @brief Get current resource usage
 * @param monitor Resource monitor
 * @param usage Resource usage structure to fill
 * @return ResourceResult indicating success/failure
 */
int resource_monitor_get_usage(ResourceMonitor* monitor, ResourceUsage* usage) {
    if (!monitor || !usage) {
        return RESOURCE_ERROR;
    }
    
    if (!monitor->is_monitoring) {
        set_monitor_error(monitor, "Monitor is not running");
        return RESOURCE_ERROR;
    }
    
    // Get CPU time using platform-specific method
    usage->cpu_time_ms = xmd_get_cpu_time();
    
    // Get memory usage
    uint64_t mem = get_memory_usage();
    usage->memory_bytes = (long)mem;
    
    // Get execution time
    usage->execution_time_ms = get_elapsed_time_ms(&monitor->start_time);
    
    // Get file descriptor count
    usage->file_descriptors = count_file_descriptors();
    if (usage->file_descriptors < 0) {
        usage->file_descriptors = 0; // Fallback to 0 if unable to count
    }
    
    return RESOURCE_SUCCESS;
}

/**
 * @brief Reset resource monitoring counters
 * @param monitor Resource monitor
 * @return ResourceResult indicating success/failure
 */
int resource_monitor_reset(ResourceMonitor* monitor) {
    if (!monitor) {
        return RESOURCE_ERROR;
    }
    
    if (!monitor->is_monitoring) {
        set_monitor_error(monitor, "Monitor is not running");
        return RESOURCE_ERROR;
    }
    
    if (xmd_get_time(&monitor->start_time) != 0) {
        set_monitor_error(monitor, "Failed to reset start time");
        return RESOURCE_ERROR;
    }
    
    return RESOURCE_SUCCESS;
}
