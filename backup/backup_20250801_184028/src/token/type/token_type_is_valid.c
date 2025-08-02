/**
 * @file token_type_is_valid.c
 * @brief Implementation of token_type_is_valid function
 * 
 * This file contains ONLY the token_type_is_valid function.
 * One function per file - Genesis principle compliance.
 * 
 * Extracted from: src/token.c
 */

#include <stdbool.h>

#include "token.h"
#include "variable.h"

/**
 * @brief Check if token type is valid
 * @param type Token type to validate
 * @return 1 if valid, 0 if invalid
 */

/**
 * @brief Check if token type is valid
 * @param type Token type to validate
 * @return 1 if valid, 0 if invalid
 */
bool token_type_is_valid(token_type type) {
    return type >= TOKEN_EOF && type <= TOKEN_COMMENT;
}