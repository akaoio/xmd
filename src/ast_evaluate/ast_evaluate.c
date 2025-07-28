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
            
            // Handle different variable types
            switch (var->type) {
                case VAR_STRING: {
                    ast_value* value = ast_value_create(AST_VAL_STRING);
                    if (value) {
                        value->value.string_value = strdup(var->value.string_value);
                    }
                    return value;
                }
                case VAR_ARRAY: {
                    ast_value* value = ast_value_create(AST_VAL_ARRAY);
                    if (value) {
                        // Copy array elements from variable to AST value
                        value->value.array_value.element_count = var->value.array_value->count;
                        if (value->value.array_value.element_count > 0) {
                            value->value.array_value.elements = malloc(value->value.array_value.element_count * sizeof(ast_value*));
                            if (value->value.array_value.elements) {
                                for (size_t i = 0; i < value->value.array_value.element_count; i++) {
                                    variable* elem_var = var->value.array_value->items[i];
                                    if (elem_var && elem_var->type == VAR_STRING) {
                                        ast_value* elem_val = ast_value_create(AST_VAL_STRING);
                                        if (elem_val) {
                                            elem_val->value.string_value = strdup(elem_var->value.string_value);
                                            value->value.array_value.elements[i] = elem_val;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    return value;
                }
                default:
                    return NULL;
            }
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
            
        case AST_ARRAY_LITERAL: {
            ast_value* array_val = ast_value_create(AST_VAL_ARRAY);
            if (!array_val) {
                return NULL;
            }
            
            size_t element_count = node->data.array_literal.element_count;
            if (element_count > 0) {
                array_val->value.array_value.elements = malloc(element_count * sizeof(ast_value*));
                if (!array_val->value.array_value.elements) {
                    ast_value_free(array_val);
                    return NULL;
                }
                
                array_val->value.array_value.element_count = 0;
                
                for (size_t i = 0; i < element_count; i++) {
                    ast_value* elem_val = ast_evaluate(node->data.array_literal.elements[i], evaluator);
                    if (elem_val) {
                        array_val->value.array_value.elements[array_val->value.array_value.element_count++] = elem_val;
                    }
                }
            }
            
            return array_val;
        }
        
        case AST_ARRAY_ACCESS: {
            // Evaluate array expression
            ast_value* array_val = ast_evaluate(node->data.array_access.array_expr, evaluator);
            if (!array_val) {
                return NULL;
            }
            
            // Evaluate index expression
            ast_value* index_val = ast_evaluate(node->data.array_access.index_expr, evaluator);
            if (!index_val) {
                ast_value_free(array_val);
                return NULL;
            }
            
            // Check that array is actually an array
            if (array_val->type != AST_VAL_ARRAY) {
                ast_value_free(array_val);
                ast_value_free(index_val);
                return NULL;
            }
            
            // Check that index is a number
            if (index_val->type != AST_VAL_NUMBER) {
                ast_value_free(array_val);
                ast_value_free(index_val);
                return NULL;
            }
            
            // Get index as integer
            int index = (int)index_val->value.number_value;
            ast_value_free(index_val);
            
            // Check bounds
            if (index < 0 || (size_t)index >= array_val->value.array_value.element_count) {
                ast_value_free(array_val);
                return NULL;
            }
            
            // Get element at index
            ast_value* element = array_val->value.array_value.elements[index];
            ast_value* result = NULL;
            
            if (element) {
                // Create a copy of the element
                result = ast_value_create(element->type);
                if (result) {
                    switch (element->type) {
                        case AST_VAL_STRING:
                            result->value.string_value = strdup(element->value.string_value);
                            break;
                        case AST_VAL_NUMBER:
                            result->value.number_value = element->value.number_value;
                            break;
                        case AST_VAL_BOOLEAN:
                            result->value.boolean_value = element->value.boolean_value;
                            break;
                        case AST_VAL_ARRAY:
                            // For array copying, we'll just return NULL for now
                            ast_value_free(result);
                            result = NULL;
                            break;
                        case AST_VAL_NULL:
                            // NULL values don't need copying
                            break;
                    }
                }
            }
            
            ast_value_free(array_val);
            return result;
        }
            
        default:
            return NULL;
    }
}