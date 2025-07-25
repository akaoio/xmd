/**
 * @file for_loop.c
 * @brief For loop implementation
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/loop.h"
#include "../../../include/conditional.h"

/**
 * @brief Loop context structure
 */
struct loop_context {
    int break_requested;      /**< Break flag */
    int continue_requested;   /**< Continue flag */
    int max_iterations;       /**< Safety limit */
    char* last_error;         /**< Last error message */
};

/**
 * @brief Create a new loop context
 * @return New loop context or NULL on error
 */
LoopContext* loop_context_new(void) {
    LoopContext* ctx = malloc(sizeof(LoopContext));
    if (!ctx) {
        return NULL;
    }
    
    ctx->break_requested = 0;
    ctx->continue_requested = 0;
    ctx->max_iterations = 1000; // Safety limit
    ctx->last_error = NULL;
    
    return ctx;
}

/**
 * @brief Free a loop context
 * @param ctx Loop context to free
 */
void loop_context_free(LoopContext* ctx) {
    if (!ctx) {
        return;
    }
    
    free(ctx->last_error);
    free(ctx);
}

/**
 * @brief Set error message in context
 * @param ctx Loop context
 * @param message Error message
 */
static void set_loop_error(LoopContext* ctx, const char* message) {
    if (!ctx || !message) {
        return;
    }
    
    free(ctx->last_error);
    ctx->last_error = strdup(message);
}

/**
 * @brief Append string to result buffer
 * @param result Current result buffer
 * @param append String to append
 * @return New result buffer (caller must free old buffer)
 */
static char* append_to_result(char* result, const char* append) {
    if (!append) {
        return result;
    }
    
    if (!result) {
        return strdup(append);
    }
    
    size_t result_len = strlen(result);
    size_t append_len = strlen(append);
    char* new_result = realloc(result, result_len + append_len + 1);
    
    if (!new_result) {
        free(result);
        return NULL;
    }
    
    strcpy(new_result + result_len, append);
    return new_result;
}

/**
 * @brief Process a for-in loop
 * @param ctx Loop context
 * @param item_name Name of loop variable
 * @param collection_name Name of collection variable
 * @param template Template content for each iteration
 * @param st Variable store
 * @param result Output result string (caller must free)
 * @return LoopResult indicating success/break/error
 */
int for_loop_process(LoopContext* ctx, const char* item_name, 
                    const char* collection_name, const char* template, 
                    store* st, char** result) {
    if (!ctx || !item_name || !collection_name || !template || !st || !result) {
        return LOOP_ERROR;
    }
    
    *result = NULL;
    ctx->break_requested = 0;
    ctx->continue_requested = 0;
    
    // Get the collection variable
    variable* collection = store_get(st, collection_name);
    if (!collection) {
        set_loop_error(ctx, "Collection not found");
        return LOOP_ERROR;
    }
    
    char* output = strdup("");
    if (!output) {
        return LOOP_ERROR;
    }
    
    // Handle array iteration
    if (variable_get_type(collection) == VAR_ARRAY) {
        size_t length = variable_array_length(collection);
        
        for (size_t i = 0; i < length && i < ctx->max_iterations; i++) {
            if (ctx->break_requested) {
                break;
            }
            
            // Get array element
            variable* item = variable_array_get(collection, i);
            if (!item) {
                continue;
            }
            
            // Set loop variable in store
            store_set(st, item_name, item);
            
            // Process template (simplified - just return template as-is for now)
            output = append_to_result(output, template);
            if (!output) {
                set_loop_error(ctx, "Memory allocation failed");
                return LOOP_ERROR;
            }
            
            if (ctx->continue_requested) {
                ctx->continue_requested = 0;
                continue;
            }
        }
    }
    // Handle object iteration (iterate over keys)
    else if (variable_get_type(collection) == VAR_OBJECT) {
        // For now, simplified object iteration
        // In a full implementation, we'd iterate over object keys
        output = append_to_result(output, template);
        if (!output) {
            set_loop_error(ctx, "Memory allocation failed");
            return LOOP_ERROR;
        }
    }
    // Handle string iteration (iterate over characters)
    else if (variable_get_type(collection) == VAR_STRING) {
        const char* str = variable_get_string(collection);
        if (str) {
            size_t len = strlen(str);
            for (size_t i = 0; i < len && i < ctx->max_iterations; i++) {
                if (ctx->break_requested) {
                    break;
                }
                
                // Create character variable
                char char_str[2] = {str[i], '\0'};
                variable* char_var = variable_create_string(char_str);
                store_set(st, item_name, char_var);
                
                output = append_to_result(output, template);
                if (!output) {
                    variable_unref(char_var);
                    set_loop_error(ctx, "Memory allocation failed");
                    return LOOP_ERROR;
                }
                
                variable_unref(char_var);
                
                if (ctx->continue_requested) {
                    ctx->continue_requested = 0;
                    continue;
                }
            }
        }
    }
    else {
        // Not a collection type
        free(output);
        set_loop_error(ctx, "Variable is not iterable");
        return LOOP_ERROR;
    }
    
    *result = output;
    return ctx->break_requested ? LOOP_BREAK : LOOP_SUCCESS;
}

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
    
    *result = NULL;
    ctx->break_requested = 0;
    ctx->continue_requested = 0;
    
    char* output = strdup("");
    if (!output) {
        return LOOP_ERROR;
    }
    
    // Create condition context for evaluation
    ConditionContext* cond_ctx = condition_context_new();
    if (!cond_ctx) {
        free(output);
        return LOOP_ERROR;
    }
    
    int iterations = 0;
    while (iterations < ctx->max_iterations) {
        if (ctx->break_requested) {
            break;
        }
        
        // Evaluate condition
        int cond_result = condition_evaluate(cond_ctx, condition, st);
        if (cond_result == CONDITION_ERROR) {
            free(output);
            condition_context_free(cond_ctx);
            set_loop_error(ctx, "Condition evaluation failed");
            return LOOP_ERROR;
        }
        
        if (cond_result == CONDITION_FALSE) {
            break; // Exit while loop
        }
        
        // Process template
        output = append_to_result(output, template);
        if (!output) {
            condition_context_free(cond_ctx);
            set_loop_error(ctx, "Memory allocation failed");
            return LOOP_ERROR;
        }
        
        if (ctx->continue_requested) {
            ctx->continue_requested = 0;
            iterations++;
            continue;
        }
        
        iterations++;
    }
    
    condition_context_free(cond_ctx);
    
    if (iterations >= ctx->max_iterations) {
        free(output);
        set_loop_error(ctx, "Maximum iterations exceeded");
        return LOOP_ERROR;
    }
    
    *result = output;
    return ctx->break_requested ? LOOP_BREAK : LOOP_SUCCESS;
}

/**
 * @brief Request loop break
 * @param ctx Loop context
 * @return LOOP_BREAK
 */
int loop_break(LoopContext* ctx) {
    if (!ctx) {
        return LOOP_ERROR;
    }
    
    ctx->break_requested = 1;
    return LOOP_BREAK;
}

/**
 * @brief Request loop continue
 * @param ctx Loop context
 * @return LOOP_CONTINUE
 */
int loop_continue(LoopContext* ctx) {
    if (!ctx) {
        return LOOP_ERROR;
    }
    
    ctx->continue_requested = 1;
    return LOOP_CONTINUE;
}