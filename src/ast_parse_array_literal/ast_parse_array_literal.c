/**
 * @file ast_parse_array_literal.c
 * @brief AST-based array literal parser implementation
 * @author XMD Team
 * @date 2025-07-28
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include "../../include/ast_evaluator.h"
#include "../../include/ast_parser.h"
#include "../../include/lexer_enhanced.h"

/**
 * @brief Parse array literal using AST (replaces string-based parse_array_literal)
 * @param input Input string containing array literal like ["item1", "item2"]
 * @return Array variable or NULL on error
 */
variable* ast_parse_array_literal(const char* input) {
    if (!input) {
        return NULL;
    }
    
    // Tokenize the input
    token* tokens = lexer_enhanced_tokenize(input, "array_literal");
    if (!tokens) {
        return NULL;
    }
    
    // Parse into AST
    ast_node* ast = ast_parse_program(tokens);
    token_list_free(tokens);
    
    if (!ast || ast->type != AST_PROGRAM || ast->data.program.statement_count == 0) {
        ast_free(ast);
        return NULL;
    }
    
    // Get the first statement, which should be an array literal expression
    ast_node* expr = ast->data.program.statements[0];
    if (!expr || expr->type != AST_ARRAY_LITERAL) {
        ast_free(ast);
        return NULL;
    }
    
    // Create array variable
    variable* array = variable_create_array();
    if (!array) {
        ast_free(ast);
        return NULL;
    }
    
    // Process array elements
    for (size_t i = 0; i < expr->data.array_literal.element_count; i++) {
        ast_node* element = expr->data.array_literal.elements[i];
        if (!element) continue;
        
        variable* item = NULL;
        
        // Convert AST node to variable
        if (element->type == AST_LITERAL) {
            switch (element->data.literal.type) {
                case LITERAL_STRING:
                    item = variable_create_string(element->data.literal.value.string_value);
                    break;
                case LITERAL_NUMBER: {
                    char number_str[64];
                    snprintf(number_str, sizeof(number_str), "%.15g", element->data.literal.value.number_value);
                    item = variable_create_string(number_str);
                    break;
                }
                case LITERAL_BOOLEAN:
                    item = variable_create_string(element->data.literal.value.boolean_value ? "true" : "false");
                    break;
            }
        }
        
        if (item) {
            if (!variable_array_add(array, item)) {
                variable_unref(item);
                variable_unref(array);
                ast_free(ast);
                return NULL;
            }
            variable_unref(item); // Array took reference
        }
    }
    
    ast_free(ast);
    return array;
}