/**
 * @file token_list_get.c
 * @brief Implementation of token_list_get function
 * 
 * This file contains ONLY the token_list_get function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/token.c
 */

#include <stddef.h>
#include "performance.h"
#include "token.h"
#include "utils.h"
#include "utils/common/common_macros.h"
/**
 * @brief Get token at specific index in list
 * @param list Token list head
 * @param index Index to retrieve (0-based)
 * @return Token at index or NULL if not found
 */
token* token_list_get(token* list, size_t index) {
    XMD_NULL_CHECK(list, NULL);
    
    token* current = list;
    size_t i = 0;
    while (current != NULL && i < index) {
        current = current->next;
        i++;
    }
    
    return current;
}
