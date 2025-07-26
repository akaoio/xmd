/**
 * @file token_list_get.c
 * @brief Token list getter function
 * @author XMD Team
 *
 * Implementation of token list element access for the XMD token system.
 */

#include "../../../include/token_internal.h"

/**
 * @brief Get token at index in list
 * @param head Head of token list
 * @param index Index (0-based)
 * @return Token at index or NULL if not found
 */
token* token_list_get(token* head, size_t index) {
    token* current = head;
    size_t i = 0;
    
    while (current != NULL && i < index) {
        current = current->next;
        i++;
    }
    
    return current;
}
