/**
 * @file token_list_destroy.c
 * @brief Implementation of token_list_destroy function
 * 
 * This file contains ONLY the token_list_destroy function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/token.c
 */

#include <stdlib.h>
#include "performance.h"
#include "token.h"
#include "token_internal.h"
/**
 * @brief Destroy token list (alias for token_list_free)
 * @param list Token list head
 */
void token_list_destroy(token* list) {
    XMD_FREE_SAFE(list);
}
