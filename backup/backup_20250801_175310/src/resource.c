/**
 * @file resource.c
 * @brief Consolidated resource management for XMD
 * @author XMD Development Team
 *
 * All resource monitoring, limiting, and management functionality
 * consolidated from 19 separate directories.
 */

#include "../include/limiter_internal.h" 
#include "../include/memory.h"
#include "../include/utils.h"
#include "../include/platform.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

// ============================================================================
// UTILITY FUNCTIONS
// ============================================================================


/**
 * @brief Get elapsed time in milliseconds
 * @param start Start time
 * @return Elapsed time in milliseconds
 */
long get_elapsed_time_ms(const xmd_time_t* start_time) {
    xmd_time_t current;
    xmd_get_time(&current);
    int64_t diff_seconds = current.seconds - start_time->seconds;
    int64_t diff_nanoseconds = current.nanoseconds - start_time->nanoseconds;
    return (long)(diff_seconds * 1000 + diff_nanoseconds / 1000000);
}

// ============================================================================
// RESOURCE LIMITER
// ============================================================================

/**
 * @brief Create new resource limiter
 * @return New resource limiter or NULL on error
 */
ResourceLimiter* resource_limiter_new(void) {
    ResourceLimiter* limiter = xmd_malloc(sizeof(ResourceLimiter));
    if (!limiter) {
        return NULL;
    }
    
    // Get limits from global configuration
    xmd_internal_config* config = xmd_internal_config_get_global();
    if (config) {
        limiter->max_memory_mb = (uint32_t)config->limits.memory_limit_mb;
        limiter->max_cpu_time_ms = (uint32_t)config->limits.cpu_time_limit_ms;
        limiter->max_execution_time_ms = (uint32_t)config->limits.execution_time_limit_ms;
    } else {
        // Default limits if no config
        limiter->max_memory_mb = 100;
        limiter->max_cpu_time_ms = 5000;
        limiter->max_execution_time_ms = 10000;
    }
    
    limiter->last_error = NULL;
    return limiter;
}

/**
 * @brief Free resource limiter
 * @param limiter Limiter to free
 */
void resource_limiter_free(ResourceLimiter* limiter) {
    if (!limiter) {
        return;
    }
    
    free(limiter->last_error);
    free(limiter);
}

/**
 * @brief Set memory limit
 * @param limiter Resource limiter
 * @param limit_mb Memory limit in MB
 * @return 0 on success, -1 on error
 */
int resource_limiter_set_memory_limit(ResourceLimiter* limiter, long max_memory_mb) {
    if (!limiter) {
        return -1;
    }
    
    limiter->max_memory_mb = max_memory_mb;
    return 0;
}

/**
 * @brief Set CPU time limit
 * @param limiter Resource limiter
 * @param limit_ms CPU time limit in milliseconds
 * @return 0 on success, -1 on error
 */
int resource_limiter_set_cpu_limit(ResourceLimiter* limiter, long max_cpu_time_ms) {
    if (!limiter) {
        return -1;
    }
    
    limiter->max_cpu_time_ms = max_cpu_time_ms;
    return 0;
}

/**
 * @brief Set execution time limit
 * @param limiter Resource limiter
 * @param limit_ms Execution time limit in milliseconds
 * @return 0 on success, -1 on error
 */
int resource_limiter_set_time_limit(ResourceLimiter* limiter, long max_execution_time_ms) {
    if (!limiter) {
        return -1;
    }
    
    limiter->max_execution_time_ms = max_execution_time_ms;
    return 0;
}

/**
 * @brief Check resource limits
 * @param limiter Resource limiter
 * @return 0 if within limits, -1 if exceeded
 */
int resource_limiter_check_limits(ResourceLimiter* limiter, ResourceUsage* usage) {
    if (!limiter) {
        return -1;
    }
    
    // Check memory usage
    size_t memory_usage = get_memory_usage();
    if (memory_usage > (size_t)(limiter->max_memory_mb * 1024 * 1024)) {
        set_limiter_error(limiter, "Memory limit exceeded");
        return -1;
    }
    
    // Update usage if provided
    if (usage) {
        usage->memory_usage = memory_usage;
    }
    
    // Check CPU time - implementation would check actual CPU usage
    // For now, just return success
    return 0;
}

// ============================================================================
// RESOURCE MONITORING
// ============================================================================

/**
 * @brief Start resource monitoring
 * @param monitor Resource monitor
 * @return 0 on success, -1 on error
 */
int resource_monitor_start(ResourceMonitor* monitor) {
    if (!monitor) {
        return -1;
    }
    
    xmd_get_time(&monitor->start_time);
    monitor->is_monitoring = 1;
    
    return 0;
}

/**
 * @brief Stop resource monitoring
 * @param monitor Resource monitor
 * @return 0 on success, -1 on error
 */
int resource_monitor_stop(ResourceMonitor* monitor) {
    if (!monitor) {
        return -1;
    }
    
    // end_time is not a field in ResourceMonitor struct
    // final_memory is not a field in ResourceMonitor struct
    
    return 0;
}

/**
 * @brief Reset resource monitor
 * @param monitor Resource monitor
 */
int resource_monitor_reset(ResourceMonitor* monitor) {
    if (!monitor) {
        return -1;
    }
    
    memset(&monitor->start_time, 0, sizeof(xmd_time_t));
    monitor->is_monitoring = 0;
    free(monitor->last_error);
    monitor->last_error = NULL;
    return 0;
}

/**
 * @brief Get resource usage
 * @param monitor Resource monitor
 * @return Resource usage structure
 */
int resource_monitor_get_usage(ResourceMonitor* monitor, ResourceUsage* usage) {
    if (!monitor || !usage) {
        return -1;
    }
    
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

/**
 * @brief Free resource monitor
 * @param monitor Resource monitor
 */
void resource_monitor_free(ResourceMonitor* monitor) {
    if (!monitor) {
        return;
    }
    
    free(monitor);
}

// ============================================================================
// UTILITY FUNCTIONS
// ============================================================================


/**
 * @brief Get current memory usage
 * @return Memory usage in bytes
 */
size_t get_memory_usage(void) {
    // Real memory usage implementation using /proc/self/status
    #ifdef __linux__
    FILE* file = fopen("/proc/self/status", "r");
    if (!file) {
        return 0;
    }
    
    char line[256];
    size_t vm_rss = 0;
    
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "VmRSS:", 6) == 0) {
            sscanf(line, "VmRSS: %zu kB", &vm_rss);
            break;
        }
    }
    
    fclose(file);
    return vm_rss * 1024; // Convert kB to bytes
    #else
    // Fallback for non-Linux systems
    return 0;
    #endif
}

/**
 * @brief Count file descriptors
 * @return Number of open file descriptors
 */
int count_file_descriptors(void) {
    // Real file descriptor counting implementation
    #ifdef __linux__
    int count = 0;
    DIR* fd_dir = opendir("/proc/self/fd");
    if (!fd_dir) {
        return 0;
    }
    
    struct dirent* entry;
    while ((entry = readdir(fd_dir)) != NULL) {
        // Skip . and .. entries
        if (entry->d_name[0] != '.') {
            count++;
        }
    }
    
    closedir(fd_dir);
    return count;
    #else
    // Fallback for non-Linux systems - use resource limits
    struct rlimit limit;
    if (getrlimit(RLIMIT_NOFILE, &limit) == 0) {
        return (int)limit.rlim_cur;
    }
    return 0;
    #endif
}

/**
 * @brief Set limiter error message
 * @param limiter Resource limiter
 * @param error Error message
 */
void set_limiter_error(ResourceLimiter* limiter, const char* error) {
    if (!limiter || !error) {
        return;
    }
    
    free(limiter->last_error);
    limiter->last_error = xmd_strdup(error);
}

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
    monitor->last_error = xmd_strdup(message);
}
