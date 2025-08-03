/**
 * @file token_free.c
 * @brief Implementation of token_free function
 * 
 * This file contains ONLY the token_free function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/token.c
 */

#include <stdlib.h>
#include "../../../include/token.h"
#include "../../../include/utils.h"
#include "../../utils/common/common_macros.h"
/**
 * @brief Free a token and its resources
 * @param tok Token to free (can be NULL)
 */
void token_free(token* tok) {
    if (!tok) return;
    
    XMD_FREE_SAFE(tok->value);
    XMD_FREE_SAFE(tok);
}
