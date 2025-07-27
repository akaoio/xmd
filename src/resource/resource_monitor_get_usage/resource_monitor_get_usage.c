/**
 * @file resource_monitor_get_usage.c
 * @brief Resource usage retrieval function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include "../../../include/platform.h"
#include "../../../include/resource.h"

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