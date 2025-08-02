/**
 * @file token_list_append.c
 * @brief Implementation of token_list_append function
 * 
 * This file contains ONLY the token_list_append function.
 * One function per file - Genesis principle compliance.
 * 
 * Extracted from: src/token.c
 */

#include "performance.h"
#include "token.h"

/**
 * @brief Append token to token list
 * @param list Pointer to list head pointer
 * @param tok Token to append
 * @return 0 on success, -1 on error
 */

/**
 * @brief Append token to token list
 * @param list Pointer to list head pointer
 * @param tok Token to append
 * @return 0 on success, -1 on error
 */
token* token_list_append(token* head, token* t) {
    if (t == NULL) {
        return head;
    }
    
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