/**
 * @file evaluate_condition.c
 * @brief Condition evaluation function
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include "../../../../include/c_api_internal.h"

/**
 * @brief Simple condition evaluator for if statements
 * @param condition Condition string (e.g., "status == \"active\"")
 * @param var_store Variable store
 * @return true if condition is true, false otherwise
 */
bool evaluate_condition(const char* condition, store* var_store) {
    if (!condition || !var_store) {
        return false;
    }
    
    // Simple condition parsing: var == "value" or var != "value"
    char var_name[256], operator[8], value[256];
    
    // Try to parse pattern: var == "value" or var != "value"
    if (sscanf(condition, "%255s %7s \"%255[^\"]\"", var_name, operator, value) == 3) {
        variable* var = store_get(var_store, var_name);
        const char* var_value = var ? variable_to_string(var) : "";
        
        if (strcmp(operator, "==") == 0) {
            return strcmp(var_value, value) == 0;
        } else if (strcmp(operator, "!=") == 0) {
            return strcmp(var_value, value) != 0;
        }
    }
    
    // Try without quotes: var == value or var != value
    if (sscanf(condition, "%255s %7s %255s", var_name, operator, value) == 3) {
        variable* var = store_get(var_store, var_name);
        const char* var_value = var ? variable_to_string(var) : "";
        
        if (strcmp(operator, "==") == 0) {
            return strcmp(var_value, value) == 0;
        } else if (strcmp(operator, "!=") == 0) {
            return strcmp(var_value, value) != 0;
        }
    }
    
    // Default: treat as variable existence check
    variable* var = store_get(var_store, condition);
    return var != NULL;
}
