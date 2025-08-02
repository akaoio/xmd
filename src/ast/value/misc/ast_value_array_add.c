/**
 * @file ast_value_array_add.c
 * @brief Implementation of ast_value_array_add function
 * 
 * This file contains ONLY the ast_value_array_add function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include "../../../../include/ast.h"
#include "../../../../include/utils.h"
int ast_value_array_add(ast_value* array, ast_value* element) {
    if (!array || array->type != AST_VAL_ARRAY || !element) {
        return -1;
    }
    
    size_t new_count = array->value.array_value.element_count + 1;
    ast_value** new_elements = xmd_realloc(array->value.array_value.elements, 
                                           new_count * sizeof(ast_value*));
    if (!new_elements) {
        return -1;
    }
    new_elements[array->value.array_value.element_count] = element;
    array->value.array_value.elements = new_elements;
    array->value.array_value.element_count = new_count;
    return 0;
}
