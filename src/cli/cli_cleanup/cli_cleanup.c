/**
 * @file cli_cleanup.c
 * @brief CLI context cleanup function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/cli.h"

/**
 * @brief Cleanup CLI context
 * @param ctx CLI context
 */
void cli_cleanup(cli_context* ctx) {
    if (!ctx) {
        return;
    }
    
    if (ctx->args) {
        free(ctx->args->input_file);
        free(ctx->args->output_file);
        free(ctx->args->config_file);
        free(ctx->args->watch_directory);
        free(ctx->args);
    }
    
    free(ctx->program_name);
    
    // Cleanup XMD context if initialized
    if (ctx->xmd) {
        // Free the XMD context (xmd_cleanup() is global)
        free(ctx->xmd);
        ctx->xmd = NULL;
    }
    
    free(ctx);
}