/**
 * @file if_statement.c
 * @brief If statement implementation
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/conditional.h"
#include "../../../include/template.h"

/**
 * @brief Process an if/else statement
 * @param ctx Conditional context
 * @param condition Condition to evaluate
 * @param true_content Content to return if condition is true
 * @param false_content Content to return if condition is false (can be NULL)
 * @param store Variable store for lookups
 * @param result Output result string (caller must free)
 * @return 0 on success, non-zero on error
 */
int if_statement_process(ConditionContext* ctx, const char* condition, 
                        const char* true_content, const char* false_content, 
                        store* st, char** result) {
    if (!ctx || !condition || !true_content || !result || !st) {
        return -1;
    }
    
    *result = NULL;
    
    // Evaluate the condition
    int condition_result = condition_evaluate(ctx, condition, st);
    
    if (condition_result == CONDITION_ERROR) {
        return -1;
    }
    
    // Choose content based on condition result
    const char* chosen_content = NULL;
    if (condition_result == CONDITION_TRUE) {
        chosen_content = true_content;
    } else if (false_content) {
        chosen_content = false_content;
    } else {
        // No else branch, return empty string
        *result = strdup("");
        return *result ? 0 : -1;
    }
    
    // For now, just return the content as-is (template processing can be added later)
    *result = strdup(chosen_content);
    return *result ? 0 : -1;
}

/**
 * @brief Process an elif (else if) chain
 * @param ctx Conditional context
 * @param conditions Array of conditions to evaluate
 * @param contents Array of content strings corresponding to conditions
 * @param count Number of conditions/contents
 * @param store Variable store for lookups
 * @param result Output result string (caller must free)
 * @return 0 on success, non-zero on error
 */
int elif_statement_process(ConditionContext* ctx, const char* conditions[], 
                          const char* contents[], int count, 
                          store* st, char** result) {
    if (!ctx || !conditions || !contents || count <= 0 || !result || !st) {
        return -1;
    }
    
    *result = NULL;
    
    // Evaluate conditions in order until one is true
    for (int i = 0; i < count; i++) {
        if (!conditions[i] || !contents[i]) {
            continue;
        }
        
        int condition_result = condition_evaluate(ctx, conditions[i], st);
        
        if (condition_result == CONDITION_ERROR) {
            return -1;
        }
        
        if (condition_result == CONDITION_TRUE) {
            // This condition is true, return its content
            *result = strdup(contents[i]);
            return *result ? 0 : -1;
        }
    }
    
    // No condition was true, return empty string
    *result = strdup("");
    return *result ? 0 : -1;
}
