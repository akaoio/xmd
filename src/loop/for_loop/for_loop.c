#define _GNU_SOURCE  // For strdup - must be before includes

/**
 * @file for_loop.c
 * @brief For loop implementation
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/loop.h"
#include "../../../include/conditional.h"

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
            
            // Process template with current loop variable
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
        // Object iteration - iterate over object properties
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
