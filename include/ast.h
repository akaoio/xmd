/**
 * @file ast.h
 * @brief Abstract Syntax Tree node definitions for XMD language
 * @author XMD Team  
 * @date 2025-07-28
 */

#ifndef XMD_AST_H
#define XMD_AST_H

#include <stddef.h>
#include <stdbool.h>
#include "variable.h"
#include "store.h"
#include "utils.h"
#include "token.h"
#include "xmd_processor_internal.h"

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
    AST_ARRAY_ACCESS,      /**< Array indexing array[index] */
    AST_OBJECT_ACCESS,     /**< Object property access obj.property */
    AST_CONDITIONAL,       /**< if/elif/else blocks */
    AST_LOOP,              /**< for loops */
    AST_BLOCK,             /**< Statement blocks */
    AST_FUNCTION_DEF,      /**< Function definitions */
    AST_RETURN,            /**< Return statements */
    AST_IDENTIFIER,        /**< Identifiers */
    AST_CLASS_DEF,         /**< Class definitions */
    AST_METHOD_DEF,        /**< Method definitions within classes */
    AST_WHILE_LOOP,        /**< While loops */
    AST_BREAK,             /**< Break statements */
    AST_CONTINUE,          /**< Continue statements */
    AST_FILE_READ,         /**< File.read operations */
    AST_FILE_WRITE,        /**< File.write operations */
    AST_FILE_EXISTS,       /**< File.exists operations */
    AST_FILE_DELETE,       /**< File.delete operations */
    AST_FILE_LIST,         /**< File.list operations */
    AST_TRY_CATCH,         /**< Try-catch error handling */
    AST_THROW,             /**< Throw statements */
    AST_TERNARY,           /**< Ternary operator condition ? true : false */
    AST_LAMBDA,            /**< Lambda functions (x => x * 2) */
    AST_STRING_METHOD,     /**< String method calls (str.upper, str.split) */
    AST_LOOP_TIMES,        /**< loop N times */
    AST_FOR_RANGE,         /**< for i in 1..5 */
    AST_FOR_INDEXED,       /**< for i, item in array */
    AST_AWAIT,             /**< await expression */
    AST_IMPORT,            /**< import statement */
    AST_DESTRUCTURE,       /**< destructuring assignment */
    AST_SPREAD,            /**< spread operator */
    AST_GENERATOR_DEF,     /**< generator function definition (function*) */
    AST_YIELD              /**< yield statement */
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
/**
 * @brief Forward declarations
 */
typedef struct ast_node ast_node;
typedef struct ast_value ast_value;
typedef struct ast_evaluator ast_evaluator;

/**
 * @brief Parser state structure
 */
typedef struct parser_state {
    token* tokens;               /**< Original token list */
    token* current_token;        /**< Current token position */
    size_t position;             /**< Current position index */
    bool has_error;              /**< Error flag */
    char* error_message;         /**< Error message */
    const char* filename;        /**< Source filename */
} parser_state;

/**
 * @brief AST evaluation result value
 */
struct ast_value {
    enum { 
        AST_VAL_STRING, 
        AST_VAL_NUMBER, 
        AST_VAL_BOOLEAN,
        AST_VAL_ARRAY,
        AST_VAL_NULL
    } type;
    union {
        char* string_value;
        double number_value;
        bool boolean_value;
        struct {
            ast_value** elements;
            size_t element_count;
        } array_value;
    } value;
};

/**
 * @brief AST evaluator context
 */
struct ast_evaluator {
    store* variables;              /**< Variable storage */
    store* functions;              /**< Function storage */
    void* ctx;                     /**< XMD processor context */
    char* output_buffer;          /**< Output accumulator */
    size_t output_size;           /**< Current buffer usage */
    size_t output_capacity;       /**< Buffer capacity */
    bool has_error;               /**< Error flag */
    char* error_message;          /**< Error details */
    bool in_statement_context;    /**< True when evaluating a statement (not expression) */
};

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
        
        /**< Array access */
        struct {
            ast_node* array_expr;    /**< Array expression */
            ast_node* index_expr;    /**< Index expression */
        } array_access;
        
        /**< Object property access */
        struct {
            ast_node* object_expr;   /**< Object expression */
            char* property_name;     /**< Property name to access */
        } object_access;
        
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
        
        /**< Function definition */
        struct {
            char* name;              /**< Function name */
            char** parameters;       /**< Parameter names */
            size_t parameter_count;  /**< Number of parameters */
            ast_node* body;          /**< Function body */
            bool is_async;           /**< true for async functions */ 
        } function_def;
        
        /**< Return statement */
        struct {
            ast_node* value;         /**< Return value expression (NULL for empty return) */
        } return_stmt;
        
        /**< Identifier */
        struct {
            char* name;
        } identifier;
        
        /**< Class definition */
        struct {
            char* name;              /**< Class name */
            char* parent_class;      /**< Parent class name (NULL if no inheritance) */
            ast_node* constructor;   /**< Constructor method */
            ast_node** methods;      /**< Array of method definitions */
            size_t method_count;     /**< Number of methods */
        } class_def;
        
        /**< Method definition */
        struct {
            char* name;              /**< Method name */
            char** parameters;       /**< Parameter names */
            size_t parameter_count;  /**< Number of parameters */
            ast_node* body;          /**< Method body */
            bool is_private;         /**< true for private methods */
        } method_def;
        
        /**< File I/O operations */
        struct {
            char* file_path;         /**< File path for operation */
            ast_node* content;       /**< Content for write operations (NULL for read/exists/delete/list) */
        } file_io;
        
        /**< Try-catch error handling */
        struct {
            ast_node* try_block;     /**< Try block */
            char* catch_variable;    /**< Catch variable name */
            ast_node* catch_block;   /**< Catch block */
        } try_catch;
        
        /**< Throw statement */
        struct {
            ast_node* exception;     /**< Exception expression to throw */
        } throw_stmt;
        
        /**< Ternary operator */
        struct {
            ast_node* condition;     /**< Condition expression */
            ast_node* true_expr;     /**< True case expression */
            ast_node* false_expr;    /**< False case expression */
        } ternary;
        
        /**< Lambda function */
        struct {
            char** parameters;       /**< Parameter names */
            size_t parameter_count;  /**< Number of parameters */
            ast_node* body;          /**< Lambda body expression */
        } lambda;
        
        /**< String method call */
        struct {
            ast_node* string_expr;   /**< String expression */
            char* method_name;       /**< Method name (upper, lower, split, etc.) */
            ast_node** arguments;    /**< Method arguments */
            size_t argument_count;   /**< Number of arguments */
        } string_method;
        
        /**< Loop N times */
        struct {
            ast_node* count_expr;    /**< Number of times to loop */
            ast_node* body;          /**< Loop body */
        } loop_times;
        
        /**< For range loop (for i in 1..5) */
        struct {
            char* variable;          /**< Loop variable name */
            ast_node* start_expr;    /**< Start value */
            ast_node* end_expr;      /**< End value */
            ast_node* body;          /**< Loop body */
        } for_range;
        
        /**< For indexed loop (for i, item in array) */
        struct {
            char* index_var;         /**< Index variable name */
            char* item_var;          /**< Item variable name */
            ast_node* array_expr;    /**< Array expression */
            ast_node* body;          /**< Loop body */
        } for_indexed;
        
        /**< Await expression */
        struct {
            ast_node* expression;    /**< Expression to await */
        } await;
        
        /**< Import statement */
        struct {
            char* module_name;       /**< Module name to import */
            char* alias;             /**< Import alias (NULL if none) */
        } import;
        
        /**< Destructuring assignment */
        struct {
            char** target_names;     /**< Target variable names */
            size_t target_count;     /**< Number of target variables */
            ast_node* source_expr;   /**< Source expression (array or object) */
            bool is_object;          /**< true for object destructuring, false for array */
            char* rest_name;         /**< Rest parameter name (NULL if no rest) */
        } destructure;
        
        /**< Spread operator */
        struct {
            ast_node* expression;    /**< Expression to spread */
            bool in_array;           /**< true if spreading in array context */
            bool in_object;          /**< true if spreading in object context */
        } spread;
        
        /**< Generator function definition */
        struct {
            char* name;              /**< Generator function name */
            char** parameters;       /**< Parameter names */
            size_t parameter_count;  /**< Number of parameters */
            ast_node* body;          /**< Generator body */
        } generator_def;
        
        /**< Yield statement */
        struct {
            ast_node* value;         /**< Value to yield (NULL for bare yield) */
        } yield_stmt;
        
    } data;
};

/* Function declarations */
int ast_add_argument(ast_node* node, ast_node* argument);
int ast_add_element(ast_node* array, ast_node* element);
int ast_add_method(ast_node* class_def, ast_node* method);
int ast_add_parameter(ast_node* function, const char* parameter);
int ast_add_statement(ast_node* block, ast_node* statement);
ast_node*ast_create_array_access(ast_node* array_expr, ast_node* index_expr, source_location loc);
ast_node*ast_create_array_access_from_strings(const char* array_name, const char* index_str, source_location loc);
ast_node*ast_create_array_literal(source_location loc);
ast_node*ast_create_object_access(ast_node* object_expr, const char* property_name, source_location loc);
ast_node*ast_create_assignment(const char* variable, binary_operator op, ast_node* value, source_location loc);
ast_node*ast_create_binary_op(binary_operator op, ast_node* left, ast_node* right, source_location loc);
ast_node*ast_create_block(source_location loc);
ast_node*ast_create_boolean_literal(bool value, source_location loc);
ast_node*ast_create_break_statement(source_location loc);
ast_node*ast_create_class_def(const char* name, const char* parent_class, source_location loc);
ast_node*ast_create_conditional(ast_node* condition, source_location loc);
ast_node*ast_create_continue_statement(source_location loc);
ast_node*ast_create_function_call(const char* name, source_location loc);
ast_node*ast_create_function_def(const char* name, bool is_async, source_location loc);
ast_node*ast_create_identifier(const char* name, source_location loc);
ast_node*ast_create_loop(const char* variable, ast_node* iterable, source_location loc);
ast_node*ast_create_method_def(const char* name, bool is_private, source_location loc);
ast_node*ast_create_number_literal(double value, source_location loc);
ast_node*ast_create_program(void);
ast_node*ast_create_string_literal(const char* value, source_location loc);
ast_node*ast_create_try_catch(ast_node* try_block, const char* catch_var, ast_node* catch_block, source_location loc);
ast_node*ast_create_throw(ast_node* exception, source_location loc);
ast_node*ast_create_ternary(ast_node* condition, ast_node* true_expr, ast_node* false_expr, source_location loc);
ast_node*ast_create_lambda(char** parameters, size_t parameter_count, ast_node* body, source_location loc);
ast_node*ast_create_string_method(ast_node* string_expr, const char* method_name, source_location loc);
ast_node*ast_create_loop_times(ast_node* count_expr, ast_node* body, source_location loc);
ast_node*ast_create_for_range(const char* variable, ast_node* start_expr, ast_node* end_expr, ast_node* body, source_location loc);
ast_node*ast_create_for_indexed(const char* index_var, const char* item_var, ast_node* array_expr, ast_node* body, source_location loc);
ast_node*ast_create_await(ast_node* expression, source_location loc);
ast_node*ast_create_destructure(char** target_names, size_t target_count, ast_node* source_expr, bool is_object, const char* rest_name, source_location loc);
ast_node*ast_create_spread(ast_node* expression, bool in_array, bool in_object, source_location loc);
int ast_evaluate_assignment(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_binary_op(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_unary_op(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_conditional(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_file_delete(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_file_exists(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_file_list(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_file_read(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_file_write(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_function_call(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_function_def(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_identifier(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_array_access(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_object_access(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_loop(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_program_node(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_while_loop(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_block(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_break(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_continue(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_try_catch(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_throw(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_ternary(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_lambda(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_string_method(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_loop_times(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_for_range(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_for_indexed(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_await(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_destructure(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_spread(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_class_def(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_import(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_generator_def(ast_node* node, ast_evaluator* evaluator);
ast_value*ast_evaluate_yield(ast_node* node, ast_evaluator* evaluator);
void ast_free(ast_node* node);
ast_node*ast_parse_array_assignment(const char** pos, const char* array_name);
ast_node*ast_parse_class(const char** pos);
ast_node*ast_parse_comparison_expression(const char* expr);
ast_node*ast_parse_elif(const char** pos);
ast_node*ast_parse_else(const char** pos);
ast_node*ast_parse_expression(const char** pos);
ast_node*ast_parse_identifier_or_array(const char* identifier_str, source_location loc);
ast_node*ast_parse_function(const char** pos);
ast_node*ast_parse_if_block(const char** pos);
ast_node*ast_parse_if_then(const char** pos);
ast_node*ast_parse_loop(const char** pos);
ast_node*ast_parse_math_expression(const char* expr);
ast_node*ast_parse_method(const char** pos);
ast_node*ast_parse_number_literal(const char** start, const char** pos);
ast_node*ast_parse_primary(parser_state* parser);
ast_node*ast_parse_program(const char* input);
ast_node*ast_parse_program(const char* input);
ast_node*ast_parse_range_loop(const char** pos);
ast_node*ast_parse_statement(const char** pos);
ast_node*ast_parse_string_literal(const char** start, const char** pos);
ast_node*ast_parse_while(const char** pos);
ast_node*ast_parse_potential_function_call(const char** pos);
ast_node*ast_create_return(ast_node* value, source_location loc);
ast_node*ast_parse_assignment(const char** pos);
ast_node*ast_parse_print(const char** pos);
ast_node*ast_parse_conditional(const char** pos);
ast_node*ast_parse_single_value(const char** pos);
ast_node*ast_parse_object_creation(const char** pos, const char* first_name);
ast_node*ast_parse_multiple_variables_handler(const char** pos, const char* first_name);
ast_node*ast_parse_destructure(const char** pos);
ast_node*ast_parse_spread(const char** pos);
ast_node*ast_parse_generator_function(const char** pos);
ast_node*ast_parse_yield(const char** pos);
ast_value*ast_value_create_array(void);
ast_value*ast_value_create_boolean(bool value);
ast_value*ast_value_create_number(double value);
ast_value*ast_value_create_string(const char* str);
void ast_value_free(ast_value* val);
ast_value*ast_value_from_variable(variable* var);
char*ast_value_to_string(ast_value* value);
variable*ast_value_to_variable(ast_value* value);
int ast_value_array_add(ast_value* array, ast_value* element);

/* Main evaluation functions */
ast_value* ast_evaluate(ast_node* node, ast_evaluator* evaluator);
char* ast_evaluate_program(ast_node* program, ast_evaluator* evaluator);
ast_evaluator* ast_evaluator_create(store* variables, processor_context* ctx);
void ast_evaluator_free(ast_evaluator* evaluator);

/* Value creation functions */
ast_value* ast_value_create_array(void);
ast_value* ast_value_create_boolean(bool value);
ast_value* ast_value_create_number(double value);
ast_value* ast_value_create_string(const char* str);

/* Global stores for functions and other global state */
extern store* global_functions;

/**
 * @brief Mass consolidation macros for duplication reduction
 */
#ifndef XMD_NULL_CHECK
#define XMD_NULL_CHECK(ptr) \
    do { if (!(ptr)) return NULL; } while(0)
#endif

#ifndef XMD_NULL_CHECK_PARAM
#define XMD_NULL_CHECK_PARAM(ptr, param) \
    do { if (!(ptr) || !(param)) return NULL; } while(0)
#endif

#define XMD_ERROR_RETURN_NULL(condition) \
    do { if (condition) return NULL; } while(0)

#define XMD_MALLOC_CHECK(ptr, size) \
    do { \
        (ptr) = xmd_malloc(size); \
        if (!(ptr)) return NULL; \
    } while(0)

#define XMD_CALLOC_CHECK(ptr, count, size) \
    do { \
        (ptr) = xmd_calloc(count, size); \
        if (!(ptr)) return NULL; \
    } while(0)

#define XMD_STRDUP_CHECK(dest, src) \
    do { \
        (dest) = xmd_strdup(src); \
        if (!(dest)) return NULL; \
    } while(0)

#define XMD_EVAL_NULL_GUARD(evaluator, node) \
    do { \
        if (!(evaluator) || !(node)) return NULL; \
    } while(0)

#define XMD_PARSER_NULL_GUARD(state) \
    do { \
        if (!(state) || !(state)->current_token) return NULL; \
    } while(0)

#define XMD_TOKEN_TYPE_CHECK(token, expected_type) \
    do { \
        if (!(token) || (token)->type != (expected_type)) return NULL; \
    } while(0)

#define XMD_VALUE_NULL_CHECK(value) \
    do { \
        if (!(value)) return NULL; \
    } while(0)

#define XMD_STANDARD_NULL_CHECKS(param1, param2) \
    do { \
        if (!(param1) || !(param2)) return NULL; \
    } while(0)

#define XMD_TRIPLE_NULL_CHECK(p1, p2, p3) \
    do { \
        if (!(p1) || !(p2) || !(p3)) return NULL; \
    } while(0)

#endif /* XMD_AST_H */
