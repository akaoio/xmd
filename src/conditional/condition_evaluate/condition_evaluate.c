/**
 * @file condition_evaluate.c
 * @brief Evaluate conditional expressions
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../../include/conditional.h"
#include "../../../include/variable.h"
#include "../../../include/store.h"

/**
 * @brief Evaluate a condition expression
 * @param ctx Condition context
 * @param condition Condition string to evaluate
 * @param variables Variable store
 * @return CONDITION_TRUE/CONDITION_FALSE/CONDITION_ERROR
 */
int condition_evaluate(ConditionContext* ctx, const char* condition, store* variables) {
    if (!ctx || !condition || !variables) {
        return CONDITION_ERROR;
    }
    
    // Remove leading/trailing whitespace
    while (*condition == ' ' || *condition == '\t') condition++;
    
    size_t len = strlen(condition);
    while (len > 0 && (condition[len-1] == ' ' || condition[len-1] == '\t')) len--;
    
    // Handle literal values
    if (strncmp(condition, "true", len) == 0 && len == 4) {
        ctx->last_result = true;
        return CONDITION_TRUE;
    }
    if (strncmp(condition, "false", len) == 0 && len == 5) {
        ctx->last_result = false;
        return CONDITION_FALSE;
    }
    
    // Handle logical operators BEFORE template variables
    
    // Check for logical NOT
    if (len > 1 && condition[0] == '!') {
        int sub_result = condition_evaluate(ctx, condition + 1, variables);
        if (sub_result == CONDITION_ERROR) {
            return CONDITION_ERROR;
        }
        ctx->last_result = !ctx->last_result;
        return ctx->last_result ? CONDITION_TRUE : CONDITION_FALSE;
    }
    
    // Check for logical AND
    char* and_pos = strstr(condition, " && ");
    if (and_pos != NULL) {
        // Split at the AND operator
        size_t left_len = and_pos - condition;
        size_t right_offset = and_pos - condition + 4; // Skip " && "
        
        char* left_expr = malloc(left_len + 1);
        char* right_expr = malloc(len - right_offset + 1);
        
        if (!left_expr || !right_expr) {
            free(left_expr);
            free(right_expr);
            return CONDITION_ERROR;
        }
        
        strncpy(left_expr, condition, left_len);
        left_expr[left_len] = '\0';
        strcpy(right_expr, condition + right_offset);
        
        int left_result = condition_evaluate(ctx, left_expr, variables);
        int right_result = condition_evaluate(ctx, right_expr, variables);
        
        free(left_expr);
        free(right_expr);
        
        if (left_result == CONDITION_ERROR || right_result == CONDITION_ERROR) {
            return CONDITION_ERROR;
        }
        
        bool result = (left_result == CONDITION_TRUE) && (right_result == CONDITION_TRUE);
        ctx->last_result = result;
        return result ? CONDITION_TRUE : CONDITION_FALSE;
    }
    
    // Check for logical OR
    char* or_pos = strstr(condition, " || ");
    if (or_pos != NULL) {
        // Split at the OR operator
        size_t left_len = or_pos - condition;
        size_t right_offset = or_pos - condition + 4; // Skip " || "
        
        char* left_expr = malloc(left_len + 1);
        char* right_expr = malloc(len - right_offset + 1);
        
        if (!left_expr || !right_expr) {
            free(left_expr);
            free(right_expr);
            return CONDITION_ERROR;
        }
        
        strncpy(left_expr, condition, left_len);
        left_expr[left_len] = '\0';
        strcpy(right_expr, condition + right_offset);
        
        int left_result = condition_evaluate(ctx, left_expr, variables);
        int right_result = condition_evaluate(ctx, right_expr, variables);
        
        free(left_expr);
        free(right_expr);
        
        if (left_result == CONDITION_ERROR || right_result == CONDITION_ERROR) {
            return CONDITION_ERROR;
        }
        
        bool result = (left_result == CONDITION_TRUE) || (right_result == CONDITION_TRUE);
        ctx->last_result = result;
        return result ? CONDITION_TRUE : CONDITION_FALSE;
    }
    
    // Handle template variables like {{variable_name}}
    if (len >= 4 && condition[0] == '{' && condition[1] == '{' && 
        condition[len-2] == '}' && condition[len-1] == '}') {
        
        // Extract variable name from {{variable_name}}
        size_t var_len = len - 4; // Remove {{ and }}
        char* var_name = malloc(var_len + 1);
        if (!var_name) {
            return CONDITION_ERROR;
        }
        strncpy(var_name, condition + 2, var_len);
        var_name[var_len] = '\0';
        
        // Check if variable exists
        variable* var = store_get(variables, var_name);
        int result = CONDITION_FALSE;
        
        if (var) {
            // Convert to boolean
            bool is_true = variable_to_boolean(var);
            result = is_true ? CONDITION_TRUE : CONDITION_FALSE;
            ctx->last_result = is_true;
        } else {
            // Undefined variable is false
            ctx->last_result = false;
            result = CONDITION_FALSE;
        }
        
        free(var_name);
        return result;
    }
    
    // For now, treat other expressions as simple variable names (fallback)
    char* var_name = malloc(len + 1);
    if (!var_name) {
        return CONDITION_ERROR;
    }
    strncpy(var_name, condition, len);
    var_name[len] = '\0';
    
    // Check if variable exists
    variable* var = store_get(variables, var_name);
    int result = CONDITION_FALSE;
    
    if (var) {
        // Convert to boolean
        bool is_true = variable_to_boolean(var);
        result = is_true ? CONDITION_TRUE : CONDITION_FALSE;
        ctx->last_result = is_true;
    } else {
        // Undefined variable is false
        ctx->last_result = false;
    }
    
    free(var_name);
    return result;
}