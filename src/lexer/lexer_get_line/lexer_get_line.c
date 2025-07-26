/**
 * @file lexer_get_line.c
 * @brief Lexer line number getter function
 * @author XMD Team
 *
 * Implementation of line number access for the XMD lexer system.
 */

#include "../../../include/lexer_internal.h"

/**
 * @brief Get current line number
 * @param lex Lexer instance
 * @return Current line number (1-based)
 */
size_t lexer_get_line(const lexer* lex) {
    return lex ? lex->line : 0;
}