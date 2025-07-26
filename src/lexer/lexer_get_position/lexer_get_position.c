/**
 * @file lexer_get_position.c
 * @brief Lexer position getter function
 * @author XMD Team
 *
 * Implementation of position access for the XMD lexer system.
 */

#include "../../../include/lexer_internal.h"

/**
 * @brief Get current position in input
 * @param lex Lexer instance
 * @return Current position
 */
size_t lexer_get_position(const lexer* lex) {
    return lex ? lex->position : 0;
}