/**
 * @file condition_context_free.c
 * @brief Free condition context
 * 
 * This file contains ONLY the condition_context_free function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/systems_consolidated.c (with syntax fixes)
 */

#include <stdlib.h>
#include "../../../include/conditional.h"
#include "../../utils/common/common_macros.h"
/**
 * @brief Free condition context
 * @param ctx Context to free
 */
void condition_context_free(ConditionContext* ctx) {
    XMD_ENTRY_VALIDATE_VOID(ctx);
    XMD_FREE_SAFE(ctx->last_error);
    XMD_FREE_SAFE(ctx);
}
