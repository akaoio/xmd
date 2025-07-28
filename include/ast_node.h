/**
 * @file ast_node.h
 * @brief Abstract Syntax Tree node definitions for XMD language
 * @author XMD Team  
 * @date 2025-07-28
 */

#ifndef XMD_AST_NODE_H
#define XMD_AST_NODE_H

#include <stddef.h>
#include <stdbool.h>

/**
 * @brief Source location information for AST nodes
 * @struct source_location
 */
typedef struct {
    size_t line;             /**< Line number (1-based) */
    size_t column;           /**< Column number (1-based) */
    const char* filename;    /**< Source filename */
} source_location;

/**
 * @brief AST node types
 * @enum ast_node_type
 */
typedef enum {
    AST_PROGRAM,           /**< Root program node */
    AST_DIRECTIVE,         /**< XMD directive (set, if, exec, etc.) */
    AST_ASSIGNMENT,        /**< Variable assignment (=, +=) */
    AST_BINARY_OP,         /**< Binary operations (+, -, *, /, ==, !=, etc.) */
    AST_UNARY_OP,          /**< Unary operations (!, -) */
    AST_FUNCTION_CALL,     /**< Function calls (import, exec, print, etc.) */
    AST_VARIABLE_REF,      /**< Variable references */
    AST_LITERAL,           /**< String, number, boolean literals */
    AST_ARRAY_LITERAL,     /**< Array literals [1, 2, 3] */
    AST_CONDITIONAL,       /**< if/elif/else blocks */
    AST_LOOP,              /**< for loops */
    AST_BLOCK,             /**< Statement blocks */
    AST_IDENTIFIER         /**< Identifiers */
} ast_node_type;

/**
 * @brief Literal value types
 * @enum literal_type
 */
typedef enum {
    LITERAL_STRING,        /**< String literal */
    LITERAL_NUMBER,        /**< Number literal */
    LITERAL_BOOLEAN        /**< Boolean literal */
} literal_type;

/**
 * @brief Binary operator types
 * @enum binary_operator
 */
typedef enum {
    BINOP_ADD,             /**< + */
    BINOP_SUB,             /**< - */
    BINOP_MUL,             /**< * */
    BINOP_DIV,             /**< / */
    BINOP_EQ,              /**< == */
    BINOP_NE,              /**< != */
    BINOP_LT,              /**< < */
    BINOP_LE,              /**< <= */
    BINOP_GT,              /**< > */
    BINOP_GE,              /**< >= */
    BINOP_AND,             /**< && */
    BINOP_OR,              /**< || */
    BINOP_ASSIGN,          /**< = */
    BINOP_ASSIGN_ADD       /**< += */
} binary_operator;

/**
 * @brief Unary operator types
 * @enum unary_operator
 */
typedef enum {
    UNOP_NOT,              /**< ! */
    UNOP_MINUS             /**< - */
} unary_operator;

/**
 * @brief Forward declaration of AST node
 */
typedef struct ast_node ast_node;

/**
 * @brief AST node structure
 * @struct ast_node
 */
struct ast_node {
    ast_node_type type;           /**< Node type */
    source_location location;     /**< Source location */
    
    union {
        /**< Program node (list of statements) */
        struct {
            ast_node** statements;
            size_t statement_count;
        } program;
        
        /**< Directive node (command with arguments) */
        struct {
            char* command;           /**< "set", "if", "exec", etc. */
            ast_node** arguments;
            size_t argument_count;
        } directive;
        
        /**< Assignment node */
        struct {
            char* variable;
            binary_operator op;      /**< BINOP_ASSIGN or BINOP_ASSIGN_ADD */
            ast_node* value;
        } assignment;
        
        /**< Binary operation */
        struct {
            binary_operator op;
            ast_node* left;
            ast_node* right;
        } binary_op;
        
        /**< Unary operation */
        struct {
            unary_operator op;
            ast_node* operand;
        } unary_op;
        
        /**< Function call */
        struct {
            char* name;
            ast_node** arguments;
            size_t argument_count;
        } function_call;
        
        /**< Variable reference */
        struct {
            char* name;
        } variable_ref;
        
        /**< Literal value */
        struct {
            literal_type type;
            union {
                char* string_value;
                double number_value;
                bool boolean_value;
            } value;
        } literal;
        
        /**< Array literal */
        struct {
            ast_node** elements;
            size_t element_count;
        } array_literal;
        
        /**< Conditional (if/elif/else) */
        struct {
            ast_node* condition;     /**< NULL for else */
            ast_node* then_block;
            ast_node* else_block;    /**< Can chain elif/else */
        } conditional;
        
        /**< Loop (for) */
        struct {
            char* variable;          /**< Loop variable */
            ast_node* iterable;      /**< What to iterate over */
            ast_node* body;          /**< Loop body */
        } loop;
        
        /**< Block (list of statements) */
        struct {
            ast_node** statements;
            size_t statement_count;
        } block;
        
        /**< Identifier */
        struct {
            char* name;
        } identifier;
        
    } data;
};

/* AST node creation functions */
ast_node* ast_create_program(void);
ast_node* ast_create_directive(const char* command, source_location loc);
ast_node* ast_create_assignment(const char* variable, binary_operator op, ast_node* value, source_location loc);
ast_node* ast_create_binary_op(binary_operator op, ast_node* left, ast_node* right, source_location loc);
ast_node* ast_create_unary_op(unary_operator op, ast_node* operand, source_location loc);
ast_node* ast_create_function_call(const char* name, source_location loc);
ast_node* ast_create_variable_ref(const char* name, source_location loc);
ast_node* ast_create_string_literal(const char* value, source_location loc);
ast_node* ast_create_number_literal(double value, source_location loc);
ast_node* ast_create_boolean_literal(bool value, source_location loc);
ast_node* ast_create_array_literal(source_location loc);
ast_node* ast_create_conditional(ast_node* condition, source_location loc);
ast_node* ast_create_loop(const char* variable, ast_node* iterable, source_location loc);
ast_node* ast_create_block(source_location loc);
ast_node* ast_create_identifier(const char* name, source_location loc);

/* AST node manipulation functions */
int ast_add_argument(ast_node* node, ast_node* argument);
int ast_add_statement(ast_node* block, ast_node* statement);
int ast_add_element(ast_node* array, ast_node* element);

/* AST utility functions */
void ast_free(ast_node* node);
ast_node* ast_clone(const ast_node* node);
void ast_print(const ast_node* node, int indent);

/* String conversion utilities */
const char* ast_node_type_to_string(ast_node_type type);
const char* binary_operator_to_string(binary_operator op);
const char* unary_operator_to_string(unary_operator op);
binary_operator string_to_binary_operator(const char* str);

#endif /* XMD_AST_NODE_H */