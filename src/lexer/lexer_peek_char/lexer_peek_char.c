/**
 * @file lexer_peek_char.c
 * @brief Lexer character peek function
 * @author XMD Team
 *
 * Implementation of character peeking for the XMD lexer system.
 */

#include "../../../include/lexer_internal.h"

/**
 * @brief Peek at next character without advancing
 * @param lex Lexer instance
 * @return Next character or '\0' if at end
 */
char lexer_peek_char(const lexer* lex) {
    if (lex->position + 1 >= lex->length) {
        return '\0';
    }
    return lex->input[lex->position + 1];
}