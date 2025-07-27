/**
 * @file condition.c
 * @brief Condition evaluation implementation
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../../include/conditional.h"

/**
 * @brief Parse comparison operator from expression
 * @param expr Expression to parse
 * @param operator Output operator type
 * @return Position after operator or NULL if not found
 */
const char* condition_parse_operator(const char* expr, int* operator) {
    if (!expr || !operator) {
        return NULL;
    }
    
    // Skip whitespace
    while (isspace(*expr)) expr++;
    
    if (strncmp(expr, "==", 2) == 0) {
        *operator = CONDITION_OP_EQUAL;
        return expr + 2;
    } else if (strncmp(expr, "!=", 2) == 0) {
        *operator = CONDITION_OP_NOT_EQUAL;
        return expr + 2;
    } else if (strncmp(expr, "<=", 2) == 0) {
        *operator = CONDITION_OP_LESS_EQUAL;
        return expr + 2;
    } else if (strncmp(expr, ">=", 2) == 0) {
        *operator = CONDITION_OP_GREATER_EQUAL;
        return expr + 2;
    } else if (*expr == '<') {
        *operator = CONDITION_OP_LESS;
        return expr + 1;
    } else if (*expr == '>') {
        *operator = CONDITION_OP_GREATER;
        return expr + 1;
    }
    
    return NULL;
}
