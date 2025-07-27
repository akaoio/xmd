/**
 * @file condition_logical_not.c
 * @brief Parse logical NOT operator
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../../../include/conditional.h"

/**
 * @brief Parse logical NOT operator
 * @param expr Expression to parse
 * @param operator Output operator type
 * @return Position after operator or NULL if not found
 */
const char* condition_logical_not(const char* expr, int* operator) {
    if (!expr || !operator) {
        return NULL;
    }
    
    // Skip whitespace
    while (isspace(*expr)) expr++;
    
    if (*expr == '!') {
        *operator = CONDITION_OP_LOGICAL_NOT;
        return expr + 1;
    }
    
    return NULL;
}