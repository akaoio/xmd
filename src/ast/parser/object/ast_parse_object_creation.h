/**
 * @file ast_parse_object_creation.h
 * @brief Declaration for ast_parse_object_creation function
 * 
 * This file contains ONLY the ast_parse_object_creation declaration.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_PARSE_OBJECT_CREATION_H
#define AST_PARSE_OBJECT_CREATION_H

#include <stddef.h>
#include <stdbool.h>

/* Forward declarations for types used */

typedef struct ast_node ast_node;
typedef struct ast_value ast_value;

/* Function declaration */
ast_node*ast_parse_object_creation(const char** pos, const char* obj_name);

#endif /* AST_PARSE_OBJECT_CREATION_H */
