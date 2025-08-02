/**
 * @file lexer_enhanced.h
 * @brief Enhanced lexer for XMD expression parsing
 * @author XMD Team
 * @date 2025-07-28
 */

#ifndef XMD_LEXER_ENHANCED_H
#define XMD_LEXER_ENHANCED_H

#include "token.h"

/**
 * @brief Tokenize input string with enhanced expression support
 * @param input Input string to tokenize
 * @param filename Source filename for location tracking
 * @return Linked list of tokens, or NULL on error
 */
token* lexer_enhanced_tokenize(const char* input, const char* filename);

/**
 * @brief Check if character is valid identifier start
 * @param c Character to check
 * @return true if valid identifier start, false otherwise
 */
bool is_identifier_start(char c);

/**
 * @brief Check if character is valid identifier continuation
 * @param c Character to check
 * @return true if valid identifier continuation, false otherwise
 */
bool is_identifier_continue(char c);

/**
 * @brief Check if character is digit
 * @param c Character to check
 * @return true if digit, false otherwise
 */
bool is_digit(char c);

/**
 * @brief Check if character is whitespace
 * @param c Character to check
 * @return true if whitespace, false otherwise
 */
bool is_whitespace(char c);

/**
 * @brief Check if string is boolean literal
 * @param str String to check
 * @return true if boolean literal, false otherwise
 */
bool is_boolean_literal(const char* str);

/**
 * @brief Get operator token from string
 * @param input Input string starting at operator
 * @param length Output parameter for operator length
 * @return Operator string, or NULL if not an operator
 */
const char* get_operator(const char* input, int* length);

#endif /* XMD_LEXER_ENHANCED_H */
