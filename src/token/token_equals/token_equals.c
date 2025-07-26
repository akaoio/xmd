/**
 * @file token_equals.c
 * @brief Token equality comparison function
 * @author XMD Team
 *
 * Implementation of token equality comparison for the XMD token system.
 */

#include "../../../include/token_internal.h"

/**
 * @brief Compare two tokens for equality
 * @param tok1 First token
 * @param tok2 Second token
 * @return true if equal, false otherwise
 */
bool token_equals(const token* tok1, const token* tok2) {
    // Handle NULL cases
    if (tok1 == NULL && tok2 == NULL) {
        return true;
    }
    if (tok1 == NULL || tok2 == NULL) {
        return false;
    }
    
    // Compare type, line, and column
    if (tok1->type != tok2->type || tok1->line != tok2->line || tok1->column != tok2->column) {
        return false;
    }
    
    // Compare values
    if (tok1->value == NULL && tok2->value == NULL) {
        return true;
    }
    if (tok1->value == NULL || tok2->value == NULL) {
        return false;
    }
    
    return strcmp(tok1->value, tok2->value) == 0;
}
