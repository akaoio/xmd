/**
 * @file ast_free.c
 * @brief Implementation of ast_free function
 * 
 * This file contains ONLY the ast_free function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "ast_node.h"
#include "variable.h"
/**
 * @brief Free AST node and all children
 * @param node Node to free (can be NULL)
 */
void ast_free(ast_node* node) {
    if (!node) {
        return;
    }
    
    switch (node->type) {
        case AST_PROGRAM:
            for (size_t i = 0; i < node->data.program.statement_count; i++) {
                ast_free(node->data.program.statements[i]);
            }
            free(node->data.program.statements);
            break;
            
        case AST_BLOCK:
            for (size_t i = 0; i < node->data.block.statement_count; i++) {
                ast_free(node->data.block.statements[i]);
            }
            free(node->data.block.statements);
            break;
            
        case AST_ASSIGNMENT:
            free(node->data.assignment.variable);
            ast_free(node->data.assignment.value);
            break;
            
        case AST_IDENTIFIER:
            free(node->data.identifier.name);
            break;
            
        case AST_LITERAL:
            if (node->data.literal.type == LITERAL_STRING) {
                free(node->data.literal.value.string_value);
            }
            break;
            
        case AST_BINARY_OP:
            ast_free(node->data.binary_op.left);
            ast_free(node->data.binary_op.right);
            break;
            
        case AST_FUNCTION_CALL:
            free(node->data.function_call.name);
            for (size_t i = 0; i < node->data.function_call.argument_count; i++) {
                ast_free(node->data.function_call.arguments[i]);
            }
            free(node->data.function_call.arguments);
            break;
            
        case AST_FUNCTION_DEF:
            free(node->data.function_def.name);
            for (size_t i = 0; i < node->data.function_def.parameter_count; i++) {
                free(node->data.function_def.parameters[i]);
            }
            free(node->data.function_def.parameters);
            ast_free(node->data.function_def.body);
            break;
            
        case AST_RETURN:
            ast_free(node->data.return_stmt.value);
            break;
            
        case AST_DIRECTIVE:
            free(node->data.directive.command);
            for (size_t i = 0; i < node->data.directive.argument_count; i++) {
                ast_free(node->data.directive.arguments[i]);
            }
            free(node->data.directive.arguments);
            break;
            
        case AST_UNARY_OP:
            ast_free(node->data.unary_op.operand);
            break;
            
        case AST_VARIABLE_REF:
            free(node->data.variable_ref.name);
            break;
            
        case AST_ARRAY_LITERAL:
            for (size_t i = 0; i < node->data.array_literal.element_count; i++) {
                ast_free(node->data.array_literal.elements[i]);
            }
            free(node->data.array_literal.elements);
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
            
        case AST_WHILE_LOOP:
            // While loops use the same structure as regular loops
            break;
            
        case AST_BREAK:
        case AST_CONTINUE:
            // Break and continue statements have no additional data to free
            break;
            
        case AST_CLASS_DEF:
            free(node->data.class_def.name);
            free(node->data.class_def.parent_class);
            ast_free(node->data.class_def.constructor);
            for (size_t i = 0; i < node->data.class_def.method_count; i++) {
                ast_free(node->data.class_def.methods[i]);
            }
            free(node->data.class_def.methods);
            break;
            
        case AST_METHOD_DEF:
            free(node->data.method_def.name);
            for (size_t i = 0; i < node->data.method_def.parameter_count; i++) {
                free(node->data.method_def.parameters[i]);
            }
            free(node->data.method_def.parameters);
            ast_free(node->data.method_def.body);
            break;
            
        default:
            break;
    }
    
    free(node);
}
