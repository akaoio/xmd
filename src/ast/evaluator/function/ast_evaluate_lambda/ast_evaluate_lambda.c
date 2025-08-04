/**
 * @file ast_evaluate_lambda.c
 * @brief Implementation of ast_evaluate_lambda function
 * 
 * This file contains ONLY the ast_evaluate_lambda function.
 * One function per file - Genesis principle compliance.
 * Evaluates lambda function expressions
 */

#include <stdbool.h>
#include "ast.h"
#include "variable.h"
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Evaluate lambda function AST node
 * @param node Lambda AST node to evaluate
 * @param evaluator AST evaluator context
 * @return Lambda function object or NULL on error
 */
ast_value* ast_evaluate_lambda(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PARAMS_2(NULL, node, evaluator);
    XMD_AST_VALIDATE_TYPE(node, AST_LAMBDA, NULL, "ast_evaluate_lambda");
    
    // For now, lambdas are stored as string representations
    // A full implementation would create a callable function object
    
    // Create a string representation of the lambda
    char* lambda_str;
    size_t str_size = 256; // Initial buffer size
    XMD_MALLOC_VALIDATED(lambda_str, char, str_size, NULL);
    
    // Build parameter list
    strcpy(lambda_str, "(");
    FOR_EACH_INDEX(i, node->data.lambda.parameter_count) {
        if (i > 0) strcat(lambda_str, ", ");
        if (node->data.lambda.parameters[i]) {
            strcat(lambda_str, node->data.lambda.parameters[i]);
        }
    }
    strcat(lambda_str, ") => ");
    
    // For demonstration, add body type info
    switch (node->data.lambda.body->type) {
        case AST_BINARY_OP:
            strcat(lambda_str, "[binary expression]");
            break;
        case AST_IDENTIFIER:
            strcat(lambda_str, "[identifier]");
            break;
        case AST_LITERAL:
            strcat(lambda_str, "[literal]");
            break;
        default:
            strcat(lambda_str, "[expression]");
            break;
    }
    
    ast_value* result = ast_value_create_string(lambda_str);
    XMD_FREE_SAFE(lambda_str);
    
    return result;
}