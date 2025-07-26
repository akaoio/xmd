/**
 * @file lexer_get_column.c
 * @brief Lexer column number getter function
 * @author XMD Team
 *
 * Implementation of column number access for the XMD lexer system.
 */

#include "../../../include/lexer_internal.h"

/**
 * @brief Get current column number
 * @param lex Lexer instance
 * @return Current column number (1-based)
 */
size_t lexer_get_column(const lexer* lex) {
    return lex ? lex->column : 0;
}