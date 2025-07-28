/**
 * @file sandbox_context_free.c
 * @brief Free a sandbox context
 * @author XMD Team
 */

#include "../../../include/sandbox_internal.h"

/**
 * @brief Free a sandbox context
 * @param ctx Sandbox context to free
 */
void sandbox_context_free(SandboxContext* ctx) {
    if (ctx) {
        if (ctx->config) {
            sandbox_config_free(ctx->config);
        }
        if (ctx->last_error) {
            free(ctx->last_error);
        }
        free(ctx);
    }
}