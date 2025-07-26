/**
 * @file lexer_at_end.c
 * @brief Lexer end-of-input checker function
 * @author XMD Team
 *
 * Implementation of end-of-input checking for the XMD lexer system.
 */

#include "../../../include/lexer_internal.h"

/**
 * @brief Check if lexer has reached end of input
 * @param lex Lexer instance
 * @return true if at end of input
 */
bool lexer_at_end(const lexer* lex) {
    return lex ? (lex->position >= lex->length) : true;
}