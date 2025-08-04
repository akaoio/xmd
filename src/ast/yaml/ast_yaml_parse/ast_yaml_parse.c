/**
 * @file ast_yaml_parse.c
 * @brief AST function: yaml.parse(string) (Genesis principle: 1 function per file)
 * 
 * This file contains the main AST function for YAML parsing.
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
variable* yaml_parse_simple(const char* yaml);

/**
 * @brief AST function: yaml.parse(string)
 * @param args Function arguments (1 expected)
 * @param arg_count Number of arguments
 * @param evaluator Evaluator context
 * @return Parsed object as ast_value
 */
ast_value* ast_yaml_parse(ast_node** args, size_t arg_count, ast_evaluator* evaluator) {
    if (arg_count != 1) {
        return ast_value_create_string("");
    }
    
    // Evaluate the argument
    ast_value* arg_val = ast_evaluate(args[0], evaluator);
    if (!arg_val || arg_val->type != AST_VAL_STRING) {
        if (arg_val) XMD_FREE_SAFE(arg_val);
        return ast_value_create_string("");
    }
    
    // Parse YAML
    variable* var = yaml_parse_simple(arg_val->value.string_value);
    XMD_FREE_SAFE(arg_val);
    
    if (!var) {
        return ast_value_create_string("");
    }
    
    // Convert to ast_value
    ast_value* result = ast_value_from_variable(var);
    variable_unref(var);
    
    return result ? result : ast_value_create_string("");
}
