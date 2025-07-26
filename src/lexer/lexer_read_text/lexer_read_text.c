/**
 * @file lexer_read_text.c
 * @brief Text reading function for lexer
 * @author XMD Team
 *
 * Implementation of text reading functionality for the XMD lexer system.
 */

#include "../../../include/lexer_internal.h"

/**
 * @brief Read text until special marker
 * @param lex Lexer instance
 * @return Text content (must be freed)
 */
char* lexer_read_text(lexer* lex) {
    size_t start_pos = lex->position;
    
    while (lexer_current_char(lex) != '\0') {
        char ch = lexer_current_char(lex);
        
        // Stop at special markers
        // Only stop at -, *, + if they're at the beginning of a line (list items)
        if ((ch == '#' && lex->column == 1) || 
            ((ch == '-' || ch == '*' || ch == '+') && lex->column == 1) || 
            lexer_starts_with(lex, "<!--") || 
            lexer_starts_with(lex, "```") ||
            lexer_starts_with(lex, "{{") ||
            lexer_starts_with(lex, "xmd:")) {  // Add inline XMD directive detection
            break;
        }
        
        // Stop at newline to separate lines into different tokens
        if (ch == '\n') {
            break;
        }
        
        lexer_advance(lex);
    }
    
    size_t length = lex->position - start_pos;
    if (length == 0) {
        return NULL;
    }
    
    char* result = malloc(length + 1);
    if (result == NULL) {
        return NULL;
    }
    
    memcpy(result, &lex->input[start_pos], length);
    result[length] = '\0';
    
    // Keep trailing whitespace for proper text segmentation
    // Don't trim - preserve original spacing
    
    return result;
}