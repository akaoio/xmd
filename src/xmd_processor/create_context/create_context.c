/**
 * @file create_context.c
 * @brief Create processor context implementation
 * @author XMD Team
 * @date 2025-07-26
 */

#include "../../../include/xmd_processor_internal.h"

/**
 * @brief Create processor context
 * @param variables Variable store to associate with context
 * @return New processor context (caller must free) or NULL on error
 */
processor_context* create_context(store* variables) {
    processor_context* ctx = malloc(sizeof(processor_context));
    if (!ctx) return NULL;
    
    ctx->variables = variables;
    ctx->if_stack_size = 0;
    ctx->loop_depth = 0;
    ctx->total_iterations = 0;
    ctx->currently_executing = true;
    ctx->source_file_path = NULL;
    return ctx;
}

/**
 * @brief Set source file path in processor context
 * @param ctx Processor context
 * @param file_path Path to source file being processed
 */
void set_context_source_file(processor_context* ctx, const char* file_path) {
    if (!ctx) return;
    
    // Free existing path if any
    if (ctx->source_file_path) {
        free(ctx->source_file_path);
    }
    
    // Set new path
    ctx->source_file_path = file_path ? strdup(file_path) : NULL;
}

/**
 * @brief Destroy processor context and free memory
 * @param ctx Processor context to destroy (can be NULL)
 */
void destroy_context(processor_context* ctx) {
    if (!ctx) return;
    
    // Free source file path if allocated
    if (ctx->source_file_path) {
        free(ctx->source_file_path);
    }
    
    // Free the context itself
    free(ctx);
}
