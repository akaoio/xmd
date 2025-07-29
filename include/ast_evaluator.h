/**
 * @file ast_evaluator.h
 * @brief AST evaluator interface for XMD language execution
 * @author XMD Team
 * @date 2025-07-28
 */

#ifndef XMD_AST_EVALUATOR_H
#define XMD_AST_EVALUATOR_H

#include "ast_node.h"
#include "variable.h"
#include "store.h"
#include "xmd_processor_internal.h"

/**
 * @brief AST evaluation result value
 */
typedef struct ast_value ast_value;

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
typedef struct {
    store* variables;              /**< Variable storage */
    processor_context* ctx;        /**< XMD processor context */
    char* output_buffer;          /**< Output accumulator */
    size_t output_size;           /**< Buffer size */
    bool has_error;               /**< Error flag */
    char* error_message;          /**< Error details */
    bool in_statement_context;    /**< True when evaluating a statement (not expression) */
} ast_evaluator;

/* Main evaluation functions */

/**
 * @brief Evaluate AST node
 * @param node AST node to evaluate
 * @param evaluator Evaluator context
 * @return AST value result or NULL on error
 */
ast_value* ast_evaluate(ast_node* node, ast_evaluator* evaluator);

/**
 * @brief Evaluate assignment statement
 * @param node Assignment AST node
 * @param evaluator Evaluator context
 * @return 0 on success, -1 on error
 */
int ast_evaluate_assignment(ast_node* node, ast_evaluator* evaluator);

/**
 * @brief Evaluate expression
 * @param node Expression AST node
 * @param evaluator Evaluator context
 * @return AST value result or NULL on error
 */
ast_value* ast_evaluate_expression(ast_node* node, ast_evaluator* evaluator);

/**
 * @brief Evaluate function call
 * @param node Function call AST node
 * @param evaluator Evaluator context
 * @return AST value result or NULL on error
 */
ast_value* ast_evaluate_function_call(ast_node* node, ast_evaluator* evaluator);

/* Evaluator management */

/**
 * @brief Create AST evaluator
 * @param variables Variable store
 * @param ctx Processor context
 * @return Evaluator or NULL on error
 */
ast_evaluator* ast_evaluator_create(store* variables, processor_context* ctx);

/**
 * @brief Free AST evaluator
 * @param evaluator Evaluator to free
 */
void ast_evaluator_free(ast_evaluator* evaluator);

/**
 * @brief Append output to evaluator buffer
 * @param evaluator Evaluator context
 * @param text Text to append
 * @return 0 on success, -1 on error
 */
int ast_evaluator_append_output(ast_evaluator* evaluator, const char* text);

/* Value management */

/**
 * @brief Create AST value
 * @param type Value type
 * @return New AST value or NULL on error
 */
ast_value* ast_value_create(int type);

/**
 * @brief Free AST value
 * @param value Value to free
 */
void ast_value_free(ast_value* value);

/**
 * @brief Convert AST value to variable
 * @param value AST value
 * @return Variable or NULL on error
 */
variable* ast_value_to_variable(ast_value* value);

/**
 * @brief Replace string-based process_set with AST evaluation
 * @param args Arguments for set directive
 * @param ctx Processor context
 * @param output Buffer to store output
 * @param output_size Size of output buffer
 * @return 0 on success, -1 on error
 */
int process_set_ast(const char* args, processor_context* ctx, char* output, size_t output_size);

/**
 * @brief AST-based condition evaluation (replaces string-based evaluate_condition)
 * @param condition Condition string to evaluate
 * @param variables Variable store for variable lookups
 * @return true if condition is true, false otherwise
 */
bool ast_evaluate_condition(const char* condition, store* variables);

/**
 * @brief AST-based array literal parser (replaces string-based parse_array_literal)
 * @param input Input string containing array literal like ["item1", "item2"]
 * @return Array variable or NULL on error
 */
variable* ast_parse_array_literal(const char* input);

/**
 * @brief AST-based concatenation expression evaluation (replaces string-based evaluate_concatenation_expression)
 * @param expr Expression string to evaluate
 * @param ctx Processor context
 * @return Evaluated string result or NULL on error
 */
char* ast_evaluate_concatenation_expression(const char* expr, processor_context* ctx);

/**
 * @brief AST-based for loop processor (replaces string-based process_for)
 * @param args Loop arguments for for directive (item in collection/range)
 * @param ctx Processor context
 * @param output Buffer to store loop content processed for each iteration
 * @param output_size Size of output buffer
 * @return 0 on success, -1 on error
 */
int ast_process_for(const char* args, processor_context* ctx, char* output, size_t output_size);

/**
 * @brief AST-based variable substitution (replaces string-based substitute_variables)
 * @param text Input text containing {{variable}} patterns
 * @param variables Variable store for variable lookups
 * @return New string with variables substituted (caller must free) or NULL on error
 */
char* ast_substitute_variables(const char* text, store* variables);

/**
 * @brief AST-based XMD content processor (replaces all string-based processors)
 * @param input Input content containing XMD directives in HTML comments
 * @param variables Variable store for processing
 * @return Processed content (caller must free) or NULL on error
 */
char* ast_process_xmd_content(const char* input, store* variables);

#endif /* XMD_AST_EVALUATOR_H */