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
#include "sandbox_internal.h"
#include "store.h"
#include "xmd.h"
#include "loop.h"
#include "import_tracker.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_IF_DEPTH 32
#define MAX_LOOP_DEPTH 8
#define MAX_LOOP_ITERATIONS 2000

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
    char* source_file_path;                 /**< Path to currently processed source file */
    SandboxContext* sandbox_ctx;            /**< Sandbox security context */
} processor_context;

/* Context functions */
processor_context* create_context(store* variables);
void destroy_context(processor_context* ctx);
void set_context_source_file(processor_context* ctx, const char* file_path);
bool should_execute_block(processor_context* ctx);

/* Execution functions */
int execute_command(const char* command, char* output, size_t output_size);
char* execute_command_dynamic(const char* command, int* exit_status);

/* Utility functions */
char* trim_whitespace(char* str);
char* substitute_variables(const char* text, store* variables);
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

/* Helper functions */
variable* parse_array_literal(const char* input);


/* Version functions */
char* get_version(void);
char* get_version_detailed(void);

/* AST processing functions (current implementation) */
char* ast_process_xmd_content(const char* input, store* variables);

/* Global import tracker functions (for watch mode) */
void xmd_set_global_import_tracker(import_tracker_t* tracker);
import_tracker_t* xmd_get_global_import_tracker(void);
bool xmd_is_watch_mode(void);

#ifdef __cplusplus
}
#endif

#endif /* XMD_PROCESSOR_INTERNAL_H */
