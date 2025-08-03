/**
 * @file core_macros.h
 * @brief Core system macro consolidation for duplication reduction
 * @author XMD Team - Zero Duplication Campaign
 * @date 2025-08-03
 */

#ifndef CORE_MACROS_H
#define CORE_MACROS_H

#include "utils/common/common_macros.h"

/**
 * @brief Standard runtime configuration validation
 */
#define XMD_RUNTIME_VALIDATE_CONFIG(config, func_name) \
    do { \
        if (!config) { \
            fprintf(stderr, "Error: %s: config is NULL\n", func_name); \
            return false; \
        } \
        if (config->max_stack_depth <= 0) { \
            fprintf(stderr, "Error: %s: invalid max_stack_depth: %d\n", \
                    func_name, config->max_stack_depth); \
            return false; \
        } \
        if (config->max_recursion_depth <= 0) { \
            fprintf(stderr, "Error: %s: invalid max_recursion_depth: %d\n", \
                    func_name, config->max_recursion_depth); \
            return false; \
        } \
    } while(0)

/**
 * @brief Standard runtime debug output
 */
#define XMD_RUNTIME_DEBUG_PRINT(config) \
    do { \
        if (config && config->debug_mode) { \
            printf("XMD Runtime initialized:\n"); \
            printf("  Version: %s\n", config->version ? config->version : "unknown"); \
            printf("  Debug: %s\n", config->debug_mode ? "true" : "false"); \
            printf("  Strict: %s\n", config->strict_mode ? "true" : "false"); \
            printf("  Safe: %s\n", config->safe_mode ? "true" : "false"); \
            printf("  Max stack depth: %d\n", config->max_stack_depth); \
            printf("  Max recursion depth: %d\n", config->max_recursion_depth); \
        } \
    } while(0)

/**
 * @brief Standard runtime status debugging
 */
#define XMD_RUNTIME_STATUS_DEBUG(status) \
    do { \
        if (getenv("XMD_DEBUG")) { \
            const char* status_names[] = { \
                "UNINITIALIZED", "INITIALIZED", "RUNNING", \
                "PAUSED", "ERROR", "TERMINATED" \
            }; \
            if (status >= 0 && status <= 5) { \
                printf("XMD Runtime status: %s\n", status_names[status]); \
            } \
        } \
    } while(0)

/**
 * @brief Standard cleanup counter with debug
 */
#define XMD_RUNTIME_CLEANUP_DEBUG(count) \
    do { \
        if (getenv("XMD_DEBUG")) { \
            printf("XMD Runtime cleanup called (count: %d)\n", count); \
        } \
    } while(0)

/**
 * @brief Standard configuration validation pattern
 */
#define XMD_CONFIG_VALIDATE_LIMITS(config, func_name) \
    do { \
        if (config->limits.memory_limit_mb == 0 || \
            config->limits.cpu_time_limit_ms == 0 || \
            config->limits.execution_time_limit_ms == 0) { \
            XMD_ERROR_RETURN(-1, "%s: Invalid resource limits configuration", func_name); \
        } \
    } while(0)

/**
 * @brief Standard configuration buffer validation
 */
#define XMD_CONFIG_VALIDATE_BUFFERS(config, func_name) \
    do { \
        if (config->buffers.line_buffer_size == 0 || \
            config->buffers.conversion_buffer_size == 0 || \
            config->buffers.initial_store_capacity == 0) { \
            XMD_ERROR_RETURN(-1, "%s: Invalid buffer configuration", func_name); \
        } \
        if (config->buffers.store_load_factor <= 0.0 || \
            config->buffers.store_load_factor >= 1.0) { \
            XMD_ERROR_RETURN(-1, "%s: Invalid store load factor", func_name); \
        } \
    } while(0)

/**
 * @brief Standard configuration precision validation
 */
#define XMD_CONFIG_VALIDATE_PRECISION(config, func_name) \
    do { \
        if (config->precision.float_epsilon <= 0.0 || \
            config->precision.number_format == NULL) { \
            XMD_ERROR_RETURN(-1, "%s: Invalid precision configuration", func_name); \
        } \
    } while(0)

/**
 * @brief Complete configuration validation
 */
#define XMD_CONFIG_FULL_VALIDATE(config, func_name) \
    do { \
        XMD_VALIDATE_PTRS(-1, config); \
        XMD_CONFIG_VALIDATE_LIMITS(config, func_name); \
        XMD_CONFIG_VALIDATE_BUFFERS(config, func_name); \
        XMD_CONFIG_VALIDATE_PRECISION(config, func_name); \
    } while(0)

/**
 * @brief Safe configuration memory cleanup pattern
 */
#define XMD_CONFIG_CLEANUP_PATHS(internal) \
    do { \
        XMD_FREE_SAFE(internal->paths.proc_status_path); \
        XMD_FREE_SAFE(internal->paths.proc_fd_path); \
        XMD_FREE_SAFE(internal->paths.temp_dir); \
        if (internal->paths.module_search_paths) { \
            for (size_t i = 0; i < internal->paths.module_search_path_count; i++) { \
                XMD_FREE_SAFE(internal->paths.module_search_paths[i]); \
            } \
            XMD_FREE_SAFE(internal->paths.module_search_paths); \
        } \
    } while(0)

/**
 * @brief Safe security whitelist cleanup pattern
 */
#define XMD_CONFIG_CLEANUP_SECURITY(internal) \
    do { \
        if (internal->security.exec_whitelist) { \
            for (size_t i = 0; i < internal->security.exec_whitelist_count; i++) { \
                XMD_FREE_SAFE(internal->security.exec_whitelist[i]); \
            } \
            XMD_FREE_SAFE(internal->security.exec_whitelist); \
        } \
    } while(0)

#endif /* CORE_MACROS_H */
