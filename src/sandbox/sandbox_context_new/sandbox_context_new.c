/**
 * @file sandbox_context_new.c
 * @brief Create a new sandbox context
 * @author XMD Team
 */

#include "../../../include/sandbox_internal.h"

/**
 * @brief Create a new sandbox context
 * @param config Sandbox configuration
 * @return New sandbox context or NULL on error
 */
SandboxContext* sandbox_context_new(SandboxConfig* config) {
    if (!config) return NULL;
    
    SandboxContext* ctx = malloc(sizeof(SandboxContext));
    if (!ctx) return NULL;
    
    ctx->config = config;
    return ctx;
}