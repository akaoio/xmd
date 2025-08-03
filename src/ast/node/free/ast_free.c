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
#include "utils/common/common_macros.h"
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
                XMD_FREE_SAFE(node->data.program.statements[i]);
            }
            XMD_FREE_SAFE(node->data.program.statements);
            break;
            
        case AST_BLOCK:
            for (size_t i = 0; i < node->data.block.statement_count; i++) {
                XMD_FREE_SAFE(node->data.block.statements[i]);
            }
            XMD_FREE_SAFE(node->data.block.statements);
            break;
            
        case AST_ASSIGNMENT:
            XMD_FREE_SAFE(node->data.assignment.variable);
            XMD_FREE_SAFE(node->data.assignment.value);
            break;
            
        case AST_IDENTIFIER:
            XMD_FREE_SAFE(node->data.identifier.name);
            break;
            
        case AST_LITERAL:
            if (node->data.literal.type == LITERAL_STRING) {
                XMD_FREE_SAFE(node->data.literal.value.string_value);
            }
            break;
            
        case AST_BINARY_OP:
            XMD_FREE_SAFE(node->data.binary_op.left);
            XMD_FREE_SAFE(node->data.binary_op.right);
            break;
            
        case AST_FUNCTION_CALL:
            XMD_FREE_SAFE(node->data.function_call.name);
            for (size_t i = 0; i < node->data.function_call.argument_count; i++) {
                XMD_FREE_SAFE(node->data.function_call.arguments[i]);
            }
            XMD_FREE_SAFE(node->data.function_call.arguments);
            break;
            
        case AST_FUNCTION_DEF:
            XMD_FREE_SAFE(node->data.function_def.name);
            for (size_t i = 0; i < node->data.function_def.parameter_count; i++) {
                XMD_FREE_SAFE(node->data.function_def.parameters[i]);
            }
            XMD_FREE_SAFE(node->data.function_def.parameters);
            XMD_FREE_SAFE(node->data.function_def.body);
            break;
            
        case AST_RETURN:
            XMD_FREE_SAFE(node->data.return_stmt.value);
            break;
            
        case AST_DIRECTIVE:
            XMD_FREE_SAFE(node->data.directive.command);
            for (size_t i = 0; i < node->data.directive.argument_count; i++) {
                XMD_FREE_SAFE(node->data.directive.arguments[i]);
            }
            XMD_FREE_SAFE(node->data.directive.arguments);
            break;
            
        case AST_UNARY_OP:
            XMD_FREE_SAFE(node->data.unary_op.operand);
            break;
            
        case AST_VARIABLE_REF:
            XMD_FREE_SAFE(node->data.variable_ref.name);
            break;
            
        case AST_ARRAY_LITERAL:
            for (size_t i = 0; i < node->data.array_literal.element_count; i++) {
                XMD_FREE_SAFE(node->data.array_literal.elements[i]);
            }
            XMD_FREE_SAFE(node->data.array_literal.elements);
            break;
            
        case AST_ARRAY_ACCESS:
            XMD_FREE_SAFE(node->data.array_access.array_expr);
            XMD_FREE_SAFE(node->data.array_access.index_expr);
            break;
            
        case AST_CONDITIONAL:
            XMD_FREE_SAFE(node->data.conditional.condition);
            XMD_FREE_SAFE(node->data.conditional.then_block);
            XMD_FREE_SAFE(node->data.conditional.else_block);
            break;
            
        case AST_LOOP:
            XMD_FREE_SAFE(node->data.loop.variable);
            XMD_FREE_SAFE(node->data.loop.iterable);
            XMD_FREE_SAFE(node->data.loop.body);
            break;
            
        case AST_WHILE_LOOP:
            // While loops use the same structure as regular loops
            break;
            
        case AST_BREAK:
        case AST_CONTINUE:
            // Break and continue statements have no additional data to free
            break;
            
        case AST_CLASS_DEF:
            XMD_FREE_SAFE(node->data.class_def.name);
            XMD_FREE_SAFE(node->data.class_def.parent_class);
            XMD_FREE_SAFE(node->data.class_def.constructor);
            for (size_t i = 0; i < node->data.class_def.method_count; i++) {
                XMD_FREE_SAFE(node->data.class_def.methods[i]);
            }
            XMD_FREE_SAFE(node->data.class_def.methods);
            break;
            
        case AST_METHOD_DEF:
            XMD_FREE_SAFE(node->data.method_def.name);
            for (size_t i = 0; i < node->data.method_def.parameter_count; i++) {
                XMD_FREE_SAFE(node->data.method_def.parameters[i]);
            }
            XMD_FREE_SAFE(node->data.method_def.parameters);
            XMD_FREE_SAFE(node->data.method_def.body);
            break;
            
        default:
            break;
    }
    
    XMD_FREE_SAFE(node);
}
