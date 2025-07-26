/**
 * @file token_duplicate.c
 * @brief Token duplication function
 * @author XMD Team
 *
 * Implementation of token duplication for the XMD token system.
 */

#include "../../../include/token_internal.h"

/**
 * @brief Duplicate a token
 * @param tok Token to duplicate
 * @return New token copy or NULL on error
 */
token* token_duplicate(const token* tok) {
    if (tok == NULL) {
        return NULL;
    }
    
    return token_create(tok->type, tok->value, tok->line, tok->column);
}
