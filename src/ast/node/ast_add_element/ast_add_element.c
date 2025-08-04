/**
 * @file ast_add_element.c
 * @brief Implementation of ast_add_element function
 * 
 * This file contains ONLY the ast_add_element function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include "ast_node.h"
#include "variable.h"
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"
/**
 * @brief Add an element to an array literal
 * @param array Array literal node
 * @param element Element to add
 * @return 0 on success, -1 on error
 */
int ast_add_element(ast_node* array, ast_node* element) {
    XMD_VALIDATE_PTRS_RETVAL(-1, array, element);
    XMD_AST_VALIDATE_TYPE(array, AST_ARRAY_LITERAL, -1, "array element addition");
    
    size_t old_count = array->data.array_literal.element_count;
    size_t new_count = old_count + 1;
    
    XMD_AST_ARRAY_RESIZE(array->data.array_literal.elements, old_count, new_count, ast_node*, -1);
    
    array->data.array_literal.elements[old_count] = element;
    array->data.array_literal.element_count = new_count;
    return 0;
}
