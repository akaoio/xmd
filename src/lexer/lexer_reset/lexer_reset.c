/**
 * @file lexer_reset.c
 * @brief Lexer reset function
 * @author XMD Team
 *
 * Implementation of lexer reset functionality for the XMD lexer system.
 */

#include "../../../include/lexer_internal.h"

/**
 * @brief Reset lexer to beginning of input
 * @param lex Lexer instance
 */
void lexer_reset(lexer* lex) {
    if (lex == NULL) {
        return;
    }
    
    lex->position = 0;
    lex->line = 1;
    lex->column = 1;
    
    if (lex->peeked_token != NULL) {
        token_free(lex->peeked_token);
        lex->peeked_token = NULL;
    }
}