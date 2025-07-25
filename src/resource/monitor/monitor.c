/**
 * @file monitor.c
 * @brief Resource monitor implementation
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <dirent.h>
#include "../../../include/resource.h"

/**
 * @brief Resource monitor context structure
 */
struct resource_monitor {
    struct timeval start_time;  /**< Monitoring start time */
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
    memset(&monitor->start_time, 0, sizeof(struct timeval));
    
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
 * @brief Get current memory usage from /proc/self/status
 * @return Memory usage in bytes, or -1 on error
 */
static long get_memory_usage(void) {
    FILE* file = fopen("/proc/self/status", "r");
    if (!file) {
        return -1;
    }
    
    char line[256];
    long memory_kb = -1;
    
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "VmRSS:", 6) == 0) {
            sscanf(line, "VmRSS: %ld kB", &memory_kb);
            break;
        }
    }
    
    fclose(file);
    return memory_kb > 0 ? memory_kb * 1024 : -1; // Convert to bytes
}

/**
 * @brief Count open file descriptors
 * @return Number of open file descriptors, or -1 on error
 */
static int count_file_descriptors(void) {
    DIR* fd_dir = opendir("/proc/self/fd");
    if (!fd_dir) {
        return -1;
    }
    
    int count = 0;
    struct dirent* entry;
    
    while ((entry = readdir(fd_dir)) != NULL) {
        if (entry->d_name[0] != '.') {
            count++;
        }
    }
    
    closedir(fd_dir);
    return count;
}

/**
 * @brief Get elapsed time in milliseconds
 * @param start_time Start time
 * @return Elapsed time in milliseconds
 */
static long get_elapsed_time_ms(const struct timeval* start_time) {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    
    long elapsed_sec = current_time.tv_sec - start_time->tv_sec;
    long elapsed_usec = current_time.tv_usec - start_time->tv_usec;
    
    return (elapsed_sec * 1000) + (elapsed_usec / 1000);
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
    
    if (gettimeofday(&monitor->start_time, NULL) != 0) {
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
    
    // Get CPU time using getrusage
    struct rusage rusage_data;
    if (getrusage(RUSAGE_SELF, &rusage_data) != 0) {
        set_monitor_error(monitor, "Failed to get resource usage");
        return RESOURCE_ERROR;
    }
    
    // Calculate CPU time in milliseconds
    usage->cpu_time_ms = (rusage_data.ru_utime.tv_sec + rusage_data.ru_stime.tv_sec) * 1000 +
                        (rusage_data.ru_utime.tv_usec + rusage_data.ru_stime.tv_usec) / 1000;
    
    // Get memory usage
    usage->memory_bytes = get_memory_usage();
    if (usage->memory_bytes < 0) {
        usage->memory_bytes = 0; // Fallback to 0 if unable to read
    }
    
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
    
    if (gettimeofday(&monitor->start_time, NULL) != 0) {
        set_monitor_error(monitor, "Failed to reset start time");
        return RESOURCE_ERROR;
    }
    
    return RESOURCE_SUCCESS;
}