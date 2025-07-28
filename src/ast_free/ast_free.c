/**
 * @file ast_free.c
 * @brief Free AST node and all its children
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdlib.h>
#include "../../include/ast_node.h"

/**
 * @brief Free AST node and all its children recursively
 * @param node Node to free (can be NULL)
 */
void ast_free(ast_node* node) {
    if (!node) {
        return;
    }
    
    switch (node->type) {
        case AST_PROGRAM:
            if (node->data.program.statements) {
                for (size_t i = 0; i < node->data.program.statement_count; i++) {
                    ast_free(node->data.program.statements[i]);
                }
                free(node->data.program.statements);
            }
            break;
            
        case AST_DIRECTIVE:
            free(node->data.directive.command);
            if (node->data.directive.arguments) {
                for (size_t i = 0; i < node->data.directive.argument_count; i++) {
                    ast_free(node->data.directive.arguments[i]);
                }
                free(node->data.directive.arguments);
            }
            break;
            
        case AST_ASSIGNMENT:
            free(node->data.assignment.variable);
            ast_free(node->data.assignment.value);
            break;
            
        case AST_BINARY_OP:
            ast_free(node->data.binary_op.left);
            ast_free(node->data.binary_op.right);
            break;
            
        case AST_UNARY_OP:
            ast_free(node->data.unary_op.operand);
            break;
            
        case AST_FUNCTION_CALL:
            free(node->data.function_call.name);
            if (node->data.function_call.arguments) {
                for (size_t i = 0; i < node->data.function_call.argument_count; i++) {
                    ast_free(node->data.function_call.arguments[i]);
                }
                free(node->data.function_call.arguments);
            }
            break;
            
        case AST_VARIABLE_REF:
            free(node->data.variable_ref.name);
            break;
            
        case AST_LITERAL:
            if (node->data.literal.type == LITERAL_STRING) {
                free(node->data.literal.value.string_value);
            }
            break;
            
        case AST_ARRAY_LITERAL:
            if (node->data.array_literal.elements) {
                for (size_t i = 0; i < node->data.array_literal.element_count; i++) {
                    ast_free(node->data.array_literal.elements[i]);
                }
                free(node->data.array_literal.elements);
            }
            break;
            
        case AST_ARRAY_ACCESS:
            ast_free(node->data.array_access.array_expr);
            ast_free(node->data.array_access.index_expr);
            break;
            
        case AST_CONDITIONAL:
            ast_free(node->data.conditional.condition);
            ast_free(node->data.conditional.then_block);
            ast_free(node->data.conditional.else_block);
            break;
            
        case AST_LOOP:
            free(node->data.loop.variable);
            ast_free(node->data.loop.iterable);
            ast_free(node->data.loop.body);
            break;
            
        case AST_BLOCK:
            if (node->data.block.statements) {
                for (size_t i = 0; i < node->data.block.statement_count; i++) {
                    ast_free(node->data.block.statements[i]);
                }
                free(node->data.block.statements);
            }
            break;
            
        case AST_IDENTIFIER:
            free(node->data.identifier.name);
            break;
    }
    
    free(node);
}