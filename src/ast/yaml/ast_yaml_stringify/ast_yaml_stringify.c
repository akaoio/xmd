/**
 * @file ast_yaml_stringify.c
 * @brief AST function: yaml.stringify(object) (Genesis principle: 1 function per file)
 * 
 * This file contains the main AST function for YAML stringification.
 * Part of the YAML processing module for XMD.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "store.h"
#include "variable.h"
#include "utils.h"
#include "utils/common/common_macros.h"

// Function declaration for the helper function
char* yaml_stringify_variable(variable* var, int indent);

/**
 * @brief AST function: yaml.stringify(object)
 * @param args Function arguments (1 expected)
 * @param arg_count Number of arguments
 * @param evaluator Evaluator context
 * @return YAML string as ast_value
 */
ast_value* ast_yaml_stringify(ast_node** args, size_t arg_count, ast_evaluator* evaluator) {
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
    XMD_FREE_SAFE(arg_val);
    
    if (!var) {
        return ast_value_create_string("");
    }
    
    // Stringify to YAML
    char* yaml = yaml_stringify_variable(var, 0);
    variable_unref(var);
    
    if (!yaml) {
        return ast_value_create_string("");
    }
    
    // Create result
    ast_value* result = ast_value_create_string(yaml);
    XMD_FREE_SAFE(yaml);
    return result;
}
