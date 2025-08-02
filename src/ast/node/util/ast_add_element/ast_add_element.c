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
/**
 * @brief Add an element to an array literal
 * @param array Array literal node
 * @param element Element to add
 * @return 0 on success, -1 on error
 */
int ast_add_element(ast_node* array, ast_node* element) {
    if (!array || !element || array->type != AST_ARRAY_LITERAL) {
        return -1;
    }
    
    // Reallocate array
    ast_node** new_elements = xmd_realloc(array->data.array_literal.elements,
                                        (array->data.array_literal.element_count + 1) * sizeof(ast_node*));
    if (!new_elements) {
        return -1;
    }
    
    array->data.array_literal.elements = new_elements;
    array->data.array_literal.elements[array->data.array_literal.element_count] = element;
    array->data.array_literal.element_count++;
    return 0;
}
