/**
 * @file lexer_consolidated.c
 * @brief Consolidated XMD lexer operations (enhanced with expression support)
 * @author XMD Development Team
 *
 * All lexer functionality consolidated from 23 directories.
 * Supports both HTML comment syntax and native XMD syntax per Genesis blueprint.
 * Includes enhanced expression parsing capabilities.
 * Moved to src level to eliminate lexer/ directory for 95% milestone.
 */

#include "../include/lexer_internal.h"
#include "../include/lexer_enhanced.h"
#include "../include/memory.h"
#include "../include/utils.h"
#include "../include/token.h"
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// ============================================================================
// LEXER LIFECYCLE
// ============================================================================

/**
 * @brief Create new lexer
 * @param input Input string to tokenize
 * @return New lexer instance or NULL on failure
 */
lexer* lexer_create(const char* input) {
    if (!input) {
        return NULL;
    }
    
    lexer* lex = xmd_calloc(1, sizeof(lexer));
    if (!lex) {
        return NULL;
    }
    
    lex->input = input;
    lex->length = strlen(input);
    lex->position = 0;
    lex->line = 1;
    lex->column = 1;
    
    return lex;
}

/**
 * @brief Free lexer resources
 * @param lex Lexer to free
 */
void lexer_free(lexer* lex) {
    if (!lex) return;
    
    free(lex);
}

/**
 * @brief Reset lexer to beginning of input
 * @param lex Lexer to reset
 */
void lexer_reset(lexer* lex) {
    if (!lex) return;
    
    lex->position = 0;
    lex->line = 1;
    lex->column = 1;
}

// ============================================================================
// CHARACTER NAVIGATION
// ============================================================================

/**
 * @brief Get current character without advancing
 * @param lex Lexer instance
 * @return Current character or '\0' at end
 */
char lexer_current_char(const lexer* lex) {
    if (!lex || lex->position >= lex->length) {
        return '\0';
    }
    return lex->input[lex->position];
}

/**
 * @brief Peek at next character without advancing
 * @param lex Lexer instance
 * @return Next character or '\0' at end
 */
char lexer_peek_char(const lexer* lex) {
    if (!lex || lex->position + 1 >= lex->length) {
        return '\0';
    }
    return lex->input[lex->position + 1];
}

/**
 * @brief Advance to next character
 * @param lex Lexer instance
 */
char lexer_advance(lexer* lex) {
    if (!lex || lex->position >= lex->length) {
        return '\0';
    }
    
    char current = lex->input[lex->position];
    
    if (current == '\n') {
        lex->line++;
        lex->column = 1;
    } else {
        lex->column++;
    }
    
    lex->position++;
    return current;
}

/**
 * @brief Check if at end of input
 * @param lex Lexer instance
 * @return true if at end
 */
bool lexer_at_end(const lexer* lex) {
    return !lex || lex->position >= lex->length;
}

// ============================================================================
// WHITESPACE AND UTILITY
// ============================================================================

/**
 * @brief Skip whitespace characters
 * @param lex Lexer instance
 */
void lexer_skip_whitespace(lexer* lex) {
    if (!lex) return;
    
    while (!lexer_at_end(lex)) {
        char c = lexer_current_char(lex);
        if (c == ' ' || c == '\t' || c == '\r') {
            lexer_advance(lex);
        } else {
            break;
        }
    }
}

/**
 * @brief Check if input starts with given string at current position
 * @param lex Lexer instance
 * @param str String to check
 * @return true if starts with string
 */
bool lexer_starts_with(const lexer* lex, const char* str) {
    if (!lex || !str) return false;
    
    size_t str_len = strlen(str);
    if (lex->position + str_len > lex->length) {
        return false;
    }
    
    return strncmp(lex->input + lex->position, str, str_len) == 0;
}

// ============================================================================
// STRING EXTRACTION
// ============================================================================

/**
 * @brief Extract substring from current position
 * @param lex Lexer instance
 * @param start Start position
 * @param end End position
 * @return Extracted string (must be freed) or NULL
 */
char* lexer_extract_substring(const lexer* lex, size_t start, size_t end) {
    if (!lex || start >= lex->length || end > lex->length || start >= end) {
        return NULL;
    }
    
    size_t len = end - start;
    char* result = xmd_malloc(len + 1);
    if (!result) return NULL;
    
    strncpy(result, lex->input + start, len);
    result[len] = '\0';
    
    return result;
}

// ============================================================================
// TOKEN READING FUNCTIONS
// ============================================================================

/**
 * @brief Read HTML comment block
 * @param lex Lexer instance
 * @return Comment content string or NULL
 */
char* lexer_read_html_comment(lexer* lex) {
    if (!lex || !lexer_starts_with(lex, "<!--")) {
        return NULL;
    }
    
    size_t start = lex->position + 4; // Skip "<!--"
    lexer_advance(lex); lexer_advance(lex); lexer_advance(lex); lexer_advance(lex);
    
    while (!lexer_at_end(lex)) {
        if (lexer_starts_with(lex, "-->")) {
            size_t end = lex->position;
            lexer_advance(lex); lexer_advance(lex); lexer_advance(lex); // Skip "-->"
            
            return lexer_extract_substring(lex, start, end);
        }
        lexer_advance(lex);
    }
    
    return NULL; // Unterminated comment
}

/**
 * @brief Read XMD directive
 * @param lex Lexer instance
 * @return Directive string or NULL
 */
char* lexer_read_xmd_directive(lexer* lex) {
    if (!lex) return NULL;
    
    size_t start = lex->position;
    
    // Read directive name
    while (!lexer_at_end(lex)) {
        char c = lexer_current_char(lex);
        if (isspace(c) || c == ':') {
            break;
        }
        lexer_advance(lex);
    }
    
    size_t end = lex->position;
    return lexer_extract_substring(lex, start, end);
}

/**
 * @brief Read variable reference (supports both ${var} and {{var}} syntax)
 * @param lex Lexer instance
 * @return Variable name string or NULL
 */
char* lexer_read_variable_ref(lexer* lex) {
    if (!lex) return NULL;
    
    char first = lexer_current_char(lex);
    
    // Check for {{variable}} syntax (Genesis preferred)
    if (first == '{' && lexer_peek_char(lex) == '{') {
        lexer_advance(lex); // Skip first '{'
        lexer_advance(lex); // Skip second '{'
        size_t start = lex->position;
        
        while (!lexer_at_end(lex)) {
            if (lexer_current_char(lex) == '}' && lexer_peek_char(lex) == '}') {
                size_t end = lex->position;
                lexer_advance(lex); // Skip first '}'
                lexer_advance(lex); // Skip second '}'
                return lexer_extract_substring(lex, start, end);
            }
            lexer_advance(lex);
        }
        return NULL; // Unterminated {{
    }
    
    // Check for ${variable} syntax (legacy support)
    if (first == '$') {
        lexer_advance(lex); // Skip '$'
        
        if (lexer_current_char(lex) == '{') {
            // ${variable} format
            lexer_advance(lex); // Skip '{'
            size_t start = lex->position;
            
            while (!lexer_at_end(lex) && lexer_current_char(lex) != '}') {
                lexer_advance(lex);
            }
            
            if (lexer_current_char(lex) == '}') {
                size_t end = lex->position;
                lexer_advance(lex); // Skip '}'
                
                return lexer_extract_substring(lex, start, end);
            }
        } else {
            // $variable format
            size_t start = lex->position;
            
            while (!lexer_at_end(lex)) {
                char c = lexer_current_char(lex);
                if (!isalnum(c) && c != '_') {
                    break;
                }
                lexer_advance(lex);
            }
            
            size_t end = lex->position;
            return lexer_extract_substring(lex, start, end);
        }
    }
    
    return NULL;
}

/**
 * @brief Read text content
 * @param lex Lexer instance
 * @return Text string or NULL
 */
char* lexer_read_text(lexer* lex) {
    if (!lex) return NULL;
    
    size_t start = lex->position;
    
    while (!lexer_at_end(lex)) {
        char c = lexer_current_char(lex);
        
        // Stop at XMD markers
        if (c == '$' || lexer_starts_with(lex, "<!--") || lexer_starts_with(lex, "xmd:") ||
            (c == '{' && lexer_peek_char(lex) == '{')) {
            break;
        }
        
        lexer_advance(lex);
    }
    
    if (lex->position == start) {
        return NULL; // No text read
    }
    
    return lexer_extract_substring(lex, start, lex->position);
}

/**
 * @brief Read a line from current position
 * @param lex Lexer instance
 * @return Line string or NULL
 */
char* lexer_read_line(lexer* lex) {
    if (!lex) return NULL;
    
    size_t start = lex->position;
    
    while (!lexer_at_end(lex) && lexer_current_char(lex) != '\n') {
        lexer_advance(lex);
    }
    
    size_t end = lex->position;
    
    // Skip the newline if we're at one
    if (lexer_current_char(lex) == '\n') {
        lexer_advance(lex);
    }
    
    if (end == start) {
        return xmd_strdup(""); // Empty line
    }
    
    return lexer_extract_substring(lex, start, end);
}

/**
 * @brief Read code block
 * @param lex Lexer instance
 * @return Code block content or NULL
 */
char* lexer_read_code_block(lexer* lex) {
    if (!lex) return NULL;
    
    // Simple implementation - read until end of block marker or EOF
    size_t start = lex->position;
    int brace_count = 0;
    
    while (!lexer_at_end(lex)) {
        char c = lexer_current_char(lex);
        
        if (c == '{') {
            brace_count++;
        } else if (c == '}') {
            brace_count--;
            if (brace_count == 0) {
                size_t end = lex->position;
                lexer_advance(lex); // Skip the closing brace
                return lexer_extract_substring(lex, start, end);
            }
        }
        
        lexer_advance(lex);
    }
    
    // Return whatever we have if we hit EOF
    return lexer_extract_substring(lex, start, lex->position);
}

// ============================================================================
// MAIN TOKENIZATION
// ============================================================================

/**
 * @brief Get next token from input
 * @param lex Lexer instance
 * @return Next token or NULL at end
 */
token* lexer_next_token(lexer* lex) {
    if (!lex || lexer_at_end(lex)) {
        return NULL;
    }
    
    lexer_skip_whitespace(lex);
    
    if (lexer_at_end(lex)) {
        return NULL;
    }
    
    // Try different token types
    token* tok = NULL;
    
    if (lexer_starts_with(lex, "<!--")) {
        tok = lexer_read_html_comment(lex);
    } else if (lexer_current_char(lex) == '$' || 
               (lexer_current_char(lex) == '{' && lexer_peek_char(lex) == '{')) {
        tok = lexer_read_variable_ref(lex);
    } else if (lexer_starts_with(lex, "xmd:")) {
        lexer_advance(lex); lexer_advance(lex); lexer_advance(lex); lexer_advance(lex); // Skip "xmd:"
        tok = lexer_read_xmd_directive(lex);
    } else {
        tok = lexer_read_text(lex);
    }
    
    return tok;
}

/**
 * @brief Peek at next token without consuming it
 * @param lex Lexer instance
 * @return Next token or NULL at end
 */
token* lexer_peek_token(lexer* lex) {
    if (!lex) return NULL;
    
    // Save current state
    size_t saved_pos = lex->position;
    size_t saved_line = lex->line;
    size_t saved_col = lex->column;
    
    token* tok = lexer_next_token(lex);
    
    // Restore state
    lex->position = saved_pos;
    lex->line = saved_line;
    lex->column = saved_col;
    
    return tok;
}