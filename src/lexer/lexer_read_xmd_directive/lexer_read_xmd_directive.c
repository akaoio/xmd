/**
 * @file lexer_read_xmd_directive.c
 * @brief XMD directive reading function for lexer
 * @author XMD Team
 *
 * Implementation of XMD directive reading functionality for the XMD lexer system.
 */

#include "../../../include/lexer_internal.h"

/**
 * @brief Read inline XMD directive
 * @param lex Lexer instance
 * @return Directive content (must be freed)
 */
char* lexer_read_xmd_directive(lexer* lex) {
    size_t start_pos = lex->position;
    
    // Skip xmd:
    lexer_advance(lex); // x
    lexer_advance(lex); // m
    lexer_advance(lex); // d
    lexer_advance(lex); // :
    
    // Read command name
    while (lexer_current_char(lex) != '\0' && 
           lexer_current_char(lex) != '(' &&
           lexer_current_char(lex) != '\n') {
        lexer_advance(lex);
    }
    
    // Read arguments if present
    if (lexer_current_char(lex) == '(') {
        int paren_count = 1;
        lexer_advance(lex); // skip opening (
        
        while (lexer_current_char(lex) != '\0' && paren_count > 0) {
            if (lexer_current_char(lex) == '(') {
                paren_count++;
            } else if (lexer_current_char(lex) == ')') {
                paren_count--;
            }
            lexer_advance(lex);
        }
    }
    
    size_t length = lex->position - start_pos;
    return lexer_extract_substring(lex, start_pos, length);
}