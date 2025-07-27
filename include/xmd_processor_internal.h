/**
 * @file xmd_processor_internal.h
 * @brief Internal header for XMD processor functions
 * @author XMD Team
 * @date 2025-07-26
 */

#ifndef XMD_PROCESSOR_INTERNAL_H
#define XMD_PROCESSOR_INTERNAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>
#include "store.h"
#include "xmd.h"
#include "loop.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_IF_DEPTH 32
#define MAX_LOOP_DEPTH 8
#define MAX_LOOP_ITERATIONS 1000

/**
 * @struct if_stack_entry
 * @brief Stack entry for nested if statements
 */
typedef struct {
    bool condition_met;     /**< Was condition true? */
    bool branch_executed;   /**< Has any branch in this if-chain been executed? */
    bool in_elif;          /**< Currently in elif processing */
} if_stack_entry;

/**
 * @struct processor_context
 * @brief Context for XMD processing
 */
typedef struct {
    store* variables;                       /**< Variable store */
    if_stack_entry if_stack[MAX_IF_DEPTH];  /**< If statement stack */
    int if_stack_size;                      /**< Current if stack size */
    int loop_depth;                         /**< Current loop nesting depth */
    int total_iterations;                   /**< Total iterations across all loops */
    bool currently_executing;               /**< Current execution state */
} processor_context;

/* Context functions */
processor_context* create_context(store* variables);
bool should_execute_block(processor_context* ctx);

/* Execution functions */
int execute_command(const char* command, char* output, size_t output_size);
char* execute_command_dynamic(const char* command, int* exit_status);

/* Utility functions */
char* trim_whitespace(char* str);
char* substitute_variables(const char* text, store* variables);
bool evaluate_condition(const char* condition, store* variables);
bool is_multiline_directive(const char* comment_content);
void process_multiline_directive(const char* directive_content, store* variables);
void process_multiline_directive_enhanced(const char* directive_content, store* variables);
char* process_multiline_block(const char* content, store* variables);
int parse_range(const char* range_str, store* variables, char*** items, int* count);
int parse_collection(const char* collection_name, store* variables, char*** items, int* count);
const char* find_matching_endfor(const char* start, const char* input_end);
store* backup_variable_scope(store* variables, const char* loop_var_name);
void restore_variable_scope(store* variables, store* backup, const char* loop_var_name);
int process_loop_body(const char* content, processor_context* ctx, LoopContext* loop_ctx);

/* Directive processing functions */
int process_exec(const char* args, processor_context* ctx, char* output, size_t output_size);
char* process_exec_dynamic(const char* args, processor_context* ctx);
int process_set(const char* args, processor_context* ctx, char* output, size_t output_size);
int process_if(const char* args, processor_context* ctx, char* output, size_t output_size);
int process_elif(const char* args, processor_context* ctx, char* output, size_t output_size);
int process_else(processor_context* ctx, char* output, size_t output_size);
int process_endif(processor_context* ctx, char* output, size_t output_size);
int process_import(const char* args, processor_context* ctx, char* output, size_t output_size);
int process_for(const char* args, processor_context* ctx, char* output, size_t output_size);
int process_directive(const char* directive, processor_context* ctx, char* output, size_t output_size);

/* Core processing functions */
char* process_xmd_content(const char* input, store* variables);
char* process_xmd_content_enhanced(const char* input, store* variables);
char* process_xmd_content_fixed(const char* input, store* variables);

/* Public API functions */
int process_xmd_directive(const char* directive, store* var_store, char* output, size_t output_size);
int process_text_with_directives(const char* text, store* var_store, char* output, size_t output_size);

#ifdef __cplusplus
}
#endif

#endif /* XMD_PROCESSOR_INTERNAL_H */
