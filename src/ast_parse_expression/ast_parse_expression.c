/**
 * @file ast_parse_expression.c
 * @brief Parse expression with precedence
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdlib.h>
#include <string.h>
#include "../../include/ast_parser.h"
#include "../../include/ast_node.h"

/**
 * @brief Get operator precedence (higher number = higher precedence)
 * @param op_str Operator string
 * @return Precedence level (0 = not an operator)
 */
static int get_precedence(const char* op_str) {
    if (!op_str) return 0;
    
    if (strcmp(op_str, "||") == 0) return 1;
    if (strcmp(op_str, "&&") == 0) return 2;
    if (strcmp(op_str, "==") == 0 || strcmp(op_str, "!=") == 0) return 3;
    if (strcmp(op_str, "<") == 0 || strcmp(op_str, ">") == 0 ||
        strcmp(op_str, "<=") == 0 || strcmp(op_str, ">=") == 0) return 4;
    if (strcmp(op_str, "+") == 0 || strcmp(op_str, "-") == 0) return 5;
    if (strcmp(op_str, "*") == 0 || strcmp(op_str, "/") == 0) return 6;
    
    return 0;
}

/**
 * @brief Convert operator string to binary_operator enum
 * @param op_str Operator string
 * @return Binary operator enum
 */
static binary_operator string_to_binop(const char* op_str) {
    if (strcmp(op_str, "+") == 0) return BINOP_ADD;
    if (strcmp(op_str, "-") == 0) return BINOP_SUB;
    if (strcmp(op_str, "*") == 0) return BINOP_MUL;
    if (strcmp(op_str, "/") == 0) return BINOP_DIV;
    if (strcmp(op_str, "==") == 0) return BINOP_EQ;
    if (strcmp(op_str, "!=") == 0) return BINOP_NE;
    if (strcmp(op_str, "<") == 0) return BINOP_LT;
    if (strcmp(op_str, "<=") == 0) return BINOP_LE;
    if (strcmp(op_str, ">") == 0) return BINOP_GT;
    if (strcmp(op_str, ">=") == 0) return BINOP_GE;
    if (strcmp(op_str, "&&") == 0) return BINOP_AND;
    if (strcmp(op_str, "||") == 0) return BINOP_OR;
    return BINOP_ADD; // Default
}

/**
 * @brief Parse expression with precedence climbing
 * @param state Parser state
 * @param min_prec Minimum precedence level
 * @return AST expression node or NULL on error
 */
static ast_node* parse_expression_prec(parser_state* state, int min_prec) {
    ast_node* left = ast_parse_primary(state);
    if (!left) {
        return NULL;
    }
    
    while (true) {
        token* op_tok = parser_peek_token(state);
        if (!op_tok || op_tok->type != TOKEN_OPERATOR) {
            break;
        }
        
        int prec = get_precedence(op_tok->value);
        if (prec < min_prec) {
            break;
        }
        
        source_location loc = {op_tok->line, op_tok->column, state->filename};
        binary_operator op = string_to_binop(op_tok->value);
        parser_advance_token(state); // Skip operator
        
        ast_node* right = parse_expression_prec(state, prec + 1);
        if (!right) {
            ast_free(left);
            return NULL;
        }
        
        ast_node* binary_op_node = ast_create_binary_op(op, left, right, loc);
        if (!binary_op_node) {
            ast_free(left);
            ast_free(right);
            return NULL;
        }
        
        left = binary_op_node;
    }
    
    return left;
}

/**
 * @brief Parse expression with precedence
 * @param state Parser state
 * @return AST expression node or NULL on error
 */
ast_node* ast_parse_expression(parser_state* state) {
    return parse_expression_prec(state, 1);
}