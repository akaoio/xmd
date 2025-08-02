/**
 * @file token_list_length.c
 * @brief Implementation of token_list_length function
 * 
 * This file contains ONLY the token_list_length function.
 * One function per file - Genesis principle compliance.
 * 
 * Extracted from: src/token.c
 */

#include <stddef.h>

#include "performance.h"
#include "token.h"

/**
 * @brief Get length of token list
 * @param list Token list head
 * @return Number of tokens in list
 */

/**
 * @brief Get length of token list
 * @param list Token list head
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