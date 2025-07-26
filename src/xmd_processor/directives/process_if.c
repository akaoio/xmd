/**
 * @file process_if.c
 * @brief Process if directive implementation
 * @author XMD Team
 * @date 2025-07-26
 */

#include "../../../include/xmd_processor_internal.h"

/**
 * @brief Process if directive with enhanced logic
 * @param args Condition arguments for if directive
 * @param ctx Processor context
 * @param output Buffer to store output (unused for if)
 * @param output_size Size of output buffer
 * @return 0 on success, -1 on error
 */
int process_if(const char* args, processor_context* ctx, char* output, size_t output_size) {
    if (ctx->if_stack_size >= MAX_IF_DEPTH - 1) {
        snprintf(output, output_size, "[Error: If nesting too deep]");
        return -1;
    }
    
    bool condition_result = evaluate_condition(args, ctx->variables);
    
    if_stack_entry* entry = &ctx->if_stack[ctx->if_stack_size];
    entry->condition_met = condition_result;
    entry->branch_executed = condition_result;
    entry->in_elif = false;
    
    ctx->if_stack_size++;
    output[0] = '\0';
    return 0;
}
