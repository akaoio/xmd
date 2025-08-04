/**
 * @file ast_evaluate_binary_op.c
 *
 *
 * @brief Implementation of ast_evaluate_binary_op function
 * 
 * This file contains ONLY the ast_evaluate_binary_op function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast_evaluator.h"
#include "ast_node.h"
#include "utils.h"
#include "variable.h"
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"
/**
 * @brief Evaluate binary operation node
 * @param node Binary operation AST node
 * @param evaluator Evaluator context
 * @return AST value result or NULL on error
 */
ast_value* ast_evaluate_binary_op(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PTRS(NULL, node, evaluator);
    XMD_VALIDATE_NODE_TYPE(node, AST_BINARY_OP, NULL, "ast_evaluate_binary_op: Invalid node type");
    
    // Evaluate left and right operands
    ast_value* left = ast_evaluate(node->data.binary_op.left, evaluator);
    ast_value* right = ast_evaluate(node->data.binary_op.right, evaluator);
    if (!left || !right) {
        XMD_FREE_SAFE(left);
        XMD_FREE_SAFE(right);
        XMD_ERROR_RETURN(NULL, "Failed to evaluate operands%s", "");
    }
    
    ast_value* result = NULL;
    // Perform operation based on operator
    switch (node->data.binary_op.op) {
        case BINOP_ADD:
            if (left->type == AST_VAL_NUMBER && right->type == AST_VAL_NUMBER) {
                double sum = left->value.number_value + right->value.number_value;
                result = ast_value_create_number(sum);
            } else if (left->type == AST_VAL_STRING && right->type == AST_VAL_STRING) {
                // String concatenation
                size_t len1 = strlen(left->value.string_value);
                size_t len2 = strlen(right->value.string_value);
                char* concat = xmd_malloc(len1 + len2 + 1);
                if (concat) {
                    // Safe string operations with explicit bounds
                    strncpy(concat, left->value.string_value, len1);
                    concat[len1] = '\0';
                    strncat(concat, right->value.string_value, len2);
                    result = ast_value_create_string(concat);
                    XMD_FREE_SAFE(concat);
                }
            } else if (left->type == AST_VAL_STRING || right->type == AST_VAL_STRING) {
                // Mixed type concatenation - USE MACRO INSTEAD OF BOILERPLATE
                char* left_str = NULL;
                char* right_str = NULL;
                
                XMD_CONVERT_VALUE_TO_STRING(left, left_str, NULL);
                XMD_CONVERT_VALUE_TO_STRING(right, right_str, NULL);
                
                if (left_str && right_str) {
                    size_t len1 = strlen(left_str);
                    size_t len2 = strlen(right_str);
                    size_t total_len = len1 + len2 + 1;
                    char* concat = xmd_malloc(total_len);
                    if (concat) {
                        // Safe string operations with explicit bounds
                        strncpy(concat, left_str, len1);
                        concat[len1] = '\0';
                        strncat(concat, right_str, len2);
                        result = ast_value_create_string(concat);
                        XMD_FREE_SAFE(concat);
                    }
                }
                XMD_FREE_SAFE(left_str);
                XMD_FREE_SAFE(right_str);
            }
            break;
        case BINOP_SUB:
            if (left->type == AST_VAL_NUMBER && right->type == AST_VAL_NUMBER) {
                double diff = left->value.number_value - right->value.number_value;
                result = ast_value_create_number(diff);
            } else {
                XMD_FREE_SAFE(left);
                XMD_FREE_SAFE(right);
                XMD_ERROR_RETURN(NULL, "ast_evaluate_binary_op: Type mismatch for subtraction - requires numbers, got %d and %d", left->type, right->type);
            }
            break;
        case BINOP_MUL:
            if (left->type == AST_VAL_NUMBER && right->type == AST_VAL_NUMBER) {
                double product = left->value.number_value * right->value.number_value;
                result = ast_value_create_number(product);
            } else {
                XMD_FREE_SAFE(left);
                XMD_FREE_SAFE(right);
                XMD_ERROR_RETURN(NULL, "ast_evaluate_binary_op: Type mismatch for multiplication - requires numbers, got %d and %d", left->type, right->type);
            }
            break;
        case BINOP_DIV:
            if (left->type == AST_VAL_NUMBER && right->type == AST_VAL_NUMBER) {
                if (right->value.number_value == 0.0) {
                    XMD_FREE_SAFE(left);
                    XMD_FREE_SAFE(right);
                    XMD_ERROR_RETURN(NULL, "%s", "ast_evaluate_binary_op: Division by zero error");
                }
                double quotient = left->value.number_value / right->value.number_value;
                result = ast_value_create_number(quotient);
            } else {
                XMD_FREE_SAFE(left);
                XMD_FREE_SAFE(right);
                XMD_ERROR_RETURN(NULL, "ast_evaluate_binary_op: Type mismatch for division - requires numbers, got %d and %d", left->type, right->type);
            }
            break;
        case BINOP_EQ:
            if (left->type == AST_VAL_NUMBER && right->type == AST_VAL_NUMBER) {
                bool equal = (left->value.number_value == right->value.number_value);
                result = ast_value_create_boolean(equal);
            } else if (left->type == AST_VAL_STRING && right->type == AST_VAL_STRING) {
                // USE MACRO INSTEAD OF BOILERPLATE
                bool equal = STR_EQUALS(left->value.string_value, right->value.string_value);
                result = ast_value_create_boolean(equal);
            } else if (left->type == AST_VAL_BOOLEAN && right->type == AST_VAL_BOOLEAN) {
                bool equal = (left->value.boolean_value == right->value.boolean_value);
                result = ast_value_create_boolean(equal);
            }
            break;
        case BINOP_NE:
            if (left->type == AST_VAL_NUMBER && right->type == AST_VAL_NUMBER) {
                bool not_equal = (left->value.number_value != right->value.number_value);
                result = ast_value_create_boolean(not_equal);
            } else if (left->type == AST_VAL_STRING && right->type == AST_VAL_STRING) {
                // USE MACRO INSTEAD OF BOILERPLATE
                bool not_equal = STR_NOT_EQUALS(left->value.string_value, right->value.string_value);
                result = ast_value_create_boolean(not_equal);
            } else if (left->type == AST_VAL_BOOLEAN && right->type == AST_VAL_BOOLEAN) {
                bool not_equal = (left->value.boolean_value != right->value.boolean_value);
                result = ast_value_create_boolean(not_equal);
            }
            break;
        case BINOP_LT:
            if (left->type == AST_VAL_NUMBER && right->type == AST_VAL_NUMBER) {
                bool less = (left->value.number_value < right->value.number_value);
                result = ast_value_create_boolean(less);
            }
            break;
        case BINOP_LE:
            if (left->type == AST_VAL_NUMBER && right->type == AST_VAL_NUMBER) {
                bool less_equal = (left->value.number_value <= right->value.number_value);
                result = ast_value_create_boolean(less_equal);
            }
            break;
        case BINOP_GT:
            if (left->type == AST_VAL_NUMBER && right->type == AST_VAL_NUMBER) {
                bool greater = (left->value.number_value > right->value.number_value);
                result = ast_value_create_boolean(greater);
            }
            break;
        case BINOP_GE:
            if (left->type == AST_VAL_NUMBER && right->type == AST_VAL_NUMBER) {
                bool greater_equal = (left->value.number_value >= right->value.number_value);
                result = ast_value_create_boolean(greater_equal);
            }
            break;
        default:
            break;
    }
    
    XMD_FREE_SAFE(left);
    XMD_FREE_SAFE(right);
    return result;
}
