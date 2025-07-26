/**
 * @file token_list_free.c
 * @brief Token list deallocation function
 * @author XMD Team
 *
 * Implementation of token list memory cleanup for the XMD token system.
 */

#include "../../../include/token_internal.h"

/**
 * @brief Free entire token list
 * @param head Head of token list
 */
void token_list_free(token* head) {
    token* current = head;
    
    while (current != NULL) {
        token* next = current->next;
        token_free(current);
        current = next;
    }
}
