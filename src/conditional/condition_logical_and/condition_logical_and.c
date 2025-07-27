/**
 * @file condition_logical_and.c
 * @brief Parse logical AND operator
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../../../include/conditional.h"

/**
 * @brief Parse logical AND operator
 * @param expr Expression to parse
 * @param operator Output operator type
 * @return Position after operator or NULL if not found
 */
const char* condition_logical_and(const char* expr, int* operator) {
    if (!expr || !operator) {
        return NULL;
    }
    
    // Skip whitespace
    while (isspace(*expr)) expr++;
    
    if (strncmp(expr, "&&", 2) == 0) {
        *operator = CONDITION_OP_LOGICAL_AND;
        return expr + 2;
    }
    
    return NULL;
}