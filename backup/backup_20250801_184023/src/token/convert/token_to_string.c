/**
 * @file token_to_string.c
 * @brief Implementation of token_to_string function
 * 
 * This file contains ONLY the token_to_string function.
 * One function per file - Genesis principle compliance.
 * 
 * Extracted from: src/token.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "performance.h"
#include "token.h"
#include "token_internal.h"
#include "utils.h"
#include "variable.h"

/**
 * @brief Convert token to string representation
 * @param tok Token to convert
 * @return String representation or NULL on error
 */

/**
 * @brief Convert token to string representation
 * @param tok Token to convert
 * @return String representation or NULL on error
 */
char* token_to_string(const token* tok) {
    if (tok == NULL) {
        return xmd_strdup("NULL");
    }
    
    const char* type_str = token_type_to_string(tok->type);
    const char* value_str = tok->value ? tok->value : "";
    
    // Estimate size: type + value + formatting + null terminator
    size_t size = strlen(type_str) + strlen(value_str) + 50;
    char* result = xmd_malloc(size);
    if (result == NULL) {
        return NULL;
    }
    
    snprintf(result, size, "Token{type=%s, value=\"%s\", line=%zu, column=%zu}", 
             type_str, value_str, tok->line, tok->column);
    
    return result;
}