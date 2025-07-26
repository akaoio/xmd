/**
 * @file token_list_append.c
 * @brief Token list append function
 * @author XMD Team
 *
 * Implementation of token list append operation for the XMD token system.
 */

#include "../../../include/token_internal.h"

/**
 * @brief Append token to end of token list
 * @param head Head of token list (can be NULL)
 * @param t Token to append
 * @return New head of list
 */
token* token_list_append(token* head, token* t) {
    if (t == NULL) {
        return head;
    }
    
    if (head == NULL) {
        return t;
    }
    
    // Find end of list
    token* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = t;
    t->next = NULL;
    
    return head;
}
