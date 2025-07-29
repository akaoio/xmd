/**
 * @file c_api.c
 * @brief C API interface for language bindings
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include "../../../include/c_api_internal.h"

// Forward declaration for AST-based XMD processor
extern char* ast_process_xmd_content(const char* input, store* variables);





/**
 * @brief Internal XMD context structure
 */


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
    
    xmd_context_internal* ctx = (xmd_context_internal*)handle;
    if (!ctx->initialized) {
        return c_api_create_result(-1, NULL, "XMD context not initialized");
    }
    
    // Record start time
    clock_t start_time = clock();
    
    // Create variable store for processing
    store* var_store = store_create();
    if (!var_store) {
        return c_api_create_result(-1, NULL, "Failed to create variable store");
    }
    
    // Copy global variables from context to processing store
    if (ctx->global_variables) {
        size_t global_var_count;
        char** global_keys = store_keys(ctx->global_variables, &global_var_count);
        if (global_keys) {
            for (size_t i = 0; i < global_var_count; i++) {
                variable* global_var = store_get(ctx->global_variables, global_keys[i]);
                if (global_var) {
                    // Create a copy of the variable for the processing store
                    const char* var_value = variable_to_string(global_var);
                    if (var_value) {
                        variable* var_copy = variable_create_string(var_value);
                        if (var_copy) {
                            store_set(var_store, global_keys[i], var_copy);
                        }
                    }
                }
            }
            free(global_keys);
        }
    }
    
    // Use AST-based processor to handle all XMD directives
    char* output = ast_process_xmd_content(input, var_store);
    
    // Cleanup
    store_destroy(var_store);
    
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















