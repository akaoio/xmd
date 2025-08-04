/**
 * @file ast_json_parse.c
 * @brief AST function: json.parse(string)
 * 
 * Genesis principle: One function per file
 * This file contains only the ast_json_parse function
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ast.h"
#include "store.h"
#include "variable.h"
#include "utils.h"

// Forward declaration for json_parse_value
extern variable* json_parse_value(const char* json, size_t* pos);

/**
 * @brief AST function: json.parse(string)
 * @param args Function arguments (1 expected)
 * @param arg_count Number of arguments
 * @param evaluator Evaluator context
 * @return Parsed object as ast_value
 */
ast_value* ast_json_parse(ast_node** args, size_t arg_count, ast_evaluator* evaluator) {
    if (arg_count != 1) {
        return ast_value_create_string("");
    }
    
    // Evaluate the argument
    ast_value* arg_val = ast_evaluate(args[0], evaluator);
    if (!arg_val || arg_val->type != AST_VAL_STRING) {
        if (arg_val) ast_value_free(arg_val);
        return ast_value_create_string("");
    }
    
    // Parse JSON
    size_t pos = 0;
    variable* var = json_parse_value(arg_val->value.string_value, &pos);
    ast_value_free(arg_val);
    
    if (!var) {
        return ast_value_create_string("");
    }
    
    // Convert to ast_value
    ast_value* result = ast_value_from_variable(var);
    variable_unref(var);
    
    return result ? result : ast_value_create_string("");
}
