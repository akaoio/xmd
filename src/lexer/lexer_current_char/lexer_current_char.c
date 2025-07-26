/**
 * @file lexer_current_char.c
 * @brief Lexer current character getter function
 * @author XMD Team
 *
 * Implementation of current character access for the XMD lexer system.
 */

#include "../../../include/lexer_internal.h"

/**
 * @brief Get current character without advancing
 * @param lex Lexer instance
 * @return Current character or '\0' if at end
 */
char lexer_current_char(const lexer* lex) {
    if (lex->position >= lex->length) {
        return '\0';
    }
    return lex->input[lex->position];
}