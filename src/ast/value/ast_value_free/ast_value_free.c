/**
 * @file ast_value_free.c
 * @brief Implementation of ast_value_free function
 * 
 * This file contains ONLY the ast_value_free function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include <stdbool.h>
#include "ast.h"
#include "utils.h"
void ast_value_free(ast_value* val) {
    if (!val) return;
    
    switch (val->type) {
        case AST_VAL_STRING:
            free(val->value.string_value);
            break;
            
        case AST_VAL_ARRAY:
            // Free all elements
            for (size_t i = 0; i < val->value.array_value.element_count; i++) {
                ast_value_free(val->value.array_value.elements[i]);
            }
            free(val->value.array_value.elements);
        default:
    }
    free(val);
}
