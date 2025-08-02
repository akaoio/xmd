/**
 * @file bindings_consolidated.c
 * @brief Consolidated language bindings for XMD
 * @author XMD Development Team
 *
 * All language binding functionality consolidated from 2 directories.
 * Provides complete C API interface for XMD processing functionality.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include "../include/processor_internal.h"
#include "../include/xmd.h"
#include "../include/xmd_processor_internal.h"
#include "../include/cli.h"
#include "../include/store.h"
#include "../include/c_api_internal.h"
#include "../include/utils.h"

// Forward declaration for AST-based XMD processor
extern char* ast_process_xmd_content(const char* input, store* variables);

// ============================================================================
// C API IMPLEMENTATION (FROM bindings/c_api DIRECTORY)
// ============================================================================

/**
 * @brief Process markdown string
 * @param handle XMD context handle
 * @param input Input markdown string
 * @param input_length Input string length
 * @return Processing result (must be freed with xmd_result_free)
 */
xmd_result* xmd_process_string_api(void* handle, const char* input, size_t input_length) {
    if (!handle || !input) {
        return NULL; // Return NULL for invalid parameters
    }
    
    xmd_processor* processor = (xmd_processor*)handle;
    if (!processor->initialized) {
        return c_api_create_result(-1, NULL, "Processor not initialized");
    }
    
    // Record start time
    clock_t start_time = clock();
    
    // Use processor->variables instead of creating new store
    // This ensures variables persist between directives
    char* output = ast_process_xmd_content(input, processor->variables);
    
    // Don't destroy processor->variables! It needs to persist
    
    // Calculate processing time
    clock_t end_time = clock();
    double processing_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000.0;
    
    xmd_result* result = c_api_create_result(0, output, NULL);
    if (result) {
        result->processing_time_ms = processing_time;
    }
    
    free(output);
    return result;
}

// ============================================================================
// CONSOLIDATED C API BINDINGS
// ============================================================================

// XMD Initialization
void* c_api_xmd_init(const char* config_path) {
    xmd_context_internal* ctx = xmd_calloc(1, sizeof(xmd_context_internal));
    if (!ctx) return NULL;
    
    ctx->config = config_create();
    if (!ctx->config) { free(ctx); return NULL; }
    
    if (config_path && config_load_file(ctx->config, config_path) != 0) {
        config_destroy(ctx->config); free(ctx); return NULL;
    }
    config_load_env(ctx->config);
    
    ctx->global_variables = store_create();
    if (!ctx->global_variables) { config_destroy(ctx->config); free(ctx); return NULL; }
    
    ctx->initialized = true;
    return ctx;
}

xmd_error_code xmd_init(void) { return XMD_SUCCESS; }

// XMD Cleanup
void c_api_xmd_cleanup(void* handle) {
    if (!handle) return;
    xmd_context_internal* ctx = (xmd_context_internal*)handle;
    if (ctx->config) config_destroy(ctx->config);
    if (ctx->global_variables) store_destroy(ctx->global_variables);
    free(ctx);
}

// Configuration Management
xmd_config* xmd_config_create_default(void) { return config_create(); }
void xmd_config_free(xmd_config* config) { if (config) config_destroy(config); }

// Variable Management  
xmd_error_code xmd_set_variable(xmd_processor* processor, const char* key, const char* value) {
    if (!processor || !key || !value) return XMD_ERROR_INVALID_ARGUMENT;
    store* variables = (store*)processor;
    variable* var = variable_create_string(value);
    if (!var) return XMD_ERROR_OUT_OF_MEMORY;
    store_set(variables, key, var);
    return XMD_SUCCESS;
}

char* xmd_get_variable(xmd_processor* processor, const char* key) {
    if (!processor || !key) return NULL;
    store* variables = (store*)processor;
    variable* var = store_get(variables, key);
    return var ? variable_to_string(var) : NULL;
}

// Processor Management - REAL implementation per Genesis NO STUBS directive
xmd_processor* xmd_processor_create(const xmd_config* config) {
    xmd_processor* processor = xmd_calloc(1, sizeof(xmd_processor));
    if (!processor) return NULL;
    
    // Initialize variable store
    processor->variables = store_create();
    if (!processor->variables) {
        free(processor);
        return NULL;
    }
    
    // Copy config (don't just reference)
    if (config) {
        processor->config = xmd_malloc(sizeof(xmd_config));
        if (processor->config) {
            memcpy(processor->config, config, sizeof(xmd_config));
        }
    }
    
    // Initialize other stores with NULL checks
    processor->modules = store_create();
    if (!processor->modules) {
        store_destroy(processor->variables);
        free(processor->config);
        free(processor);
        return NULL;
    }
    
    processor->functions = store_create();
    if (!processor->functions) {
        store_destroy(processor->variables);
        store_destroy(processor->modules);
        free(processor->config);
        free(processor);
        return NULL;
    }
    
    processor->exports = store_create();
    if (!processor->exports) {
        store_destroy(processor->variables);
        store_destroy(processor->modules);
        store_destroy(processor->functions);
        free(processor->config);
        free(processor);
        return NULL;
    }
    
    processor->initialized = true;
    processor->current_file = NULL; // Initialize to NULL for safe free()
    
    return processor;
}

void xmd_processor_free(xmd_processor* processor) {
    if (!processor) return;
    
    printf("DEBUG: xmd_processor_free starting\n");
    fflush(stdout);
    
    // Safely destroy stores with NULL checks
    if (processor->variables) {
        printf("DEBUG: About to destroy variables store\n");
        fflush(stdout);
        store_destroy(processor->variables);
        printf("DEBUG: Variables store destroyed\n");
        fflush(stdout);
    }
    if (processor->modules) {
        printf("DEBUG: About to destroy modules store\n");
        fflush(stdout);
        store_destroy(processor->modules);
        printf("DEBUG: Modules store destroyed\n");
        fflush(stdout);
    }
    if (processor->functions) {
        printf("DEBUG: About to destroy functions store\n");
        fflush(stdout);
        store_destroy(processor->functions);
        printf("DEBUG: Functions store destroyed\n");
        fflush(stdout);
    }
    if (processor->exports) {
        printf("DEBUG: About to destroy exports store\n");
        fflush(stdout);
        store_destroy(processor->exports);
        printf("DEBUG: Exports store destroyed\n");
        fflush(stdout);
    }
    
    if (processor->config) {
        printf("DEBUG: About to free config\n");
        fflush(stdout);
        // processor->config is just a malloc'd copy, not a full config structure
        free(processor->config);
        printf("DEBUG: Config freed\n");
        fflush(stdout);
    }
    
    if (processor->current_file) {
        printf("DEBUG: About to free current_file\n");
        fflush(stdout);
        free(processor->current_file);
        printf("DEBUG: Current_file freed\n");
        fflush(stdout);
    }
    
    printf("DEBUG: About to free processor\n");
    fflush(stdout);
    free(processor);
    printf("DEBUG: xmd_processor_free completed\n");
    fflush(stdout);
}

// String Processing (consolidated from xmd_process_string subdirectory)
xmd_result* c_api_xmd_process_string(void* handle, const char* input, size_t input_length) {
    if (!handle || !input || input_length == 0) {
        return NULL;
    }
    
    // Use the main API function
    return xmd_process_string_api(handle, input, input_length);
}

// File Processing
xmd_result* xmd_process_file(xmd_processor* processor, const char* filename) {
    if (!processor || !filename) {
        return c_api_create_result(-1, NULL, "Invalid processor or filename");
    }
    
    // Read file content
    FILE* file = fopen(filename, "r");
    if (!file) {
        char error_msg[256];
        snprintf(error_msg, sizeof(error_msg), "Cannot open file: %s", filename);
        return c_api_create_result(-1, NULL, error_msg);
    }
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char* content = xmd_malloc(size + 1);
    if (!content) {
        fclose(file);
        return c_api_create_result(-1, NULL, "Memory allocation failed");
    }
    
    fread(content, 1, size, file);
    content[size] = '\0';
    fclose(file);
    
    // Process content using existing function
    xmd_result* result = xmd_process_string(processor, content, size);
    free(content);
    
    return result;
}

// String Processing  
xmd_result* xmd_process_string(xmd_processor* processor, const char* input, size_t input_length) {
    if (!processor || !input) {
        return c_api_create_result(-1, NULL, "Invalid processor or input");
    }
    
    // Use the API function with proper processor
    return xmd_process_string_api(processor, input, input_length);
}

// Result Management
void xmd_result_free(xmd_result* result) {
    if (!result) return;
    free(result->output);
    free(result->error_message);
    free(result);
}

// Version Information
const char* xmd_get_version(void) { return "2.0.0-consolidation"; }

// ============================================================================
// BINDING UTILITIES
// ============================================================================

/**
 * @brief Validate C API parameters
 * @param handle Context handle
 * @param input Input string
 * @param input_length Input length
 * @return true if valid, false otherwise
 */
bool c_api_validate_params(void* handle, const char* input, size_t input_length) {
    return handle != NULL && input != NULL && input_length > 0;
}

/**
 * @brief Create result structure helper
 * @param error_code Error code
 * @param output Output string (will be copied)
 * @param error_message Error message (will be copied)
 * @return New result structure or NULL on error
 */
xmd_result* c_api_create_result(int error_code, const char* output, const char* error_message) {
    xmd_result* result = xmd_malloc(sizeof(xmd_result));
    if (!result) {
        return NULL;
    }
    
    result->error_code = error_code;
    result->processing_time_ms = 0.0;
    
    // Copy output string
    if (output) {
        result->output = xmd_malloc(strlen(output) + 1);
        if (result->output) {
            strcpy(result->output, output);
        } else {
            free(result);
            return NULL;
        }
    } else {
        result->output = NULL;
    }
    
    // Copy error message
    if (error_message) {
        result->error_message = xmd_malloc(strlen(error_message) + 1);
        if (result->error_message) {
            strcpy(result->error_message, error_message);
        } else {
            free(result->output);
            free(result);
            return NULL;
        }
    } else {
        result->error_message = NULL;
    }
    
    return result;
}

/**
 * @brief Get bindings version information
 * @return Version string
 */
const char* bindings_get_version(void) {
    return "XMD Language Bindings v2.0 (consolidated)";
}

// ============================================================================  
// MISSING CORE XMD PROCESSOR FUNCTIONS (REAL IMPLEMENTATIONS)
// ============================================================================

// ast_process_xmd_content is already implemented in native_xmd_consolidated.c
