/**
 * @file evaluate_condition.c
 * @brief Evaluate condition expression implementation
 * @author XMD Team
 * @date 2025-07-26
 */

#include "../../../include/xmd_processor_internal.h"
#include "../../../include/variable.h"

/**
 * @brief Evaluate condition (supports ==, !=, <, >, <=, >=)
 * @param condition Condition string to evaluate (e.g., "var == value")
 * @param variables Variable store for variable lookups
 * @return true if condition is true, false otherwise
 */
bool evaluate_condition(const char* condition, store* variables) {
    char* cond_copy = strdup(condition);
    char* trimmed = trim_whitespace(cond_copy);
    
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
            
            // Remove quotes from right side
            if (strlen(right) >= 2 &&
                ((right[0] == '"' && right[strlen(right)-1] == '"') ||
                 (right[0] == '\'' && right[strlen(right)-1] == '\''))) {
                right[strlen(right)-1] = '\0';
                right++;
            }
            
            // Get variable value
            variable* var = store_get(variables, left);
            char* var_value = var ? variable_to_string(var) : strdup("");
            
            bool result = false;
            if (strcmp(operators[i].op, "==") == 0) {
                result = strcmp(var_value, right) == 0;
            } else if (strcmp(operators[i].op, "!=") == 0) {
                result = strcmp(var_value, right) != 0;
            } else {
                // Numeric comparisons
                double left_num = atof(var_value);
                double right_num = atof(right);
                
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
