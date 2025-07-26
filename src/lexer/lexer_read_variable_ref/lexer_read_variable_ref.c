/**
 * @file lexer_read_variable_ref.c
 * @brief Variable reference reading function for lexer
 * @author XMD Team
 *
 * Implementation of variable reference reading functionality for the XMD lexer system.
 */

#include "../../../include/lexer_internal.h"

/**
 * @brief Read variable reference {{var}}
 * @param lex Lexer instance
 * @return Variable reference (must be freed)
 */
char* lexer_read_variable_ref(lexer* lex) {
    size_t start_pos = lex->position;
    
    // Skip opening {{
    lexer_advance(lex); // {
    lexer_advance(lex); // {
    
    // Read until }}
    while (lexer_current_char(lex) != '\0') {
        if (lexer_starts_with(lex, "}}")) {
            lexer_advance(lex); // }
            lexer_advance(lex); // }
            break;
        }
        lexer_advance(lex);
    }
    
    size_t length = lex->position - start_pos;
    return lexer_extract_substring(lex, start_pos, length);
}