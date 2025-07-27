/**
 * @file loop_continue.c
 * @brief Loop continue control function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/loop.h"

/**
 * @brief Request loop continue
 * @param ctx Loop context
 * @return LOOP_CONTINUE
 */
int loop_continue(LoopContext* ctx) {
    if (ctx) {
        ctx->continue_requested = 1;
    }
    return LOOP_CONTINUE;
}