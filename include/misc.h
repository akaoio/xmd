/**
 * @file misc.h
 * @brief Forward declarations for misc module functions
 * 
 * Auto-generated during modular refactoring.
 * One function per file - Genesis principle compliance.
 */

#ifndef XMD_MISC_H
#define XMD_MISC_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used in this module */

/* Function declarations */
ast_node*ast_create_class_def(const char* name, const char* parent_class, source_location loc);
ast_node*ast_create_directive(const char* command, source_location loc);
ast_node*ast_create_file_delete(const char* file_path, source_location loc);
ast_node*ast_create_file_exists(const char* file_path, source_location loc);
ast_node*ast_create_file_list(const char* directory_path, source_location loc);
ast_node*ast_create_file_read(const char* file_path, source_location loc);
ast_node*ast_create_file_write(const char* file_path, ast_node* content, source_location loc);
ast_node*ast_create_method_def(const char* name, bool is_private, source_location loc);
ast_node*ast_create_return(ast_node* value, source_location loc);
ast_node*ast_create_unary_op(unary_operator op, ast_node* operand, source_location loc);
ast_node*ast_create_variable_ref(const char* name, source_location loc);
ast_value*ast_evaluate(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_block(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_break(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_continue(ast_node* node, ast_evaluator* evaluator);
ast_evaluator*ast_evaluator_create(store* variables, processor_context* ctx);
void ast_evaluator_free(ast_evaluator* evaluator);
void ast_functions_cleanup(void);
void ast_functions_init(void);
ast_node*ast_parse_conditional_simple(const char** pos);
ast_node*ast_parse_multiple_variables_handler(const char** pos, const char* first_name);
ast_node*ast_parse_object_creation(const char** pos, const char* obj_name);
ast_node*ast_parse_potential_function_call(const char** pos);
ast_node*ast_parse_print_simple(const char** pos);
ast_node*ast_parse_single_value(const char** pos);
char*ast_substitute_variables(const char* content, store* variables);
int ast_value_array_add(ast_value* array, ast_value* element);

#endif /* XMD_MISC_H */
