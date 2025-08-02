/**
 * @file condition_context_new.c
 * @brief Create new condition context
 * 
 * This file contains ONLY the condition_context_new function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/systems_consolidated.c
 */

#include "../../../include/conditional.h"
#include "../../../include/utils.h"
/**
 * @brief Create new condition context
 * @return New condition context or NULL on error
  * /
 */
ConditionContext* condition_context_new(void) {
    ConditionContext* ctx = xmd_malloc(sizeof(ConditionContext));
    if (!ctx) {
        return NULL;
    }
    
    ctx->last_result = false;
    ctx->last_error = NULL;
    return ctx;
}
