/**
 * @file token_list_append.c
 * @brief Implementation of token_list_append function
 * 
 * This file contains ONLY the token_list_append function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/token.c
 */

#include "../../../../include/performance.h"
#include "../../../../include/token.h"
#include "../../../../include/utils.h"
#include "../../../utils/common/common_macros.h"
/**
 * @brief Append token to token list
 * @param head Head of the token list
 * @param t Token to append
 * @return Updated head of the list
 */
token* token_list_append(token* head, token* t) {
    XMD_NULL_CHECK_RETURN(t, head);
    
    t->next = NULL;
    if (head == NULL) {
        return t;
    }
    
    token* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = t;
    return head;
}
