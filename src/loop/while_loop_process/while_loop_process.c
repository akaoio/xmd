/**
 * @file while_loop_process.c
 * @brief While loop processing function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/loop.h"
#include "../../../include/conditional.h"
#include "../../../include/store.h"

/**
 * @brief Process a while loop
 * @param ctx Loop context
 * @param condition Condition to evaluate each iteration
 * @param template Template content for each iteration
 * @param st Variable store
 * @param result Output result string (caller must free)
 * @return LoopResult indicating success/break/error
 */
int while_loop_process(LoopContext* ctx, const char* condition, 
                      const char* template, store* st, char** result) {
    if (!ctx || !condition || !template || !st || !result) {
        return LOOP_ERROR;
    }
    
    *result = malloc(1);
    if (!*result) {
        return LOOP_ERROR;
    }
    (*result)[0] = '\0';
    
    // Create condition context for evaluation
    ConditionContext* cond_ctx = condition_context_new();
    if (!cond_ctx) {
        free(*result);
        *result = NULL;
        return LOOP_ERROR;
    }
    
    size_t iterations = 0;
    while (iterations < ctx->max_iterations) {
        
        // Evaluate condition
        int cond_result = condition_evaluate(cond_ctx, condition, st);
        if (cond_result == CONDITION_ERROR) {
            break;
        }
        if (cond_result == CONDITION_FALSE) {
            break;
        }
        
        if (ctx->break_requested) {
            break;
        }
        
        if (ctx->continue_requested) {
            ctx->continue_requested = 0;
            iterations++;
            continue;
        }
        
        // For now, just append the template as-is
        // In a full implementation, this would process the template
        char* new_result = append_to_result(*result, template);
        if (!new_result) {
            condition_context_free(cond_ctx);
            free(*result);
            *result = NULL;
            return LOOP_ERROR;
        }
        
        free(*result);
        *result = new_result;
        iterations++;
    }
    
    condition_context_free(cond_ctx);
    return LOOP_SUCCESS;
}