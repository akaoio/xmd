/**
 * @file lexer_next_token.c
 * @brief Next token function for lexer
 * @author XMD Team
 *
 * Implementation of next token functionality for the XMD lexer system.
 */

#include "../../../include/lexer_internal.h"

/**
 * @brief Get next token from lexer
 * @param lex Lexer instance
 * @return Next token or NULL on error
 */
token* lexer_next_token(lexer* lex) {
    if (lex == NULL) {
        return NULL;
    }
    
    // Return cached token if available
    if (lex->peeked_token != NULL) {
        token* result = lex->peeked_token;
        lex->peeked_token = NULL;
        return result;
    }
    
    lexer_skip_whitespace(lex);
    
    if (lexer_current_char(lex) == '\0') {
        return token_create(TOKEN_EOF, "", lex->line, lex->column);
    }
    
    size_t token_line = lex->line;
    size_t token_column = lex->column;
    
    // Check for headings (must be at start of line)
    if (lexer_current_char(lex) == '#' && token_column == 1) {
        char* content = lexer_read_line(lex);
        return token_create(TOKEN_HEADING, content, token_line, token_column);
    }
    
    // Check for list items (must be at start of line)
    if ((lexer_current_char(lex) == '-' || lexer_current_char(lex) == '*' || 
         lexer_current_char(lex) == '+') && token_column == 1) {
        char* content = lexer_read_line(lex);
        return token_create(TOKEN_LIST_ITEM, content, token_line, token_column);
    }
    
    // Check for HTML comments (including XMD directives)
    if (lexer_starts_with(lex, "<!--")) {
        char* content = lexer_read_html_comment(lex);
        
        // Check if it's an XMD directive
        char* xmd_start = strstr(content, "xmd:");
        if (xmd_start != NULL) {
            // Return the full HTML comment for XMD directives
            return token_create(TOKEN_XMD_DIRECTIVE, content, token_line, token_column);
        } else {
            return token_create(TOKEN_HTML_COMMENT, content, token_line, token_column);
        }
    }
    
    // Check for code blocks
    if (lexer_starts_with(lex, "```")) {
        char* content = lexer_read_code_block(lex);
        return token_create(TOKEN_CODE_BLOCK, content, token_line, token_column);
    }
    
    // Check for variable references
    if (lexer_starts_with(lex, "{{")) {
        char* content = lexer_read_variable_ref(lex);
        return token_create(TOKEN_VARIABLE_REF, content, token_line, token_column);
    }
    
    // Note: Inline XMD directives (xmd:command) are NOT supported
    // Only HTML comment format is allowed: <!-- xmd:command -->
    
    // Default to text
    char* content = lexer_read_text(lex);
    if (content == NULL || strlen(content) == 0) {
        free(content);
        // Skip one character to avoid infinite loop
        lexer_advance(lex);
        return lexer_next_token(lex);
    }
    
    return token_create(TOKEN_TEXT, content, token_line, token_column);
}