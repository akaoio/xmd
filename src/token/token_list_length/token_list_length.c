/**
 * @file token_list_length.c
 * @brief Token list length function
 * @author XMD Team
 *
 * Implementation of token list length calculation for the XMD token system.
 */

#include "../../../include/token_internal.h"

/**
 * @brief Get length of token list
 * @param head Head of token list
 * @return Number of tokens in list
 */
size_t token_list_length(const token* head) {
    size_t count = 0;
    const token* current = head;
    
    while (current != NULL) {
        count++;
        current = current->next;
    }
    
    return count;
}
