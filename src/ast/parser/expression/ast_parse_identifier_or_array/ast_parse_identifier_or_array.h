/**
 * @file ast_parse_identifier_or_array.h
 * @brief Header for ast_parse_identifier_or_array function
 * 
 * This file contains ONLY the declaration for ast_parse_identifier_or_array function.
 * One function per file - Genesis principle compliance.
 */

#ifndef AST_PARSE_IDENTIFIER_OR_ARRAY_H
#define AST_PARSE_IDENTIFIER_OR_ARRAY_H

#include "ast_node.h"
#include "ast_parser.h"

/**
 * @brief Parse identifier with optional array access (array[index])
 * @param identifier_str The identifier string to parse
 * @param loc Source location  
 * @return AST node (identifier or array access) or NULL on error
 */
ast_node* ast_parse_identifier_or_array(const char* identifier_str, source_location loc);

#endif /* AST_PARSE_IDENTIFIER_OR_ARRAY_H */