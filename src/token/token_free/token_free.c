/**
 * @file token_free.c
 * @brief Token memory deallocation function
 * @author XMD Team
 *
 * Implementation of token memory cleanup for the XMD token system.
 */

#include "../../../include/token_internal.h"

/**
 * @brief Free a token and its resources
 * @param tok Token to free (can be NULL)
 */
void token_free(token* tok) {
    if (tok == NULL) {
        return;
    }
    
    free(tok->value);
    free(tok);
}
