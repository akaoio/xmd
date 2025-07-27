/**
 * @file loop_break.c
 * @brief Loop break control function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/loop.h"

/**
 * @brief Request loop break
 * @param ctx Loop context
 * @return LOOP_BREAK
 */
int loop_break(LoopContext* ctx) {
    if (ctx) {
        ctx->break_requested = 1;
    }
    return LOOP_BREAK;
}