/**
 * @file flow_control.c
 * @brief Flow control function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include "../../../include/flow.h"

/**
 * @brief Check current flow status
 * @param ctx Flow context
 * @return Current FlowResult status
 */
int flow_check_status(FlowContext* ctx) {
    if (!ctx) {
        return FLOW_ERROR;
    }
    
    return ctx->status;
}
