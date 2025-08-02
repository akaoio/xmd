/**
 * @file ast_parser.h
 * @brief AST parser interface for XMD language
 * @author XMD Team
 * @date 2025-07-28
 */

#ifndef XMD_AST_PARSER_H
#define XMD_AST_PARSER_H

#include "ast_node.h"
#include "token.h"

/**
 * @brief Parser state structure
 */
typedef struct {
    token* tokens;           /**< Token stream from lexer */
    token* current_token;    /**< Current parsing position */
    size_t position;         /**< Current token index */
    const char* filename;    /**< Source filename for errors */
    bool has_error;          /**< Error flag */
    char* error_message;     /**< Last error message */
} parser_state;

/* Main parsing functions */

/**
 * @brief Parse program from source code string (REAL AST Parser per Genesis)
 * @param input Source code string
 * @return AST program node or NULL on error
 */
ast_node* ast_parse_program(const char* input);

/**
 * @brief Parse single statement
 * @param state Parser state
 * @return AST statement node or NULL on error
 */
ast_node* ast_parse_statement(parser_state* state);

/**
 * @brief Parse expression with precedence
 * @param state Parser state
 * @return AST expression node or NULL on error
 */
ast_node* ast_parse_expression(parser_state* state);

/**
 * @brief Parse assignment statement
 * @param state Parser state  
 * @return AST assignment node or NULL on error
 */
ast_node* ast_parse_assignment(parser_state* state);

/**
 * @brief Parse function call
 * @param state Parser state
 * @return AST function call node or NULL on error
 */
ast_node* ast_parse_function_call(parser_state* state);

/**
 * @brief Parse primary expression (literals, identifiers, parentheses)
 * @param state Parser state
 * @return AST primary expression node or NULL on error
 */
ast_node* ast_parse_primary(parser_state* state);

/* Parser state management */

/**
 * @brief Create parser state from token stream
 * @param tokens Token stream
 * @param filename Source filename
 * @return Parser state or NULL on error
 */
parser_state* parser_state_create(token* tokens, const char* filename);

/**
 * @brief Free parser state
 * @param state Parser state to free
 */
void parser_state_free(parser_state* state);

/**
 * @brief Advance to next token
 * @param state Parser state
 * @return Current token after advance
 */
token* parser_advance_token(parser_state* state);

/**
 * @brief Peek at current token without advancing
 * @param state Parser state
 * @return Current token
 */
token* parser_peek_token(parser_state* state);

/**
 * @brief Check if parser has encountered an error
 * @return true if error occurred, false otherwise
 */
bool parser_has_error(void);

/**
 * @brief Get last parser error message
 * @return Error message string or NULL
 */
const char* parser_get_error(void);

/**
 * @brief Set parser error with message
 * @param state Parser state
 * @param message Error message
 */
void parser_set_error(parser_state* state, const char* message);

#endif /* XMD_AST_PARSER_H */
