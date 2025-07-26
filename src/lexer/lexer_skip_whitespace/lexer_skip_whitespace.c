/**
 * @file lexer_skip_whitespace.c
 * @brief Lexer whitespace skipping function
 * @author XMD Team
 *
 * Implementation of whitespace skipping for the XMD lexer system.
 */

#include "../../../include/lexer_internal.h"

/**
 * @brief Skip whitespace characters but preserve newlines
 * @param lex Lexer instance
 */
void lexer_skip_whitespace(lexer* lex) {
    while (lexer_current_char(lex) != '\0' && 
           isspace((unsigned char)lexer_current_char(lex)) && 
           lexer_current_char(lex) != '\n') {
        lexer_advance(lex);
    }
}