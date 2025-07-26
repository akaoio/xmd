/**
 * @file lexer_peek_token.c
 * @brief Peek token function for lexer
 * @author XMD Team
 *
 * Implementation of peek token functionality for the XMD lexer system.
 */

#include "../../../include/lexer_internal.h"

/**
 * @brief Peek at next token without consuming it
 * @param lex Lexer instance
 * @return Copy of next token or NULL on error
 */
token* lexer_peek_token(lexer* lex) {
    if (lex == NULL) {
        return NULL;
    }
    
    if (lex->peeked_token == NULL) {
        lex->peeked_token = lexer_next_token(lex);
    }
    
    return token_copy(lex->peeked_token);
}