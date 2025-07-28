/**
 * @file evaluate_condition.c
 * @brief Evaluate condition expression implementation
 * @author XMD Team
 * @date 2025-07-26
 */

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>

#include "../../../include/xmd_processor_internal.h"
#include "../../../include/variable.h"

/**
 * @brief Evaluate condition (supports ==, !=, <, >, <=, >=)
 * @param condition Condition string to evaluate (e.g., "var == value")
 * @param variables Variable store for variable lookups
 * @return true if condition is true, false otherwise
 */
bool evaluate_condition(const char* condition, store* variables) {
    printf("DEBUG: evaluate_condition called with: '%s'\n", condition);
    char* cond_copy = strdup(condition);
    char* trimmed = trim_whitespace(cond_copy);
    printf("DEBUG: trimmed condition: '%s'\n", trimmed);
    
    // Look for operators
    struct {
        const char* op;
        int (*compare)(const char*, const char*);
    } operators[] = {
        {"==", (int(*)(const char*, const char*))strcmp},
        {"!=", (int(*)(const char*, const char*))strcmp},
        {"<=", NULL},
        {">=", NULL},
        {"<", NULL},
        {">", NULL}
    };
    
    for (int i = 0; i < 6; i++) {
        char* op_pos = strstr(trimmed, operators[i].op);
        if (op_pos) {
            *op_pos = '\0';
            char* left = trim_whitespace(trimmed);
            char* right = trim_whitespace(op_pos + strlen(operators[i].op));
            
            // Get left variable value
            variable* var = store_get(variables, left);
            char* var_value = var ? variable_to_string(var) : strdup("");
            
            // Handle right side - check for quotes first, then variables
            char* right_value;
            if (strlen(right) >= 2 &&
                ((right[0] == '"' && right[strlen(right)-1] == '"') ||
                 (right[0] == '\'' && right[strlen(right)-1] == '\''))) {
                // Quoted string literal - remove quotes
                right_value = strdup(right + 1);
                right_value[strlen(right_value) - 1] = '\0';
            } else {
                // Try as variable first, then as literal
                variable* right_var = store_get(variables, right);
                if (right_var) {
                    right_value = variable_to_string(right_var);
                } else {
                    right_value = strdup(right);
                }
            }
            
            // Debug output
            printf("DEBUG: Comparing '%s' %s '%s'\n", var_value, operators[i].op, right_value);
            
            bool result = false;
            if (strcmp(operators[i].op, "==") == 0) {
                result = strcmp(var_value, right_value) == 0;
            } else if (strcmp(operators[i].op, "!=") == 0) {
                result = strcmp(var_value, right_value) != 0;
            } else {
                // Numeric comparisons
                double left_num = atof(var_value);
                double right_num = atof(right_value);
                
                if (strcmp(operators[i].op, "<") == 0) {
                    result = left_num < right_num;
                } else if (strcmp(operators[i].op, ">") == 0) {
                    result = left_num > right_num;
                } else if (strcmp(operators[i].op, "<=") == 0) {
                    result = left_num <= right_num;
                } else if (strcmp(operators[i].op, ">=") == 0) {
                    result = left_num >= right_num;
                }
            }
            
            free(var_value);
            free(right_value);
            free(cond_copy);
            return result;
        }
    }
    
    // If no operator, treat as boolean variable
    variable* var = store_get(variables, trimmed);
    bool result = false;
    if (var) {
        char* var_value = variable_to_string(var);
        result = (var_value && strlen(var_value) > 0 && 
                 strcmp(var_value, "false") != 0 && 
                 strcmp(var_value, "0") != 0);
        free(var_value);
    }
    
    free(cond_copy);
    return result;
}
