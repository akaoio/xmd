/**
 * @file cli.h
 * @brief Command-line interface and integration system
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#ifndef CLI_H
#define CLI_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "xmd.h"  // Include canonical XMD types

#ifdef __cplusplus
extern "C" {
#endif

// Forward declarations
typedef struct xmd_context xmd_context;

/**
 * @brief CLI command types
 */
typedef enum {
    CLI_CMD_PROCESS = 0,    ///< Process single file
    CLI_CMD_WATCH = 1,      ///< Watch directory
    CLI_CMD_VALIDATE = 2,   ///< Validate syntax
    CLI_CMD_CONFIG = 3,     ///< Show configuration
    CLI_CMD_HELP = 4,       ///< Show help
    CLI_CMD_VERSION = 5,    ///< Show version
    CLI_CMD_PLUGIN = 6      ///< Plugin command
} cli_command_type;

/**
 * @brief CLI argument structure
 */
typedef struct cli_args {
    cli_command_type command;   ///< Command type
    char *input_file;          ///< Input file path
    char *output_file;         ///< Output file path
    char *config_file;         ///< Config file path
    char *watch_dir;           ///< Directory to watch
    char *watch_directory;     ///< Directory to watch (alternate field name)
    char *plugin_name;         ///< Plugin name for plugin command
    bool verbose;              ///< Verbose output flag
    bool quiet;                ///< Quiet output flag
    bool debug;                ///< Debug output flag
    bool help;                 ///< Help flag
    bool version;              ///< Version flag
    int watch_recursive;       ///< Recursive watch flag
} cli_args;

/**
 * @brief CLI context structure
 */
typedef struct cli_context {
    cli_args* args;
    xmd_context* xmd;
    char* program_name;
    int exit_code;
} cli_context;

/**
 * @brief Configuration value types
 */
typedef enum {
    CONFIG_STRING = 0,
    CONFIG_INTEGER = 1,
    CONFIG_BOOLEAN = 2,
    CONFIG_ARRAY = 3,
    CONFIG_OBJECT = 4
} config_value_type;

/**
 * @brief Configuration value structure
 */
typedef struct config_value {
    config_value_type type;
    union {
        char* string_val;
        int64_t integer_val;
        bool boolean_val;
        struct {
            struct config_value** items;
            size_t count;
        } array_val;
        struct {
            char** keys;
            struct config_value** values;
            size_t count;
        } object_val;
    } data;
} config_value;

// xmd_config and xmd_result are now provided by xmd.h

/**
 * @brief Language binding types
 */
typedef enum {
    BINDING_C = 0,
    BINDING_PYTHON = 1,
    BINDING_NODEJS = 2,
    BINDING_GO = 3,
    BINDING_RUST = 4
} binding_type;

/**
 * @brief Plugin manager structure
 */
typedef struct plugin_manager {
    void** plugins;             /**< Array of loaded plugins */
    size_t plugin_count;        /**< Number of loaded plugins */
    size_t plugin_capacity;     /**< Capacity of plugin array */
    bool initialized;           /**< Whether manager is initialized */
} plugin_manager;

// =============================================================================
// CLI Functions
// =============================================================================

/**
 * @brief Initialize CLI context
 * @param argc Argument count
 * @param argv Argument vector
 * @return CLI context or NULL on error
 */
cli_context* cli_init(int argc, char** argv);

/**
 * @brief Parse command line arguments
 * @param argc Argument count
 * @param argv Argument vector
 * @return Parsed arguments or NULL on error
 */
cli_args* cli_parse_args(int argc, char** argv);

/**
 * @brief Execute CLI command
 * @param ctx CLI context
 * @return Exit code
 */
int cli_execute(cli_context* ctx);

/**
 * @brief Show CLI help
 * @param program_name Program name
 */
void cli_show_help(const char* program_name);

/**
 * @brief Show CLI version
 */
void cli_show_version(void);

/**
 * @brief Cleanup CLI context
 * @param ctx CLI context
 */
void cli_cleanup(cli_context* ctx);

/**
 * @brief Process a markdown file
 * @param input_file Input file path
 * @param output_file Output file path (NULL for stdout)
 * @param verbose Verbose output
 * @return Exit code
 */
int cli_process_file(const char* input_file, const char* output_file, bool verbose);

/**
 * @brief Watch directory for changes
 * @param directory Directory to watch
 * @param verbose Verbose output
 * @return Exit code
 */
int cli_watch_directory(const char* directory, bool verbose);

/**
 * @brief Validate XMD file syntax
 * @param input_file Input file path
 * @param verbose Verbose output
 * @return Exit code
 */
int cli_validate_file(const char* input_file, bool verbose);

/**
 * @brief Show configuration
 * @param config_file Config file path (NULL for default)
 * @return Exit code
 */
int cli_show_config(const char* config_file);

/**
 * @brief Create plugin manager
 * @return Plugin manager or NULL on error
 */
plugin_manager* plugin_manager_create(void);

// =============================================================================
// Configuration Functions
// =============================================================================

/**
 * @brief Create configuration structure
 * @return Configuration structure or NULL on error
 */
xmd_config* config_create(void);

/**
 * @brief Load configuration from file
 * @param config Configuration structure
 * @param file_path Path to configuration file
 * @return 0 on success, -1 on error
 */
int config_load_file(xmd_config* config, const char* file_path);

/**
 * @brief Load configuration from environment
 * @param config Configuration structure
 * @return 0 on success, -1 on error
 */
int config_load_env(xmd_config* config);

/**
 * @brief Get configuration value
 * @param config Configuration structure
 * @param key Configuration key
 * @return Configuration value or NULL if not found
 */
config_value* config_get(xmd_config* config, const char* key);

/**
 * @brief Set configuration value
 * @param config Configuration structure
 * @param key Configuration key
 * @param value Configuration value
 * @return 0 on success, -1 on error
 */
int config_set(xmd_config* config, const char* key, config_value* value);

/**
 * @brief Validate configuration
 * @param config Configuration structure
 * @return 0 if valid, -1 if invalid
 */
int config_validate(xmd_config* config);

/**
 * @brief Destroy configuration structure
 * @param config Configuration structure
 */
void config_destroy(xmd_config* config);


// =============================================================================
// C API Functions (for language bindings)
// =============================================================================

// These functions are now defined in c_api_internal.h with c_api_ prefix
// to avoid conflicts with the main XMD API in xmd.h

/**
 * @brief Validate markdown syntax
 * @param handle XMD context handle
 * @param input Input markdown string
 * @param input_length Input string length
 * @return Validation result (must be freed with xmd_result_free)
 */
xmd_result* xmd_validate(void* handle, const char* input, size_t input_length);

/**
 * @brief Set configuration option
 * @param handle XMD context handle
 * @param key Configuration key
 * @param value Configuration value
 * @return 0 on success, -1 on error
 */
int xmd_set_config(void* handle, const char* key, const char* value);

/**
 * @brief Get configuration option
 * @param handle XMD context handle
 * @param key Configuration key
 * @return Configuration value or NULL if not found (must be freed)
 */
char* xmd_get_config(void* handle, const char* key);

/**
 * @brief Free result structure
 * @param result Result structure
 */
void xmd_result_free(xmd_result* result);

// CLI cleanup function is now c_api_xmd_cleanup in c_api_internal.h

// =============================================================================
// Utility Macros
// =============================================================================

/**
 * @brief Check if CLI argument is present
 */
#define CLI_HAS_ARG(args, field) ((args) && (args)->field)

/**
 * @brief Get configuration string value
 */
#define CONFIG_GET_STRING(config, key, default_val) \
    ({ \
        config_value* val = config_get(config, key); \
        (val && val->type == CONFIG_STRING) ? val->data.string_val : default_val; \
    })

/**
 * @brief Get configuration integer value
 */
#define CONFIG_GET_INT(config, key, default_val) \
    ({ \
        config_value* val = config_get(config, key); \
        (val && val->type == CONFIG_INTEGER) ? val->data.integer_val : default_val; \
    })

/**
 * @brief Get configuration boolean value
 */
#define CONFIG_GET_BOOL(config, key, default_val) \
    ({ \
        config_value* val = config_get(config, key); \
        (val && val->type == CONFIG_BOOLEAN) ? val->data.boolean_val : default_val; \
    })

// XMD processor free function is provided by main XMD API in xmd.h

/**
 * @brief Cleanup XMD processor context (CLI wrapper - duplicate removed)
 * @param handle XMD context handle
 */
// void cli_xmd_cleanup(void* handle); // Already defined above

#ifdef __cplusplus
}
#endif

#endif // CLI_H
