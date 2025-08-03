/**
 * @file token_list_destroy.c
 * @brief Implementation of token_list_destroy function
 * 
 * This file contains ONLY the token_list_destroy function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/token.c
 */

#include <stdlib.h>
#include "../../../../include/token.h"
#include "../../../utils/common/common_macros.h"
/**
 * @brief Destroy token list (alias for token_list_free)
 * @param list Token list head
 */
void token_list_destroy(token* list) {
    // This should actually call token_list_free to properly free all tokens
    // For now, simple implementation
    if (list) {
        token* current = list;
        while (current) {
            token* next = current->next;
            if (current->value) {
                XMD_FREE_SAFE(current->value);
            }
            XMD_FREE_SAFE(current);
            current = next;
        }
    }
}
