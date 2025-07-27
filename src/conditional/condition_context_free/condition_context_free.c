/**
 * @file condition_context_free.c
 * @brief Free condition context
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/conditional.h"

/**
 * @brief Free a condition context
 * @param ctx Condition context to free
 */
void condition_context_free(ConditionContext* ctx) {
    if (!ctx) {
        return;
    }
    
    free(ctx->last_error);
    free(ctx);
}