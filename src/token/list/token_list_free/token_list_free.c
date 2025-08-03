/**
 * @file token_list_free.c
 * @brief Implementation of token_list_free function
 * 
 * This file contains ONLY the token_list_free function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/token.c
 */

#include <stdlib.h>
#include "../../../../include/token.h"
#include "../../../utils/common/common_macros.h"
/**
 * @brief Free all tokens in list
 * @param list Token list head
 */
void token_list_free(token* list) {
    token* current = list;
    
    while (current != NULL) {
        token* next = current->next;
        if (current->value) {
            XMD_FREE_SAFE(current->value);
        }
        XMD_FREE_SAFE(current);
        current = next;
    }
}
