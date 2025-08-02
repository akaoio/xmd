/**
 * @file evaluate_condition.c
 * @brief Evaluate conditional expression
 * 
 * This file contains ONLY the evaluate_condition function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/systems_consolidated.c (with syntax fixes)
 */

#include <string.h>
#include <stdbool.h>
#include "../../../include/conditional.h"
#include "../../../include/store.h"
#include "../../../include/variable.h"
/**
 * @brief Evaluate conditional expression
 * @param condition Condition string to evaluate
 * @param variables Variable store
 * @return true if condition is true, false otherwise
  * /
 */
bool evaluate_condition(const char* condition, store* variables) {
    if (!condition) {
        return false;
    }
    
    // Simple condition evaluation - can be enhanced
    if (strcmp(condition, "true") == 0) {
        return true;
    }
    
    if (strcmp(condition, "false") == 0) {
        return false;
    }
    
    // Variable reference
    if (variables) {
        variable* var = store_get(variables, condition);
        if (var) {
            return variable_to_boolean(var);
        }
    }
    
    return false;
}
