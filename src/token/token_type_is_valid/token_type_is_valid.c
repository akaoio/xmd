/**
 * @file token_type_is_valid.c
 * @brief Token type validation function
 * @author XMD Team
 *
 * Implementation of token type validation for the XMD token system.
 */

#include "../../../include/token_internal.h"

/**
 * @brief Check if token type is valid
 * @param type Token type to validate
 * @return true if valid, false otherwise
 */
bool token_type_is_valid(token_type type) {
    return type >= TOKEN_TEXT && type <= TOKEN_EOF;
}
