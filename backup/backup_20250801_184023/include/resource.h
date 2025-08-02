/**
 * @file resource.h
 * @brief Resource management system for XMD
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#ifndef RESOURCE_H
#define RESOURCE_H

#include "platform.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Resource usage information
 */
typedef struct {
    long cpu_time_ms;           /**< CPU time used in milliseconds */
    long memory_bytes;          /**< Memory used in bytes */
    long memory_usage;          /**< Memory used in bytes (alias) */
    long execution_time_ms;     /**< Wall clock time in milliseconds */
    long elapsed_time_ms;       /**< Elapsed time in milliseconds */
    int file_descriptors;       /**< Number of open file descriptors */
} ResourceUsage;

/**
 * @brief Resource result codes
 */
typedef enum {
    RESOURCE_SUCCESS = 0,       /**< Operation successful */
    RESOURCE_ERROR = -1,        /**< General error */
    RESOURCE_LIMIT_EXCEEDED = -2, /**< Resource limit exceeded */
    RESOURCE_TIMEOUT = -3       /**< Operation timed out */
} ResourceResult;

/**
 * @brief Resource limiter context structure
 */
struct resource_limiter {
    long max_memory_mb;         /**< Maximum memory in MB */
    long max_cpu_time_ms;       /**< Maximum CPU time in milliseconds */
    long max_execution_time_ms; /**< Maximum execution time in milliseconds */
    char* last_error;           /**< Last error message */
};

/**
 * @brief Resource monitor context structure
 */
struct resource_monitor {
    xmd_time_t start_time;      /**< Monitoring start time */
    int is_monitoring;          /**< Whether monitoring is active */
    char* last_error;           /**< Last error message */
};

/**
 * @brief Resource limiter context typedef
 */
typedef struct resource_limiter ResourceLimiter;

/**
 * @brief Resource monitor context typedef
 */
typedef struct resource_monitor ResourceMonitor;

/**
 * @brief Create a new resource limiter
 * @return New resource limiter or NULL on error
 */
ResourceLimiter* resource_limiter_new(void);

/**
 * @brief Free a resource limiter
 * @param limiter Resource limiter to free
 */
void resource_limiter_free(ResourceLimiter* limiter);

/**
 * @brief Set memory limit
 * @param limiter Resource limiter
 * @param max_memory_mb Maximum memory in MB
 * @return ResourceResult indicating success/failure
 */
int resource_limiter_set_memory_limit(ResourceLimiter* limiter, long max_memory_mb);

/**
 * @brief Set CPU time limit
 * @param limiter Resource limiter
 * @param max_cpu_time_ms Maximum CPU time in milliseconds
 * @return ResourceResult indicating success/failure
 */
int resource_limiter_set_cpu_limit(ResourceLimiter* limiter, long max_cpu_time_ms);

/**
 * @brief Set execution time limit
 * @param limiter Resource limiter
 * @param max_execution_time_ms Maximum execution time in milliseconds
 * @return ResourceResult indicating success/failure
 */
int resource_limiter_set_time_limit(ResourceLimiter* limiter, long max_execution_time_ms);

/**
 * @brief Check if resource usage is within limits
 * @param limiter Resource limiter
 * @param usage Current resource usage
 * @return ResourceResult indicating within limits or exceeded
 */
int resource_limiter_check_limits(ResourceLimiter* limiter, ResourceUsage* usage);

/**
 * @brief Create a new resource monitor
 * @return New resource monitor or NULL on error
 */
ResourceMonitor* resource_monitor_new(void);

/**
 * @brief Free a resource monitor
 * @param monitor Resource monitor to free
 */
void resource_monitor_free(ResourceMonitor* monitor);

/**
 * @brief Start monitoring resource usage
 * @param monitor Resource monitor
 * @return ResourceResult indicating success/failure
 */
int resource_monitor_start(ResourceMonitor* monitor);

/**
 * @brief Stop monitoring resource usage
 * @param monitor Resource monitor
 * @return ResourceResult indicating success/failure
 */
int resource_monitor_stop(ResourceMonitor* monitor);

/**
 * @brief Get current resource usage
 * @param monitor Resource monitor
 * @param usage Resource usage structure to fill
 * @return ResourceResult indicating success/failure
 */
int resource_monitor_get_usage(ResourceMonitor* monitor, ResourceUsage* usage);

/**
 * @brief Reset resource monitoring counters
 * @param monitor Resource monitor
 * @return ResourceResult indicating success/failure
 */
int resource_monitor_reset(ResourceMonitor* monitor);

/**
 * @brief Set error message in monitor
 * @param monitor Resource monitor
 * @param message Error message
 */
void set_monitor_error(ResourceMonitor* monitor, const char* message);

/**
 * @brief Get current memory usage using platform-specific method
 * @return Memory usage in bytes, or -1 on error
 */
uint64_t get_memory_usage(void);

/**
 * @brief Count open file descriptors using platform-specific method
 * @return Number of open file descriptors, or -1 on error
 */
int count_file_descriptors(void);

/**
 * @brief Get elapsed time in milliseconds
 * @param start_time Start time
 * @return Elapsed time in milliseconds
 */
long get_elapsed_time_ms(const xmd_time_t* start_time);

#ifdef __cplusplus
}
#endif

#endif /* RESOURCE_H */
