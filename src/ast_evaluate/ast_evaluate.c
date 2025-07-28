/**
 * @file ast_evaluate.c
 * @brief Evaluate AST node
 * @author XMD Team
 * @date 2025-07-28
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include "../../include/ast_evaluator.h"

/**
 * @brief Evaluate AST node
 * @param node AST node to evaluate
 * @param evaluator Evaluator context
 * @return AST value result or NULL on error
 */
ast_value* ast_evaluate(ast_node* node, ast_evaluator* evaluator) {
    if (!node || !evaluator) {
        return NULL;
    }
    
    switch (node->type) {
        case AST_LITERAL: {
            ast_value* value = NULL;
            switch (node->data.literal.type) {
                case LITERAL_STRING:
                    value = ast_value_create(AST_VAL_STRING);
                    if (value) {
                        value->value.string_value = strdup(node->data.literal.value.string_value);
                    }
                    break;
                case LITERAL_NUMBER:
                    value = ast_value_create(AST_VAL_NUMBER);
                    if (value) {
                        value->value.number_value = node->data.literal.value.number_value;
                    }
                    break;
                case LITERAL_BOOLEAN:
                    value = ast_value_create(AST_VAL_BOOLEAN);
                    if (value) {
                        value->value.boolean_value = node->data.literal.value.boolean_value;
                    }
                    break;
            }
            return value;
        }
        
        case AST_VARIABLE_REF: {
            variable* var = store_get(evaluator->variables, node->data.variable_ref.name);
            if (!var) {
                return NULL;
            }
            
            ast_value* value = ast_value_create(AST_VAL_STRING);
            if (value && var->type == VAR_STRING) {
                value->value.string_value = strdup(var->value.string_value);
            }
            return value;
        }
        
        case AST_BINARY_OP: {
            ast_value* left = ast_evaluate(node->data.binary_op.left, evaluator);
            ast_value* right = ast_evaluate(node->data.binary_op.right, evaluator);
            
            if (!left || !right) {
                ast_value_free(left);
                ast_value_free(right);
                return NULL;
            }
            
            ast_value* result = NULL;
            
            // Handle numeric operations
            if (left->type == AST_VAL_NUMBER && right->type == AST_VAL_NUMBER) {
                switch (node->data.binary_op.op) {
                    case BINOP_ADD:
                        result = ast_value_create(AST_VAL_NUMBER);
                        if (result) result->value.number_value = left->value.number_value + right->value.number_value;
                        break;
                    case BINOP_SUB:
                        result = ast_value_create(AST_VAL_NUMBER);
                        if (result) result->value.number_value = left->value.number_value - right->value.number_value;
                        break;
                    case BINOP_MUL:
                        result = ast_value_create(AST_VAL_NUMBER);
                        if (result) result->value.number_value = left->value.number_value * right->value.number_value;
                        break;
                    case BINOP_DIV:
                        result = ast_value_create(AST_VAL_NUMBER);
                        if (result) result->value.number_value = left->value.number_value / right->value.number_value;
                        break;
                    case BINOP_EQ:
                        result = ast_value_create(AST_VAL_BOOLEAN);
                        if (result) result->value.boolean_value = (left->value.number_value == right->value.number_value);
                        break;
                    default:
                        break;
                }
            }
            // Handle string operations
            else if (left->type == AST_VAL_STRING && right->type == AST_VAL_STRING) {
                switch (node->data.binary_op.op) {
                    case BINOP_ADD:
                        result = ast_value_create(AST_VAL_STRING);
                        if (result) {
                            size_t len = strlen(left->value.string_value) + strlen(right->value.string_value) + 1;
                            result->value.string_value = malloc(len);
                            if (result->value.string_value) {
                                snprintf(result->value.string_value, len, "%s%s", left->value.string_value, right->value.string_value);
                            }
                        }
                        break;
                    case BINOP_EQ:
                        result = ast_value_create(AST_VAL_BOOLEAN);
                        if (result) {
                            result->value.boolean_value = (strcmp(left->value.string_value, right->value.string_value) == 0);
                        }
                        break;
                    case BINOP_NE:
                        result = ast_value_create(AST_VAL_BOOLEAN);
                        if (result) {
                            result->value.boolean_value = (strcmp(left->value.string_value, right->value.string_value) != 0);
                        }
                        break;
                    default:
                        break;
                }
            }
            
            ast_value_free(left);
            ast_value_free(right);
            return result;
        }
        
        case AST_FUNCTION_CALL:
            return ast_evaluate_function_call(node, evaluator);
            
        default:
            return NULL;
    }
}