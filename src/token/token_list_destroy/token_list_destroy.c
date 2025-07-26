/**
 * @file token_list_destroy.c
 * @brief Token list destruction function
 * @author XMD Team
 *
 * Implementation of token list destruction for the XMD token system.
 */

#include "../../../include/token_internal.h"

/**
 * @brief Destroy entire token list (alias for token_list_free)
 * @param head Head of token list
 */
void token_list_destroy(token* head) {
    token_list_free(head);
}
