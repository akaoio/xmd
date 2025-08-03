
#ifndef XMD_AST_PARSER_H
#define XMD_AST_PARSER_H

#include "ast.h"
#include "token.h"

/* Forward declarations - parser_state is defined in ast.h */

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

/**
 * @brief Parse single value (string, number, identifier) without comma handling
 * @param pos Pointer to current position
 * @return Value AST node or NULL
 */
ast_node* ast_parse_single_value(const char** pos);

/**
 * @brief Parse object creation from comma-separated key-value pairs
 * @param pos Pointer to current position
 * @return Object AST node or NULL
 */
ast_node* ast_parse_object_creation(const char** pos, const char* first_name);

/**
 * @brief Parse assignment with Genesis comma disambiguation: set varname value
 * @param pos Pointer to current position
 * @return Assignment AST node or NULL (or program node for multiple assignments)
 */
ast_node* ast_parse_multiple_variables_handler(const char** pos, const char* first_name);

/**
 * @brief Parse identifier or array access (array[index])
 * @param identifier_str The identifier string to parse
 * @param loc Source location for AST nodes
 * @return AST node (identifier or array access)
 */
ast_node* ast_parse_identifier_or_array(const char* identifier_str, source_location loc);

/**
 * @brief Parse identifier or object property access (obj.property)
 * @param identifier_str The identifier string to parse
 * @param loc Source location for AST nodes
 * @return AST node (identifier or object access)
 */
ast_node* ast_parse_object_access(const char* identifier_str, source_location loc);

#endif /* XMD_AST_PARSER_H */
