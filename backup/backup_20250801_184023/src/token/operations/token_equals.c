/**
 * @file token_equals.c
 * @brief Implementation of token_equals function
 * 
 * This file contains ONLY the token_equals function.
 * One function per file - Genesis principle compliance.
 * 
 * Extracted from: src/token.c
 */

#include <stdbool.h>
#include <string.h>

#include "performance.h"
#include "token.h"
#include "variable.h"

/**
 * @brief Check if two tokens are equal
 * @param tok1 First token
 * @param tok2 Second token
 * @return 1 if equal, 0 if not equal
 */

/**
 * @brief Check if two tokens are equal
 * @param tok1 First token
 * @param tok2 Second token
 * @return 1 if equal, 0 if not equal
 */
bool token_equals(const token* tok1, const token* tok2) {
    if (tok1 == tok2) {
        return true; // Same pointer or both NULL
    }
    
    if (tok1 == NULL || tok2 == NULL) {
        return false; // One is NULL, the other isn't
    }
    
    // Compare type, line, column
    if (tok1->type != tok2->type || 
        tok1->line != tok2->line || 
        tok1->column != tok2->column) {
        return false;
    }
    
    // Compare values
    if (tok1->value == tok2->value) {
        return true; // Same pointer or both NULL
    }
    
    if (tok1->value == NULL || tok2->value == NULL) {
        return false; // One is NULL, the other isn't
    }
    
    return strcmp(tok1->value, tok2->value) == 0;
}