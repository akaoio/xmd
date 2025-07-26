/**
 * @file lexer_free.c
 * @brief Lexer memory deallocation function
 * @author XMD Team
 *
 * Implementation of lexer cleanup for the XMD lexer system.
 */

#include "../../../include/lexer_internal.h"

/**
 * @brief Free lexer resources
 * @param lex Lexer to free (can be NULL)
 */
void lexer_free(lexer* lex) {
    if (lex == NULL) {
        return;
    }
    
    if (lex->peeked_token != NULL) {
        token_free(lex->peeked_token);
    }
    
    free(lex);
}