/**
 * @file token_list_reverse.c
 * @brief Implementation of token_list_reverse function
 * 
 * This file contains ONLY the token_list_reverse function.
 * One function per file - Genesis principle compliance.
 * 
 * Extracted from: src/token.c
 */

#include "performance.h"
#include "token.h"

/**
 * @brief Reverse token list in place
 * @param list Pointer to list head pointer
 * @return 0 on success, -1 on error
 */

/**
 * @brief Reverse token list in place
 * @param list Pointer to list head pointer
 * @return 0 on success, -1 on error
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