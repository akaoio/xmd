/**
 * @file xmd.h
 * @brief Main header file for XMD (eXtended MarkDown) processor
 * 
 * This header provides the core API for XMD processing, including
 * markdown parsing, variable management, and command execution.
 */

#ifndef XMD_H
#define XMD_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Version information */
#define XMD_VERSION_MAJOR 0
#define XMD_VERSION_MINOR 0
#define XMD_VERSION_PATCH 2
#define XMD_VERSION_STRING "0.0.2"

/* Error codes */
typedef enum {
    XMD_SUCCESS = 0,
    XMD_ERROR_PARSE = 1,
    XMD_ERROR_SYNTAX = 2,
    XMD_ERROR_PERMISSION = 3,
    XMD_ERROR_MODULE_NOT_FOUND = 4,
    XMD_ERROR_CIRCULAR_DEPENDENCY = 5,
    XMD_ERROR_COMMAND_FAILED = 6,
    XMD_ERROR_OUT_OF_MEMORY = 7,
    XMD_ERROR_TIMEOUT = 8,
    XMD_ERROR_INVALID_ARGUMENT = 9,
    XMD_ERROR_FILE_NOT_FOUND = 10
} xmd_error_code;

/* Forward declarations */
typedef struct xmd_config xmd_config;
typedef struct xmd_processor xmd_processor;
typedef struct xmd_result xmd_result;

/**
 * @brief XMD processing result
 * @struct xmd_result
 * 
 * Contains the processed output and any error information.
 */
typedef struct xmd_result {
    xmd_error_code error_code;      /**< Error code (XMD_SUCCESS if no error) */
    char* output;                   /**< Processed markdown output */
    char* error_message;            /**< Error message if error_code != XMD_SUCCESS */
    size_t output_length;           /**< Length of output string */
    uint64_t processing_time_ms;    /**< Processing time in milliseconds */
    uint64_t memory_used_bytes;     /**< Peak memory usage in bytes */
} xmd_result;

/**
 * @brief Sandbox configuration for command execution
 * @struct xmd_sandbox_config
 */
typedef struct xmd_sandbox_config {
    char** exec_whitelist;          /**< Allowed commands (NULL-terminated array) */
    char** exec_blacklist;          /**< Forbidden commands (NULL-terminated array) */
    char** allowed_paths;           /**< Allowed filesystem paths */
    char** blocked_paths;           /**< Blocked filesystem paths */
    char** allowed_networks;        /**< Allowed network destinations */
    uint32_t max_memory_mb;         /**< Maximum memory usage in MB */
    uint32_t max_cpu_time_ms;       /**< Maximum CPU time in milliseconds */
    uint32_t max_wall_time_ms;      /**< Maximum wall time in milliseconds */
    bool allow_network;             /**< Whether to allow network access */
    bool allow_filesystem_write;    /**< Whether to allow filesystem writes */
} xmd_sandbox_config;

/**
 * @brief XMD processor configuration
 * @struct xmd_config
 */
typedef struct xmd_config {
    /* Execution settings */
    xmd_sandbox_config* sandbox;    /**< Sandbox configuration */
    uint32_t max_recursion_depth;   /**< Maximum recursion depth */
    uint32_t max_loop_iterations;   /**< Maximum loop iterations */
    
    /* Cache settings */
    uint64_t cache_max_memory;      /**< Maximum cache memory in bytes */
    uint32_t cache_default_ttl_ms;  /**< Default cache TTL in milliseconds */
    
    /* Module settings */
    char** module_search_paths;     /**< Module search paths */
    size_t search_path_count;       /**< Number of search paths */
    
    /* Output settings */
    bool preserve_comments;         /**< Whether to preserve HTML comments */
    bool pretty_print;              /**< Whether to format output nicely */
    char* output_format;            /**< Output format: "markdown", "html", "json" */
    
    /* Debug settings */
    bool debug_mode;                /**< Enable debug mode */
    bool trace_execution;           /**< Enable execution tracing */
    char* log_level;                /**< Log level: "error", "warn", "info", "debug" */
} xmd_config;

/* Core API functions */

/**
 * @brief Create default XMD configuration
 * @return Default configuration structure
 */
xmd_config* xmd_config_create_default(void);

/**
 * @brief Create a new XMD configuration with default values
 * @return New configuration or NULL on error
 */
xmd_config* xmd_config_new(void);

/**
 * @brief Free XMD configuration
 * @param config Configuration to free
 */
void xmd_config_free(xmd_config* config);

/**
 * @brief Create XMD processor with given configuration
 * @param config Configuration for the processor
 * @return Processor instance or NULL on error
 */
xmd_processor* xmd_processor_create(const xmd_config* config);

/**
 * @brief Free XMD processor
 * @param processor Processor to free
 */
void xmd_processor_free(xmd_processor* processor);

/**
 * @brief Process markdown string with XMD directives
 * @param processor XMD processor instance
 * @param input Input markdown string
 * @param input_length Length of input string (0 for NULL-terminated)
 * @return Processing result (must be freed with xmd_result_free)
 */
xmd_result* xmd_process_string(xmd_processor* processor, 
                               const char* input, 
                               size_t input_length);

/**
 * @brief Process markdown file with XMD directives
 * @param processor XMD processor instance
 * @param input_path Path to input markdown file
 * @return Processing result (must be freed with xmd_result_free)
 */
xmd_result* xmd_process_file(xmd_processor* processor, 
                             const char* input_path);

/**
 * @brief Free XMD processing result
 * @param result Result to free
 */
void xmd_result_free(xmd_result* result);

/**
 * @brief Set variable in processor
 * @param processor XMD processor instance
 * @param key Variable name
 * @param value Variable value (JSON string)
 * @return Error code
 */
xmd_error_code xmd_set_variable(xmd_processor* processor,
                                const char* key,
                                const char* value);

/**
 * @brief Get variable from processor
 * @param processor XMD processor instance
 * @param key Variable name
 * @return Variable value as JSON string (must be freed) or NULL if not found
 */
char* xmd_get_variable(xmd_processor* processor, const char* key);

/**
 * @brief Validate XMD syntax without processing
 * @param input Input markdown string
 * @param input_length Length of input string (0 for NULL-terminated)
 * @return Error code
 */
xmd_error_code xmd_validate_syntax(const char* input, size_t input_length);

/**
 * @brief Get version information
 * @return Version string
 */
const char* xmd_get_version(void);

/* Utility functions */

/**
 * @brief Get error message for error code
 * @param error_code Error code
 * @return Human-readable error message
 */
const char* xmd_error_string(xmd_error_code error_code);

/**
 * @brief Initialize XMD library (optional)
 * @return Error code
 */
xmd_error_code xmd_init(void);

/**
 * @brief Cleanup XMD library (optional)
 */
void xmd_cleanup(void);

// =============================================================================
// Phase 8: Documentation and Community Tools
// =============================================================================

/**
 * @brief Generate interactive tutorials from example files
 * @param source_dir Directory containing example files
 * @param output_dir Directory to write generated tutorials
 * @return 0 on success, -1 on error
 */
int tutorial_generate(const char* source_dir, const char* output_dir);

/**
 * @brief Generate comprehensive examples documentation
 * @param source_dir Directory containing example files
 * @param output_dir Directory to write generated examples
 * @return 0 on success, -1 on error
 */
int examples_generate(const char* source_dir, const char* output_dir);

/**
 * @brief Generate API reference documentation from header files
 * @param include_dir Directory containing header files
 * @param output_file Output file for generated reference
 * @return 0 on success, -1 on error
 */
int reference_generate(const char* include_dir, const char* output_file);

/**
 * @brief Trace XMD execution with detailed logging
 * @param input_file Path to XMD file to trace
 * @param output_file Path to write trace log
 * @return 0 on success, -1 on error
 */
int debugger_trace(const char* input_file, const char* output_file);

/**
 * @brief Check XMD syntax and style
 * @param content XMD content to check
 * @return 0 if valid, -1 if errors found
 */
int linter_check(const char* content);

/**
 * @brief Format XMD content for consistent style
 * @param content XMD content to format
 * @param output_file Path to write formatted content
 * @return 0 on success, -1 on error
 */
int formatter_format(const char* content, const char* output_file);

#ifdef __cplusplus
}
#endif

#endif /* XMD_H */
