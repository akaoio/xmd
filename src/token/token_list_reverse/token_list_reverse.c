/**
 * @file token_list_reverse.c
 * @brief Token list reverse function
 * @author XMD Team
 *
 * Implementation of token list reversal for the XMD token system.
 */

#include "../../../include/token_internal.h"

/**
 * @brief Reverse token list
 * @param head Head of token list
 * @return New head of reversed list
 */
token* token_list_reverse(token* head) {
    token* prev = NULL;
    token* current = head;
    token* next = NULL;
    
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    
    return prev;
}
