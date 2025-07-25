/**
 * @file lexer.c
 * @brief Lexical analyzer implementation
 * @author XMD Team
 *
 * Tokenizes markdown input with XMD directive support,
 * position tracking, and UTF-8 handling.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "token.h"
#include "lexer.h"

/**
 * @struct lexer
 * @brief Lexer state structure
 */
struct lexer {
    const char* input;     /**< Input string */
    size_t position;       /**< Current position in input */
    size_t length;         /**< Length of input */
    size_t line;           /**< Current line number (1-based) */
    size_t column;         /**< Current column number (1-based) */
    token* peeked_token;   /**< Cached token for peek functionality */
};

/**
 * @brief Create a new lexer
 * @param input Input string to tokenize
 * @return New lexer instance or NULL on failure
 */
lexer* lexer_create(const char* input) {
    if (input == NULL) {
        return NULL;
    }
    
    lexer* lex = malloc(sizeof(lexer));
    if (lex == NULL) {
        return NULL;
    }
    
    lex->input = input;
    lex->position = 0;
    lex->length = strlen(input);
    lex->line = 1;
    lex->column = 1;
    lex->peeked_token = NULL;
    
    return lex;
}

/**
 * @brief Free lexer resources
 * @param lex Lexer to free (can be NULL)
 */
void lexer_free(lexer* lex) {
    if (lex == NULL) {
        return;
    }
    
    if (lex->peeked_token != NULL) {
        token_free(lex->peeked_token);
    }
    
    free(lex);
}


/**
 * @brief Get current character without advancing
 * @param lex Lexer instance
 * @return Current character or '\0' if at end
 */
static char lexer_current_char(const lexer* lex) {
    if (lex->position >= lex->length) {
        return '\0';
    }
    return lex->input[lex->position];
}

/**
 * @brief Advance position and update line/column tracking
 * @param lex Lexer instance
 * @return Next character or '\0' if at end
 */
static char lexer_advance(lexer* lex) {
    if (lex->position >= lex->length) {
        return '\0';
    }
    
    char ch = lex->input[lex->position];
    lex->position++;
    
    if (ch == '\n') {
        lex->line++;
        lex->column = 1;
    } else {
        lex->column++;
    }
    
    return ch;
}

/**
 * @brief Peek at next character without advancing
 * @param lex Lexer instance
 * @return Next character or '\0' if at end
 */
static char lexer_peek_char(const lexer* lex) {
    if (lex->position + 1 >= lex->length) {
        return '\0';
    }
    return lex->input[lex->position + 1];
}

/**
 * @brief Skip whitespace characters but preserve newlines
 * @param lex Lexer instance
 */
static void lexer_skip_whitespace(lexer* lex) {
    while (lexer_current_char(lex) != '\0' && 
           isspace((unsigned char)lexer_current_char(lex)) && 
           lexer_current_char(lex) != '\n') {
        lexer_advance(lex);
    }
}

/**
 * @brief Check if string starts at current position
 * @param lex Lexer instance
 * @param str String to check
 * @return true if string matches at current position
 */
static bool lexer_starts_with(const lexer* lex, const char* str) {
    size_t len = strlen(str);
    if (lex->position + len > lex->length) {
        return false;
    }
    return strncmp(&lex->input[lex->position], str, len) == 0;
}

/**
 * @brief Extract a substring from lexer input
 * 
 * Extracts a substring from the lexer's input buffer starting at the given
 * position with the specified length. The returned string is null-terminated
 * and must be freed by the caller.
 * 
 * This function consolidates the duplicated malloc/memcpy pattern found
 * throughout the lexer code.
 * 
 * @param lex The lexer instance
 * @param start_pos Starting position in the input buffer
 * @param length Number of characters to extract
 * @return New substring on success, NULL if lex is NULL, position is invalid, or allocation fails
 */
static char* lexer_extract_substring(const lexer* lex, size_t start_pos, size_t length) {
    if (lex == NULL || lex->input == NULL) {
        return NULL;
    }
    
    // Check bounds
    if (start_pos >= lex->length) {
        return NULL;
    }
    
    // Adjust length if it extends beyond input
    size_t available = lex->length - start_pos;
    if (length > available) {
        length = available;
    }
    
    // Allocate memory for result
    char* result = malloc(length + 1);
    if (result == NULL) {
        return NULL;
    }
    
    // Copy substring
    memcpy(result, &lex->input[start_pos], length);
    result[length] = '\0';
    
    return result;
}

/**
 * @brief Read until end of line
 * @param lex Lexer instance
 * @return Line content (must be freed)
 */
static char* lexer_read_line(lexer* lex) {
    size_t start_pos = lex->position;
    
    // Find end of line
    while (lexer_current_char(lex) != '\0' && lexer_current_char(lex) != '\n') {
        lexer_advance(lex);
    }
    
    size_t length = lex->position - start_pos;
    return lexer_extract_substring(lex, start_pos, length);
}

/**
 * @brief Read HTML comment (including XMD directives)
 * @param lex Lexer instance
 * @return Comment content (must be freed)
 */
static char* lexer_read_html_comment(lexer* lex) {
    size_t start_pos = lex->position;
    
    // Skip opening <!--
    lexer_advance(lex); // <
    lexer_advance(lex); // !
    lexer_advance(lex); // -
    lexer_advance(lex); // -
    
    // Read until -->
    while (lexer_current_char(lex) != '\0') {
        if (lexer_starts_with(lex, "-->")) {
            lexer_advance(lex); // -
            lexer_advance(lex); // -
            lexer_advance(lex); // >
            break;
        }
        lexer_advance(lex);
    }
    
    size_t length = lex->position - start_pos;
    return lexer_extract_substring(lex, start_pos, length);
}

/**
 * @brief Read code block (``` or indented)
 * @param lex Lexer instance
 * @return Code block content (must be freed)
 */
static char* lexer_read_code_block(lexer* lex) {
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

/**
 * @brief Read variable reference {{var}}
 * @param lex Lexer instance
 * @return Variable reference (must be freed)
 */
static char* lexer_read_variable_ref(lexer* lex) {
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

/**
 * @brief Read inline XMD directive
 * @param lex Lexer instance
 * @return Directive content (must be freed)
 */
static char* lexer_read_xmd_directive(lexer* lex) {
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

/**
 * @brief Read text until special marker
 * @param lex Lexer instance
 * @return Text content (must be freed)
 */
static char* lexer_read_text(lexer* lex) {
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
        if (strstr(content, "xmd:") != NULL) {
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
    
    // Check for inline XMD directives
    if (lexer_starts_with(lex, "xmd:")) {
        char* content = lexer_read_xmd_directive(lex);
        return token_create(TOKEN_XMD_DIRECTIVE, content, token_line, token_column);
    }
    
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

/**
 * @brief Peek at next token without consuming it
 * @param lex Lexer instance
 * @return Copy of next token or NULL on error
 */
token* lexer_peek_token(lexer* lex) {
    if (lex == NULL) {
        return NULL;
    }
    
    if (lex->peeked_token == NULL) {
        lex->peeked_token = lexer_next_token(lex);
    }
    
    return token_copy(lex->peeked_token);
}

/**
 * @brief Get current position in input
 * @param lex Lexer instance
 * @return Current byte position in input
 */
size_t lexer_get_position(const lexer* lex) {
    return lex ? lex->position : 0;
}

/**
 * @brief Get current line number
 * @param lex Lexer instance
 * @return Current line number (1-based)
 */
size_t lexer_get_line(const lexer* lex) {
    return lex ? lex->line : 0;
}

/**
 * @brief Get current column number
 * @param lex Lexer instance
 * @return Current column number (1-based)
 */
size_t lexer_get_column(const lexer* lex) {
    return lex ? lex->column : 0;
}

/**
 * @brief Check if lexer has reached end of input
 * @param lex Lexer instance
 * @return true if at end of input
 */
bool lexer_at_end(const lexer* lex) {
    return lex ? (lex->position >= lex->length) : true;
}

/**
 * @brief Reset lexer to beginning of input
 * @param lex Lexer instance
 */
void lexer_reset(lexer* lex) {
    if (lex == NULL) {
        return;
    }
    
    lex->position = 0;
    lex->line = 1;
    lex->column = 1;
    
    if (lex->peeked_token != NULL) {
        token_free(lex->peeked_token);
        lex->peeked_token = NULL;
    }
}