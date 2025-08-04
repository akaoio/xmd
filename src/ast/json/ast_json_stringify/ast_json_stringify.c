/**
 * @file ast_json_stringify.c
 * @brief AST function: json.stringify(object)
 * 
 * Genesis principle: One function per file
 * This file contains only the ast_json_stringify function
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ast.h"
#include "store.h"
#include "variable.h"
#include "utils.h"

// Forward declaration for json_stringify_variable
extern char* json_stringify_variable(variable* var, bool pretty, int indent);

/**
 * @brief AST function: json.stringify(object)
 * @param args Function arguments (1 expected)
 * @param arg_count Number of arguments
 * @param evaluator Evaluator context
 * @return JSON string as ast_value
 */
ast_value* ast_json_stringify(ast_node** args, size_t arg_count, ast_evaluator* evaluator) {
    if (arg_count != 1) {
        return ast_value_create_string("");
    }
    
    // Evaluate the argument
    ast_value* arg_val = ast_evaluate(args[0], evaluator);
    if (!arg_val) {
        return ast_value_create_string("");
    }
    
    // Convert to variable
    variable* var = ast_value_to_variable(arg_val);
    if (arg_val) {
        ast_value_free(arg_val);
    }
    
    if (!var) {
        return ast_value_create_string("");
    }
    
    // Stringify to JSON
    char* json = json_stringify_variable(var, false, 0);
    variable_unref(var);
    
    if (!json) {
        return ast_value_create_string("");
    }
    
    // Create result
    ast_value* result = ast_value_create_string(json);
    if (json) {
        free(json);
    }
    return result;
}
