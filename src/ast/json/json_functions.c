/**
 * @file json_functions.c
 * @brief JSON functions for XMD - DEPRECATED 
 * 
 * Genesis principle: Functions have been refactored into separate files
 * This file is now deprecated and functions have been moved to:
 * - json_escape_string/json_escape_string.c
 * - json_stringify_variable/json_stringify_variable.c
 * - json_parse_object/json_parse_object.c
 * - json_parse_array/json_parse_array.c
 * - json_parse_value/json_parse_value.c
 * - ast_json_stringify/ast_json_stringify.c
 * - ast_json_parse/ast_json_parse.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ast.h"
#include "store.h"
#include "variable.h"
#include "utils.h"

// Include headers for the separated functions
extern char* json_escape_string(const char* str);
extern char* json_stringify_variable(variable* var, bool pretty, int indent);
extern variable* json_parse_object(const char* json, size_t* pos);
extern variable* json_parse_array(const char* json, size_t* pos);
extern variable* json_parse_value(const char* json, size_t* pos);
extern ast_value* ast_json_stringify(ast_node** args, size_t arg_count, ast_evaluator* evaluator);
extern ast_value* ast_json_parse(ast_node** args, size_t arg_count, ast_evaluator* evaluator);

// This file is now empty - all functions have been moved to separate files
// following the Genesis principle (1 function per file)