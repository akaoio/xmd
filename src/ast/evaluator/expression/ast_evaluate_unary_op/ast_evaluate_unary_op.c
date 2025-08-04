/**
 * @file ast_evaluate_unary_op.c
 *
 * @brief Implementation of ast_evaluate_unary_op function
 * 
 * This file contains ONLY the ast_evaluate_unary_op function.
 * One function per file - Genesis principle compliance.
 * 
 * Handles unary operators like ! (NOT) and - (negation)
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ast.h"
#include "utils/common/validation_macros.h"

// Forward declarations
ast_value* ast_evaluate(ast_node* node, ast_evaluator* evaluator);

/**
 * @brief Evaluate unary operation
 * @param node Unary operation AST node
 * @param evaluator Evaluator context
 * @return AST value result or NULL on error
 */
ast_value* ast_evaluate_unary_op(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PTRS(NULL, node, evaluator);
    
    if (node->type != AST_UNARY_OP) {
        XMD_ERROR_RETURN(NULL, "Expected AST_UNARY_OP node, got type %d", node->type);
    }
    
    // Evaluate the operand
    ast_value* operand_value = ast_evaluate(node->data.unary_op.operand, evaluator);
    if (!operand_value) {
        XMD_ERROR_RETURN(NULL, "Failed to evaluate unary operand%s", "");
    }
    
    ast_value* result = NULL;
    
    switch (node->data.unary_op.op) {
        case UNOP_NOT: {
            // Logical NOT - convert operand to boolean and negate
            bool operand_bool = false;
            
            // Convert operand to boolean based on type
            switch (operand_value->type) {
                case AST_VAL_BOOLEAN:
                    operand_bool = operand_value->value.boolean_value;
                    break;
                case AST_VAL_NUMBER:
                    // 0 is false, non-zero is true
                    operand_bool = (operand_value->value.number_value != 0.0);
                    break;
                case AST_VAL_STRING:
                    // Empty string is false, non-empty is true
                    operand_bool = (operand_value->value.string_value != NULL && 
                                  operand_value->value.string_value[0] != '\0');
                    break;
                case AST_VAL_ARRAY:
                    // Non-empty array is true, empty array is false
                    operand_bool = (operand_value->value.array_value.element_count > 0);
                    break;
                default:
                    // Unknown types default to false
                    operand_bool = false;
                    break;
            }
            
            // Return negated boolean
            result = ast_value_create_boolean(!operand_bool);
            break;
        }
        
        case UNOP_MINUS: {
            // Numeric negation - only works on numbers
            if (operand_value->type != AST_VAL_NUMBER) {
                XMD_FREE_SAFE(operand_value);
                XMD_ERROR_RETURN(NULL, "Cannot apply unary minus to non-numeric value%s", "");
            }
            
            // Return negated number
            result = ast_value_create_number(-operand_value->value.number_value);
            break;
        }
        
        default:
            XMD_FREE_SAFE(operand_value);
            XMD_ERROR_RETURN(NULL, "Unknown unary operator: %d", node->data.unary_op.op);
    }
    
    // Clean up operand
    XMD_FREE_SAFE(operand_value);
    
    return result;
}