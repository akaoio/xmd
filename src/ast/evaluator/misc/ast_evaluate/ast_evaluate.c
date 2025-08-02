/**
 * @file ast_evaluate.c
 * @brief Implementation of ast_evaluate function
 * 
 * This file contains ONLY the ast_evaluate function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "ast_evaluator.h"
#include "ast_node.h"
#include "error.h"
#include "module.h"
#include "variable.h"

// Forward declaration for string interpolation
extern char* ast_interpolate_string(const char* str, ast_evaluator* evaluator);

/**
 * @brief Evaluate AST node
 * @param node Node to evaluate
 * @param evaluator Evaluator context
 * @return Result value or NULL on error
 */
ast_value* ast_evaluate(ast_node* node, ast_evaluator* evaluator) {
    if (!node || !evaluator) {
        return NULL;
    }
    
    switch (node->type) {
        case AST_PROGRAM:
            return ast_evaluate_program_node(node, evaluator);
            
        case AST_BLOCK:
            return ast_evaluate_block(node, evaluator);
            
        case AST_ASSIGNMENT: {
            // FIXED: Return the assigned value instead of boolean success
            printf("DEBUG: Evaluating assignment node\n");
            
            // Use the existing assignment evaluation which handles everything
            int result = ast_evaluate_assignment(node, evaluator);
            if (result != 0) {
                return NULL;
            }
            
            // Re-evaluate to get the return value (for now, could be optimized later)
            ast_value* assigned_value = ast_evaluate(node->data.assignment.value, evaluator);
            
            // Return the assigned value instead of boolean true
            printf("DEBUG: Assignment successful, returning computed value\n");
            return assigned_value;
        }
            
        case AST_IDENTIFIER:
            return ast_evaluate_identifier(node, evaluator);
            
        case AST_LITERAL:
            switch (node->data.literal.type) {
                case LITERAL_NUMBER:
                    return ast_value_create_number(node->data.literal.value.number_value);
                case LITERAL_STRING: {
                    // Apply string interpolation for ${var} syntax
                    char* interpolated = ast_interpolate_string(node->data.literal.value.string_value, evaluator);
                    if (interpolated) {
                        ast_value* result = ast_value_create_string(interpolated);
                        free(interpolated);
                        return result;
                    } else {
                        return ast_value_create_string(node->data.literal.value.string_value);
                    }
                }
                case LITERAL_BOOLEAN:
                    return ast_value_create_boolean(node->data.literal.value.boolean_value);
            }
            return NULL;
            
        case AST_BINARY_OP:
            return ast_evaluate_binary_op(node, evaluator);
            
        case AST_FUNCTION_CALL:
            return ast_evaluate_function_call(node, evaluator);
            
        case AST_FUNCTION_DEF:
            // Function definitions don't return a value, they define functions
            // Store function in evaluator context for later calls
            return ast_evaluate_function_def(node, evaluator);
            
        case AST_RETURN:
            // Evaluate return value
            if (node->data.return_stmt.value) {
                return ast_evaluate(node->data.return_stmt.value, evaluator);
            } else {
                return ast_value_create_string(""); // Empty return
            }
            
        case AST_CLASS_DEF:
            // Class definitions don't return a value, they register classes
            printf("DEBUG: Evaluating class definition: %s\n", node->data.class_def.name);
            if (node->data.class_def.parent_class) {
                printf("DEBUG: Extends: %s\n", node->data.class_def.parent_class);
            }
            printf("DEBUG: Methods: %zu\n", node->data.class_def.method_count);
            // Store class in evaluator context for instantiation
            return ast_value_create_boolean(true);
            
        case AST_METHOD_DEF:
            // Method definitions are handled within class context
            return ast_value_create_boolean(true);
            
        case AST_CONDITIONAL:
            return ast_evaluate_conditional(node, evaluator);
            
        case AST_LOOP:
            return ast_evaluate_loop(node, evaluator);
            
        case AST_WHILE_LOOP:
            return ast_evaluate_while_loop(node, evaluator);
            
        case AST_BREAK:
            return ast_evaluate_break(node, evaluator);
            
        case AST_CONTINUE:
            return ast_evaluate_continue(node, evaluator);
            
        case AST_FILE_READ:
            return ast_evaluate_file_read(node, evaluator);
            
        case AST_FILE_WRITE:
            return ast_evaluate_file_write(node, evaluator);
            
        case AST_FILE_EXISTS:
            return ast_evaluate_file_exists(node, evaluator);
            
        case AST_FILE_DELETE:
            return ast_evaluate_file_delete(node, evaluator);
            
        case AST_FILE_LIST:
            return ast_evaluate_file_list(node, evaluator);
            
        case AST_ARRAY_LITERAL: {
            printf("DEBUG: Evaluating array literal with %zu elements\n", node->data.array_literal.element_count);
            // Create array value
            ast_value* array_val = ast_value_create_array();
            if (!array_val) {
                return NULL;
            }
            
            // Evaluate each element and add to array
            for (size_t i = 0; i < node->data.array_literal.element_count; i++) {
                ast_value* elem_val = ast_evaluate(node->data.array_literal.elements[i], evaluator);
                if (!elem_val) {
                    // Clean up on error
                    for (size_t j = 0; j < array_val->value.array_value.element_count; j++) {
                        ast_value_free(array_val->value.array_value.elements[j]);
                    }
                    free(array_val->value.array_value.elements);
                    free(array_val);
                    return NULL;
                }
                
                if (ast_value_array_add(array_val, elem_val) != 0) {
                    // Clean up on error
                    ast_value_free(elem_val);
                    for (size_t j = 0; j < array_val->value.array_value.element_count; j++) {
                        ast_value_free(array_val->value.array_value.elements[j]);
                    }
                    free(array_val->value.array_value.elements);
                    free(array_val);
                    return NULL;
                }
            }
            
            return array_val;
        }
            
        default:
            return NULL;
    }
}