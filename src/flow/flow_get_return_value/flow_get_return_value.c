/**
 * @file flow_get_return_value.c
 * @brief Get return value from flow context
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/flow.h"

/**
 * @brief Get the return value from flow context
 * @param ctx Flow context
 * @return Return value or NULL if no return value
 */
variable* flow_get_return_value(FlowContext* ctx) {
    if (!ctx) {
        return NULL;
    }
    
    return ctx->return_value;
}