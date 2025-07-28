/**
 * @file create_context.c
 * @brief Create processor context implementation
 * @author XMD Team
 * @date 2025-07-26
 */

#define _GNU_SOURCE
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
    
    // Initialize sandbox with default security configuration
    SandboxConfig* sandbox_config = sandbox_config_new();
    if (sandbox_config) {
        // Add dangerous commands to blacklist
        sandbox_config_add_blacklist(sandbox_config, "rm");
        sandbox_config_add_blacklist(sandbox_config, "rmdir");
        sandbox_config_add_blacklist(sandbox_config, "dd");
        sandbox_config_add_blacklist(sandbox_config, "mkfs");
        sandbox_config_add_blacklist(sandbox_config, "fdisk");
        sandbox_config_add_blacklist(sandbox_config, "format");
        sandbox_config_add_blacklist(sandbox_config, "shutdown");
        sandbox_config_add_blacklist(sandbox_config, "reboot");
        sandbox_config_add_blacklist(sandbox_config, "init");
        sandbox_config_add_blacklist(sandbox_config, "halt");
        sandbox_config_add_blacklist(sandbox_config, "poweroff");
        sandbox_config_add_blacklist(sandbox_config, "su");
        sandbox_config_add_blacklist(sandbox_config, "sudo");
        sandbox_config_add_blacklist(sandbox_config, "chmod");
        sandbox_config_add_blacklist(sandbox_config, "curl");
        sandbox_config_add_blacklist(sandbox_config, "wget");
        sandbox_config_add_blacklist(sandbox_config, "nc");
        sandbox_config_add_blacklist(sandbox_config, "netcat");
        sandbox_config_add_blacklist(sandbox_config, "ncat");
        
        ctx->sandbox_ctx = sandbox_context_new(sandbox_config);
    } else {
        ctx->sandbox_ctx = NULL;
    }
    
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
    
    // Destroy sandbox context if allocated
    if (ctx->sandbox_ctx) {
        sandbox_context_free(ctx->sandbox_ctx);
    }
    
    // Free the context itself
    free(ctx);
}
