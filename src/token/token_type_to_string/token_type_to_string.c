/**
 * @file token_type_to_string.c
 * @brief Token type string conversion function
 * @author XMD Team
 *
 * Implementation of token type to string conversion for the XMD token system.
 */

#include "../../../include/token_internal.h"

/**
 * @brief Convert token type to string
 * @param type Token type
 * @return String representation of token type
 */
const char* token_type_to_string(token_type type) {
    switch (type) {
        case TOKEN_TEXT:         return "TEXT";
        case TOKEN_HEADING:      return "HEADING";
        case TOKEN_LIST_ITEM:    return "LIST_ITEM";
        case TOKEN_CODE_BLOCK:   return "CODE_BLOCK";
        case TOKEN_HTML_COMMENT: return "HTML_COMMENT";
        case TOKEN_XMD_DIRECTIVE: return "XMD_DIRECTIVE";
        case TOKEN_VARIABLE_REF: return "VARIABLE_REF";
        case TOKEN_EOF:          return "EOF";
        default:                 return "UNKNOWN";
    }
}
