/**
 * @file ast_value_array_add.c
 * @brief Implementation of ast_value_array_add function
 * 
 * This file contains ONLY the ast_value_array_add function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include "ast.h"
#include "utils.h"
#include "utils/common/common_macros.h"
int ast_value_array_add(ast_value* array, ast_value* element) {
    XMD_NULL_CHECK_RETURN(array, -1);
    XMD_NULL_CHECK_RETURN(element, -1);
    if (array->type != AST_VAL_ARRAY) {
        return -1;
    }
    
    size_t new_count = array->value.array_value.element_count + 1;
    ast_value** new_elements = xmd_realloc(array->value.array_value.elements, 
                                           new_count * sizeof(ast_value*));
    XMD_NULL_CHECK_RETURN(new_elements, -1);
    new_elements[array->value.array_value.element_count] = element;
    array->value.array_value.elements = new_elements;
    array->value.array_value.element_count = new_count;
    return 0;
}
