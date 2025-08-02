
#ifndef XMD_AST_NODE_H
#define XMD_AST_NODE_H

#include "ast.h"

ast_node* ast_clone(const ast_node* node);
void ast_print(const ast_node* node, int indent);

/* String conversion utilities */
const char* ast_node_type_to_string(ast_node_type type);
const char* binary_operator_to_string(binary_operator op);
const char* unary_operator_to_string(unary_operator op);
binary_operator string_to_binary_operator(const char* str);

#endif /* XMD_AST_NODE_H */
