/**
 * @file token_duplicate.c
 * @brief Implementation of token_duplicate function
 * 
 * This file contains ONLY the token_duplicate function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/token.c
 */

#include "../../../../include/performance.h"
#include "../../../../include/token.h"
#include "../../../../include/token_internal.h"
#include "../../../../include/variable.h"
#include "../../../../include/utils.h"
#include "../../../utils/common/common_macros.h"
/**
 * @brief Duplicate a token
 * @param tok Token to duplicate
 * @return New token copy or NULL on error
 */
token* token_duplicate(const token* tok) {
    XMD_NULL_CHECK(tok, NULL);
    
    return token_create(tok->type, tok->value, tok->line, tok->column);
}
