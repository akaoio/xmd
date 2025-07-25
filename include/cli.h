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
    CLI_CMD_VERSION = 5     ///< Show version
} cli_command_type;

/**
 * @brief CLI argument structure
 */
typedef struct cli_args {
    cli_command_type command;
    char* input_file;
    char* output_file;
    char* config_file;
    char* watch_directory;
    bool verbose;
    bool quiet;
    bool debug;
    bool version;
    bool help;
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

/**
 * @brief Configuration structure
 */
typedef struct xmd_config {
    char* config_file_path;
    config_value* values;
    size_t value_count;
    bool loaded;
} xmd_config;


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
 * @brief C API result structure
 */
typedef struct xmd_result {
    int error_code;
    char* output;
    char* error_message;
    size_t output_length;
    double processing_time_ms;
} xmd_result;

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

/**
 * @brief Initialize XMD processor
 * @param config_path Path to configuration file (optional)
 * @return XMD context handle or NULL on error
 */
void* xmd_init(const char* config_path);

/**
 * @brief Process markdown string
 * @param handle XMD context handle
 * @param input Input markdown string
 * @param input_length Input string length
 * @return Processing result (must be freed with xmd_result_free)
 */
xmd_result* xmd_process_string(void* handle, const char* input, size_t input_length);

/**
 * @brief Process markdown file
 * @param handle XMD context handle
 * @param input_path Input file path
 * @param output_path Output file path (optional)
 * @return Processing result (must be freed with xmd_result_free)
 */
xmd_result* xmd_process_file(void* handle, const char* input_path, const char* output_path);

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

/**
 * @brief Cleanup XMD processor
 * @param handle XMD context handle
 */
void xmd_cleanup(void* handle);

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

#ifdef __cplusplus
}
#endif

#endif // CLI_H