/**
 * @file ast_create_file_write.h
 * @brief Declaration for ast_create_file_write function
 * 
 * This file contains ONLY the ast_create_file_write declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_CREATE_FILE_WRITE_H
#define AST_CREATE_FILE_WRITE_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
ast_node* ast_create_file_write(const char* file_path, ast_node* content, source_location loc);

#endif /* AST_CREATE_FILE_WRITE_H */
