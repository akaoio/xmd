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
/**
 * @brief Evaluate binary operation node
 * @param node Binary operation AST node
 * @param evaluator Evaluator context
 * @return AST value result or NULL on error
 */
ast_value* ast_evaluate_binary_op(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PTRS(NULL, node, evaluator);
    if (node->type != AST_BINARY_OP) {
        XMD_ERROR_RETURN(NULL, "Invalid node type: expected AST_BINARY_OP, got %d", node->type);
    }
    
    printf("DEBUG: ast_evaluate_binary_op called with op=%d\n", node->data.binary_op.op);
    // Evaluate left and right operands
    ast_value* left = ast_evaluate(node->data.binary_op.left, evaluator);
    ast_value* right = ast_evaluate(node->data.binary_op.right, evaluator);
    printf("DEBUG: Left operand type=%d, Right operand type=%d\n", 
           left ? left->type : -1, right ? right->type : -1);
    if (!left || !right) {
        XMD_FREE_SAFE(left);
        XMD_FREE_SAFE(right);
        XMD_ERROR_RETURN(NULL, "Failed to evaluate operands");
    }
    
    ast_value* result = NULL;
    // Perform operation based on operator
    switch (node->data.binary_op.op) {
        case BINOP_ADD:
            printf("DEBUG: Performing BINOP_ADD\n");
            if (left->type == AST_VAL_NUMBER && right->type == AST_VAL_NUMBER) {
                double sum = left->value.number_value + right->value.number_value;
                printf("DEBUG: Computing %f + %f = %f\n", left->value.number_value, right->value.number_value, sum);
                result = ast_value_create_number(sum);
            } else if (left->type == AST_VAL_STRING && right->type == AST_VAL_STRING) {
                // String concatenation
                size_t len1 = strlen(left->value.string_value);
                size_t len2 = strlen(right->value.string_value);
                char* concat = xmd_malloc(len1 + len2 + 1);
                if (concat) {
                    strcpy(concat, left->value.string_value);
                    strcat(concat, right->value.string_value);
                    result = ast_value_create_string(concat);
                    XMD_FREE_SAFE(concat);
                    printf("DEBUG: String concat: '%s' + '%s' = '%s'\n", 
                           left->value.string_value, right->value.string_value, 
                           result ? result->value.string_value : "NULL");
                }
            } else if (left->type == AST_VAL_STRING || right->type == AST_VAL_STRING) {
                // Mixed type concatenation - convert to strings
                char* left_str = NULL;
                char* right_str = NULL;
                
                if (left->type == AST_VAL_STRING) {
                    left_str = xmd_strdup(left->value.string_value);
                } else if (left->type == AST_VAL_NUMBER) {
                    left_str = xmd_malloc(32);
                    if (left_str) snprintf(left_str, 32, "%g", left->value.number_value);
                } else if (left->type == AST_VAL_BOOLEAN) {
                    left_str = xmd_strdup(left->value.boolean_value ? "true" : "false");
                }
                
                if (right->type == AST_VAL_STRING) {
                    right_str = xmd_strdup(right->value.string_value);
                } else if (right->type == AST_VAL_NUMBER) {
                    right_str = xmd_malloc(32);
                    if (right_str) snprintf(right_str, 32, "%g", right->value.number_value);
                } else if (right->type == AST_VAL_BOOLEAN) {
                    right_str = xmd_strdup(right->value.boolean_value ? "true" : "false");
                }
                
                if (left_str && right_str) {
                    size_t total_len = strlen(left_str) + strlen(right_str) + 1;
                    char* concat = xmd_malloc(total_len);
                    if (concat) {
                        strcpy(concat, left_str);
                        strcat(concat, right_str);
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
            }
            break;
        case BINOP_MUL:
            if (left->type == AST_VAL_NUMBER && right->type == AST_VAL_NUMBER) {
                double product = left->value.number_value * right->value.number_value;
                result = ast_value_create_number(product);
            }
            break;
        case BINOP_DIV:
            if (left->type == AST_VAL_NUMBER && right->type == AST_VAL_NUMBER) {
                if (right->value.number_value != 0.0) {
                    double quotient = left->value.number_value / right->value.number_value;
                    result = ast_value_create_number(quotient);
                }
            }
            break;
        case BINOP_EQ:
            printf("DEBUG: Performing BINOP_EQ comparison\n");
            if (left->type == AST_VAL_NUMBER && right->type == AST_VAL_NUMBER) {
                bool equal = (left->value.number_value == right->value.number_value);
                printf("DEBUG: Comparing numbers %f == %f = %s\n", 
                       left->value.number_value, right->value.number_value, equal ? "true" : "false");
                result = ast_value_create_boolean(equal);
            } else if (left->type == AST_VAL_STRING && right->type == AST_VAL_STRING) {
                bool equal = (strcmp(left->value.string_value, right->value.string_value) == 0);
                printf("DEBUG: Comparing strings '%s' == '%s' = %s\n", 
                       left->value.string_value, right->value.string_value, equal ? "true" : "false");
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
                bool not_equal = (strcmp(left->value.string_value, right->value.string_value) != 0);
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
            printf("DEBUG: Unsupported binary operator: %d\n", node->data.binary_op.op);
            break;
    }
    
    XMD_FREE_SAFE(left);
    XMD_FREE_SAFE(right);
    return result;
}
