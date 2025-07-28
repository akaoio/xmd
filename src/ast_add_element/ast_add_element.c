/**
 * @file ast_add_element.c
 * @brief Add element to AST array literal node
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdlib.h>
#include "../../include/ast_node.h"

/**
 * @brief Add element to AST array literal node
 * @param array Array node
 * @param element Element to add (takes ownership)
 * @return 0 on success, -1 on error
 */
int ast_add_element(ast_node* array, ast_node* element) {
    if (!array || !element || array->type != AST_ARRAY_LITERAL) {
        return -1;
    }
    
    size_t new_count = array->data.array_literal.element_count + 1;
    ast_node** new_elements = realloc(array->data.array_literal.elements, 
                                      new_count * sizeof(ast_node*));
    if (!new_elements) {
        return -1;
    }
    
    new_elements[array->data.array_literal.element_count] = element;
    array->data.array_literal.elements = new_elements;
    array->data.array_literal.element_count = new_count;
    
    return 0;
}