/**
 * @file condition_context_new.c
 * @brief Create new condition context
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/conditional.h"

/**
 * @brief Create a new condition context
 * @return New condition context or NULL on error
 */
ConditionContext* condition_context_new(void) {
    ConditionContext* ctx = malloc(sizeof(ConditionContext));
    if (!ctx) {
        return NULL;
    }
    
    ctx->last_result = false;
    ctx->last_error = NULL;
    
    return ctx;
}