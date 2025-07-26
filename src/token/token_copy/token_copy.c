/**
 * @file token_copy.c
 * @brief Token copy function
 * @author XMD Team
 *
 * Implementation of token copying for the XMD token system.
 */

#include "../../../include/token_internal.h"

/**
 * @brief Create a copy of a token (alias for token_duplicate)
 * @param t Token to copy
 * @return Copy of token or NULL if input is NULL
 */
token* token_copy(const token* t) {
    return token_duplicate(t);
}
