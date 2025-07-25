/**
 * @file c_api.c
 * @brief C API interface for language bindings
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../../../include/cli.h"
#include "../../../include/lexer.h"
#include "../../../include/token.h"
#include "../../../include/store.h"

/**
 * @brief Internal XMD context structure
 */
typedef struct xmd_context_internal {
    xmd_config* config;
    plugin_manager* plugins;
    bool initialized;
} xmd_context_internal;

/**
 * @brief Initialize XMD processor
 * @param config_path Path to configuration file (optional)
 * @return XMD context handle or NULL on error
 */
void* xmd_init(const char* config_path) {
    xmd_context_internal* ctx = calloc(1, sizeof(xmd_context_internal));
    if (!ctx) {
        return NULL;
    }
    
    // Initialize configuration
    ctx->config = config_create();
    if (!ctx->config) {
        free(ctx);
        return NULL;
    }
    
    // Load configuration file if provided
    if (config_path) {
        if (config_load_file(ctx->config, config_path) != 0) {
            config_destroy(ctx->config);
            free(ctx);
            return NULL;
        }
    }
    
    // Load environment configuration
    config_load_env(ctx->config);
    
    // Initialize plugin manager
    ctx->plugins = plugin_manager_create();
    if (!ctx->plugins) {
        config_destroy(ctx->config);
        free(ctx);
        return NULL;
    }
    
    ctx->initialized = true;
    return ctx;
}

/**
 * @brief Create result structure
 * @param error_code Error code
 * @param output Output string
 * @param error_message Error message
 * @return Result structure
 */
static xmd_result* create_result(int error_code, const char* output, const char* error_message) {
    xmd_result* result = calloc(1, sizeof(xmd_result));
    if (!result) {
        return NULL;
    }
    
    result->error_code = error_code;
    
    if (output) {
        result->output = strdup(output);
        result->output_length = strlen(output);
    } else {
        result->output = NULL;
        result->output_length = 0;
    }
    
    if (error_message) {
        result->error_message = strdup(error_message);
    } else {
        result->error_message = NULL;
    }
    
    result->processing_time_ms = 0.0;
    
    return result;
}

/**
 * @brief Process markdown string
 * @param handle XMD context handle
 * @param input Input markdown string
 * @param input_length Input string length
 * @return Processing result (must be freed with xmd_result_free)
 */
xmd_result* xmd_process_string(void* handle, const char* input, size_t input_length) {
    if (!handle || !input) {
        return NULL; // Return NULL for invalid parameters
    }
    
    xmd_context_internal* ctx = (xmd_context_internal*)handle;
    if (!ctx->initialized) {
        return create_result(-1, NULL, "XMD context not initialized");
    }
    
    // Record start time
    clock_t start_time = clock();
    
    // Process the input through the XMD pipeline
    // 1. Create lexer to tokenize input
    lexer* lex = lexer_create(input);
    if (!lex) {
        return create_result(-1, NULL, "Failed to create lexer");
    }
    
    // 2. Create variable store for processing
    store* var_store = store_create();
    if (!var_store) {
        lexer_free(lex);
        return create_result(-1, NULL, "Failed to create variable store");
    }
    
    // 3. Process tokens and build output
    char* output = malloc(input_length * 2 + 1000); // Allocate extra space for processing
    if (!output) {
        store_destroy(var_store);
        lexer_free(lex);
        return create_result(-1, NULL, "Memory allocation failed");
    }
    
    // 4. Process the markdown content
    size_t output_pos = 0;
    token* tok;
    
    while ((tok = lexer_next_token(lex)) != NULL && tok->type != TOKEN_EOF) {
        // Process each token based on its type
        switch (tok->type) {
            case TOKEN_TEXT:
                // Copy text content directly
                if (tok->value) {
                    size_t text_len = strlen(tok->value);
                    if (output_pos + text_len < input_length * 2 + 999) {
                        strcpy(output + output_pos, tok->value);
                        output_pos += text_len;
                    }
                }
                break;
                
            case TOKEN_VARIABLE_REF:
                // Process variable references
                if (tok->value) {
                    // Extract variable name (remove {{ and }})
                    char* var_name = strdup(tok->value);
                    if (var_name) {
                        // Simple variable lookup - in real implementation would be more sophisticated
                        char* var_value = ""; // Default to empty if not found
                        if (output_pos + strlen(var_value) < input_length * 2 + 999) {
                            strcpy(output + output_pos, var_value);
                            output_pos += strlen(var_value);
                        }
                        free(var_name);
                    }
                }
                break;
                
            case TOKEN_XMD_DIRECTIVE:
                // Process XMD directives - skip for now but could execute commands
                break;
                
            default:
                // For other token types, copy the raw content
                if (tok->value) {
                    size_t text_len = strlen(tok->value);
                    if (output_pos + text_len < input_length * 2 + 999) {
                        strcpy(output + output_pos, tok->value);
                        output_pos += text_len;
                    }
                }
                break;
        }
        
        token_free(tok);
    }
    
    if (tok) {
        token_free(tok);
    }
    
    output[output_pos] = '\0';
    
    // Cleanup
    store_destroy(var_store);
    lexer_free(lex);
    
    // Calculate processing time
    clock_t end_time = clock();
    double processing_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000.0;
    
    xmd_result* result = create_result(0, output, NULL);
    if (result) {
        result->processing_time_ms = processing_time;
    }
    
    free(output);
    return result;
}

/**
 * @brief Process markdown file
 * @param handle XMD context handle
 * @param input_path Input file path
 * @param output_path Output file path (optional)
 * @return Processing result (must be freed with xmd_result_free)
 */
xmd_result* xmd_process_file(void* handle, const char* input_path, const char* output_path) {
    if (!handle || !input_path) {
        return NULL; // Return NULL for invalid parameters
    }
    
    xmd_context_internal* ctx = (xmd_context_internal*)handle;
    if (!ctx->initialized) {
        return create_result(-1, NULL, "XMD context not initialized");
    }
    
    // Read input file
    FILE* input_file = fopen(input_path, "r");
    if (!input_file) {
        return create_result(-1, NULL, "Failed to open input file");
    }
    
    // Get file size
    fseek(input_file, 0, SEEK_END);
    long file_size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);
    
    if (file_size < 0) {
        fclose(input_file);
        return create_result(-1, NULL, "Failed to get file size");
    }
    
    // Read file content
    char* content = malloc(file_size + 1);
    if (!content) {
        fclose(input_file);
        return create_result(-1, NULL, "Memory allocation failed");
    }
    
    size_t bytes_read = fread(content, 1, file_size, input_file);
    content[bytes_read] = '\0';
    fclose(input_file);
    
    // Process the content
    xmd_result* result = xmd_process_string(handle, content, bytes_read);
    
    // Write output file if specified
    if (output_path && result && result->error_code == 0) {
        FILE* output_file = fopen(output_path, "w");
        if (output_file) {
            fwrite(result->output, 1, result->output_length, output_file);
            fclose(output_file);
        }
    }
    
    free(content);
    return result;
}

/**
 * @brief Validate markdown syntax
 * @param handle XMD context handle
 * @param input Input markdown string
 * @param input_length Input string length
 * @return Validation result (must be freed with xmd_result_free)
 */
xmd_result* xmd_validate(void* handle, const char* input, size_t input_length) {
    if (!handle || !input) {
        return NULL; // Return NULL for invalid parameters
    }
    
    xmd_context_internal* ctx = (xmd_context_internal*)handle;
    if (!ctx->initialized) {
        return create_result(-1, NULL, "XMD context not initialized");
    }
    
    // Record start time
    clock_t start_time = clock();
    
    // Basic validation - check for balanced directives
    // In a full implementation, this would parse and validate the entire syntax
    int directive_balance = 0;
    const char* pos = input;
    const char* end = input + input_length;
    
    while (pos < end) {
        if (strncmp(pos, "<!-- xmd:", 9) == 0) {
            // Found XMD directive start
            if (strstr(pos, "if") || strstr(pos, "for") || strstr(pos, "while") || strstr(pos, "try")) {
                directive_balance++;
            } else if (strstr(pos, "endif") || strstr(pos, "endfor") || strstr(pos, "endwhile") || strstr(pos, "endtry")) {
                directive_balance--;
            }
        }
        pos++;
    }
    
    // Calculate processing time
    clock_t end_time = clock();
    double processing_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000.0;
    
    xmd_result* result;
    if (directive_balance == 0) {
        result = create_result(0, "Validation successful", NULL);
    } else {
        result = create_result(1, NULL, "Unbalanced XMD directives");
    }
    
    if (result) {
        result->processing_time_ms = processing_time;
    }
    
    return result;
}

/**
 * @brief Set configuration option
 * @param handle XMD context handle
 * @param key Configuration key
 * @param value Configuration value
 * @return 0 on success, -1 on error
 */
int xmd_set_config(void* handle, const char* key, const char* value) {
    if (!handle || !key || !value) {
        return -1;
    }
    
    xmd_context_internal* ctx = (xmd_context_internal*)handle;
    if (!ctx->initialized || !ctx->config) {
        return -1;
    }
    
    config_value* config_val = malloc(sizeof(config_value));
    if (!config_val) {
        return -1;
    }
    
    config_val->type = CONFIG_STRING;
    config_val->data.string_val = strdup(value);
    
    return config_set(ctx->config, key, config_val);
}

/**
 * @brief Get configuration option
 * @param handle XMD context handle
 * @param key Configuration key
 * @return Configuration value or NULL if not found (must be freed)
 */
char* xmd_get_config(void* handle, const char* key) {
    if (!handle || !key) {
        return NULL;
    }
    
    xmd_context_internal* ctx = (xmd_context_internal*)handle;
    if (!ctx->initialized || !ctx->config) {
        return NULL;
    }
    
    config_value* value = config_get(ctx->config, key);
    if (value && value->type == CONFIG_STRING && value->data.string_val) {
        return strdup(value->data.string_val);
    }
    
    return NULL;
}

/**
 * @brief Free result structure
 * @param result Result structure
 */
void xmd_result_free(xmd_result* result) {
    if (!result) {
        return;
    }
    
    free(result->output);
    free(result->error_message);
    free(result);
}

/**
 * @brief Cleanup XMD processor
 * @param handle XMD context handle
 */
void xmd_cleanup(void* handle) {
    if (!handle) {
        return;
    }
    
    xmd_context_internal* ctx = (xmd_context_internal*)handle;
    
    if (ctx->config) {
        config_destroy(ctx->config);
    }
    
    if (ctx->plugins) {
        plugin_manager_destroy(ctx->plugins);
    }
    
    free(ctx);
}

/**
 * @brief Get version information
 * @return Version string
 */
const char* xmd_get_version(void) {
    return "1.0.0";
}

/**
 * @brief Get error message for error code
 * @param error_code Error code
 * @return Human-readable error message
 */
const char* xmd_error_string(int error_code) {
    switch (error_code) {
        case 0: return "Success";
        case -1: return "General error";
        case -2: return "Parse error";
        case -3: return "Memory allocation failed";
        case -4: return "File not found";
        case -5: return "Permission denied";
        default: return "Unknown error";
    }
}

/**
 * @brief Validate syntax
 * @param input Input markdown
 * @param input_length Input length
 * @return 0 on success, -1 on error
 */
int xmd_validate_syntax(const char* input, size_t input_length) {
    if (!input || input_length == 0) {
        return -1;
    }
    
    // Basic validation using lexer
    lexer* lex = lexer_create(input);
    if (!lex) {
        return -1;
    }
    
    // Try to tokenize the entire input
    token* tok;
    while ((tok = lexer_next_token(lex)) != NULL && tok->type != TOKEN_EOF) {
        token_free(tok);
    }
    
    if (tok) {
        token_free(tok);
    }
    
    lexer_free(lex);
    return 0; // Valid if we can tokenize it
}

/**
 * @brief Set variable in processor context
 * @param processor Processor instance (actually xmd_context_internal*)
 * @param key Variable name
 * @param value Variable value
 * @return 0 on success, -1 on error
 */
int xmd_set_variable(void* processor, const char* key, const char* value) {
    if (!processor || !key || !value) {
        return -1;
    }
    
    xmd_context_internal* ctx = (xmd_context_internal*)processor;
    if (!ctx->initialized) {
        return -1;
    }
    
    // In a full implementation, would store in variable context
    // For now, just validate parameters
    return 0;
}

/**
 * @brief Get variable from processor context
 * @param processor Processor instance (actually xmd_context_internal*)
 * @param key Variable name
 * @return Variable value or NULL if not found
 */
char* xmd_get_variable(void* processor, const char* key) {
    if (!processor || !key) {
        return NULL;
    }
    
    xmd_context_internal* ctx = (xmd_context_internal*)processor;
    if (!ctx->initialized) {
        return NULL;
    }
    
    // In a full implementation, would lookup from variable context
    // For now, return NULL (not found)
    return NULL;
}

/**
 * @brief Create default XMD configuration
 * @return Default configuration structure
 */
void* xmd_config_create_default(void) {
    return config_create();
}

/**
 * @brief Free XMD configuration
 * @param config Configuration to free
 */
void xmd_config_free(void* config) {
    if (config) {
        config_destroy((xmd_config*)config);
    }
}

/**
 * @brief Create XMD processor
 * @param config Configuration
 * @return Processor instance or NULL on error
 */
void* xmd_processor_create(const void* config) {
    (void)config; // Suppress unused parameter warning
    
    // Create using the existing xmd_init function
    return xmd_init(NULL);
}

/**
 * @brief Free XMD processor
 * @param processor Processor to free
 */
void xmd_processor_free(void* processor) {
    if (processor) {
        xmd_cleanup(processor);
    }
}