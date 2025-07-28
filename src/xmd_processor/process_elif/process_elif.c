/**
 * @file process_elif.c
 * @brief Process elif directive implementation
 * @author XMD Team
 * @date 2025-07-26
 */

#include "../../../include/xmd_processor_internal.h"
#include "../../../include/ast_evaluator.h"

/**
 * @brief Process elif directive
 * @param args Condition arguments for elif directive
 * @param ctx Processor context
 * @param output Buffer to store output (unused for elif)
 * @param output_size Size of output buffer
 * @return 0 on success, -1 on error
 */
int process_elif(const char* args, processor_context* ctx, char* output, size_t output_size) {
    if (ctx->if_stack_size == 0) {
        snprintf(output, output_size, "[Error: elif without if]");
        return -1;
    }
    
    if_stack_entry* entry = &ctx->if_stack[ctx->if_stack_size - 1];
    
    // Only evaluate elif if no previous branch was executed
    if (!entry->branch_executed) {
        bool condition_result = ast_evaluate_condition(args, ctx->variables);
        entry->condition_met = condition_result;
        if (condition_result) {
            entry->branch_executed = true;
        }
    } else {
        entry->condition_met = false;
    }
    
    entry->in_elif = true;
    output[0] = '\0';
    return 0;
}
