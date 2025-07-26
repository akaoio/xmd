/**
 * @file lexer_read_code_block.c
 * @brief Code block reading function for lexer
 * @author XMD Team
 *
 * Implementation of code block reading functionality for the XMD lexer system.
 */

#include "../../../include/lexer_internal.h"

/**
 * @brief Read code block (``` or indented)
 * @param lex Lexer instance
 * @return Code block content (must be freed)
 */
char* lexer_read_code_block(lexer* lex) {
    size_t start_pos = lex->position;
    
    if (lexer_starts_with(lex, "```")) {
        // Fenced code block
        lexer_advance(lex); // `
        lexer_advance(lex); // `
        lexer_advance(lex); // `
        
        // Read until closing ```
        while (lexer_current_char(lex) != '\0') {
            if (lexer_current_char(lex) == '\n' && 
                lexer_peek_char(lex) != '\0') {
                lexer_advance(lex); // newline
                if (lexer_starts_with(lex, "```")) {
                    lexer_advance(lex); // `
                    lexer_advance(lex); // `
                    lexer_advance(lex); // `
                    break;
                }
            } else {
                lexer_advance(lex);
            }
        }
    }
    
    size_t length = lex->position - start_pos;
    return lexer_extract_substring(lex, start_pos, length);
}