/**
 * @file loop_context_free.c
 * @brief Loop context cleanup function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/loop.h"

/**
 * @brief Free a loop context
 * @param ctx Loop context to free
 */
void loop_context_free(LoopContext* ctx) {
    if (!ctx) {
        return;
    }
    
    free(ctx->last_error);
    free(ctx);
}