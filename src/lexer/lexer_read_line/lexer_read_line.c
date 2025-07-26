/**
 * @file lexer_read_line.c
 * @brief Line reading function for lexer
 * @author XMD Team
 *
 * Implementation of line reading functionality for the XMD lexer system.
 */

#include "../../../include/lexer_internal.h"

/**
 * @brief Read until end of line
 * @param lex Lexer instance
 * @return Line content (must be freed)
 */
char* lexer_read_line(lexer* lex) {
    size_t start_pos = lex->position;
    
    // Find end of line
    while (lexer_current_char(lex) != '\0' && lexer_current_char(lex) != '\n') {
        lexer_advance(lex);
    }
    
    size_t length = lex->position - start_pos;
    return lexer_extract_substring(lex, start_pos, length);
}