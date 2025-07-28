/**
 * @file lexer_enhanced.c
 * @brief Enhanced lexer for XMD expression parsing
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../include/lexer_enhanced.h"
#include "../../include/token.h"

/**
 * @brief Check if character is valid identifier start
 * @param c Character to check
 * @return true if valid identifier start, false otherwise
 */
bool is_identifier_start(char c) {
    return isalpha(c) || c == '_';
}

/**
 * @brief Check if character is valid identifier continuation
 * @param c Character to check
 * @return true if valid identifier continuation, false otherwise
 */
bool is_identifier_continue(char c) {
    return isalnum(c) || c == '_';
}

/**
 * @brief Check if character is digit
 * @param c Character to check
 * @return true if digit, false otherwise
 */
bool is_digit(char c) {
    return isdigit(c);
}

/**
 * @brief Check if character is whitespace
 * @param c Character to check
 * @return true if whitespace, false otherwise
 */
bool is_whitespace(char c) {
    return isspace(c);
}

/**
 * @brief Check if string is boolean literal
 * @param str String to check
 * @return true if boolean literal, false otherwise
 */
bool is_boolean_literal(const char* str) {
    return (strcmp(str, "true") == 0) || (strcmp(str, "false") == 0);
}

/**
 * @brief Get operator token from string
 * @param input Input string starting at operator
 * @param length Output parameter for operator length
 * @return Operator string, or NULL if not an operator
 */
const char* get_operator(const char* input, int* length) {
    if (!input || !length) {
        return NULL;
    }
    
    // Two-character operators first
    if (strncmp(input, "==", 2) == 0) { *length = 2; return "=="; }
    if (strncmp(input, "!=", 2) == 0) { *length = 2; return "!="; }
    if (strncmp(input, "<=", 2) == 0) { *length = 2; return "<="; }
    if (strncmp(input, ">=", 2) == 0) { *length = 2; return ">="; }
    if (strncmp(input, "&&", 2) == 0) { *length = 2; return "&&"; }
    if (strncmp(input, "||", 2) == 0) { *length = 2; return "||"; }
    if (strncmp(input, "+=", 2) == 0) { *length = 2; return "+="; }
    
    // Single-character operators
    switch (input[0]) {
        case '+': *length = 1; return "+";
        case '-': *length = 1; return "-";
        case '*': *length = 1; return "*";
        case '/': *length = 1; return "/";
        case '<': *length = 1; return "<";
        case '>': *length = 1; return ">";
        case '=': *length = 1; return "=";
        case '!': *length = 1; return "!";
        default: return NULL;
    }
}

/**
 * @brief Tokenize input string with enhanced expression support
 * @param input Input string to tokenize
 * @param filename Source filename for location tracking
 * @return Linked list of tokens, or NULL on error
 */
token* lexer_enhanced_tokenize(const char* input, const char* filename) {
    if (!input) {
        return NULL;
    }
    
    if (strlen(input) == 0) {
        return token_create(TOKEN_EOF, "", 1, 1);
    }
    
    token* head = NULL;
    token* current = NULL;
    size_t pos = 0;
    size_t line = 1;
    size_t column = 1;
    size_t len = strlen(input);
    
    while (pos < len) {
        char c = input[pos];
        
        // Skip whitespace
        if (is_whitespace(c)) {
            if (c == '\n') {
                line++;
                column = 1;
            } else {
                column++;
            }
            pos++;
            continue;
        }
        
        token* new_token = NULL;
        
        // Operators (multi-character first)
        int op_len = 0;
        const char* op = get_operator(&input[pos], &op_len);
        if (op) {
            new_token = token_create(TOKEN_OPERATOR, op, line, column);
            pos += op_len;
            column += op_len;
        }
        // String literals
        else if (c == '"' || c == '\'') {
            char quote = c;
            size_t start = pos + 1;
            pos++;
            column++;
            
            while (pos < len && input[pos] != quote) {
                pos++;
                column++;
            }
            
            if (pos < len) {
                size_t str_len = pos - start;
                char* str_value = malloc(str_len + 1);
                if (str_value) {
                    strncpy(str_value, &input[start], str_len);
                    str_value[str_len] = '\0';
                    new_token = token_create(TOKEN_STRING, str_value, line, column - str_len - 1);
                    free(str_value);
                }
                pos++;
                column++;
            }
        }
        // Numbers  
        else if (is_digit(c)) {
            size_t start = pos;
            while (pos < len && (is_digit(input[pos]) || input[pos] == '.')) {
                pos++;
                column++;
            }
            
            size_t num_len = pos - start;
            char* num_value = malloc(num_len + 1);
            if (num_value) {
                strncpy(num_value, &input[start], num_len);
                num_value[num_len] = '\0';
                new_token = token_create(TOKEN_NUMBER, num_value, line, column - num_len);
                free(num_value);
            }
        }
        // Identifiers and keywords
        else if (is_identifier_start(c)) {
            size_t start = pos;
            while (pos < len && is_identifier_continue(input[pos])) {
                pos++;
                column++;
            }
            
            size_t id_len = pos - start;
            char* identifier = malloc(id_len + 1);
            if (identifier) {
                strncpy(identifier, &input[start], id_len);
                identifier[id_len] = '\0';
                
                token_type type = is_boolean_literal(identifier) ? TOKEN_BOOLEAN : TOKEN_IDENTIFIER;
                new_token = token_create(type, identifier, line, column - id_len);
                free(identifier);
            }
        }
        // XMD directive detection
        else if (pos + 8 < len && strncmp(&input[pos], "<!-- xmd:", 9) == 0) {
            size_t start = pos;
            // Find end of directive
            while (pos + 2 < len && strncmp(&input[pos], "-->", 3) != 0) {
                pos++;
                column++;
            }
            if (pos + 2 < len) {
                pos += 3; // Skip -->
                column += 3;
            }
            
            size_t dir_len = pos - start;
            char* directive = malloc(dir_len + 1);
            if (directive) {
                strncpy(directive, &input[start], dir_len);
                directive[dir_len] = '\0';
                new_token = token_create(TOKEN_XMD_DIRECTIVE, directive, line, column - dir_len);
                free(directive);
            }
        }
        // Single character tokens
        else if (c == '(') { new_token = token_create(TOKEN_LPAREN, "(", line, column); pos++; column++; }
        else if (c == ')') { new_token = token_create(TOKEN_RPAREN, ")", line, column); pos++; column++; }
        else if (c == '[') { new_token = token_create(TOKEN_LBRACKET, "[", line, column); pos++; column++; }
        else if (c == ']') { new_token = token_create(TOKEN_RBRACKET, "]", line, column); pos++; column++; }
        else if (c == ',') { new_token = token_create(TOKEN_COMMA, ",", line, column); pos++; column++; }
        else if (c == ';') { new_token = token_create(TOKEN_SEMICOLON, ";", line, column); pos++; column++; }
        else {
            // Skip unknown character
            pos++;
            column++;
            continue;
        }
        
        // Add token to list
        if (new_token) {
            if (!head) {
                head = current = new_token;
            } else {
                current->next = new_token;
                current = new_token;
            }
        }
    }
    
    // Add EOF token
    token* eof = token_create(TOKEN_EOF, "", line, column);
    if (eof) {
        if (!head) {
            head = eof;
        } else {
            current->next = eof;
        }
    }
    
    return head;
}