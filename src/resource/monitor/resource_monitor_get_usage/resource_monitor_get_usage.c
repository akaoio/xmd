/**
 * @file resource_monitor_get_usage.c
 * @brief Get resource usage
 */

#include <string.h>
#include <stdint.h>
#include "../../../../include/resource.h"
#include "../../../../include/platform.h"
#include "utils/common/common_macros.h"

size_t get_memory_usage(void);
int count_file_descriptors(void);
/**
 * @return 0 on success, -1 on error
 */
int resource_monitor_get_usage(ResourceMonitor* monitor, ResourceUsage* usage) {
    XMD_VALIDATE_PTRS(-1, monitor, usage);
    
    memset(usage, 0, sizeof(ResourceUsage));
    
    // Get elapsed time if monitoring
    if (monitor->is_monitoring) {
        xmd_time_t current_time;
        xmd_get_time(&current_time);
        int64_t diff_seconds = current_time.seconds - monitor->start_time.seconds;
        int64_t diff_nanoseconds = current_time.nanoseconds - monitor->start_time.nanoseconds;
        usage->elapsed_time_ms = (long)(diff_seconds * 1000 + diff_nanoseconds / 1000000);
    }
    
    // Memory usage would be retrieved from system here
    usage->memory_bytes = get_memory_usage();
    usage->cpu_time_ms = 0;
    usage->file_descriptors = count_file_descriptors();
    
    return 0;
}
