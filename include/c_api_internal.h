/**
 * @file c_api_internal.h
 * @brief Internal header for C API functions
 * @author XMD Team
 */

#ifndef C_API_INTERNAL_H
#define C_API_INTERNAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include "cli.h"
#include "lexer.h"
#include "token.h"
#include "store.h"

// Forward declarations for XMD directive processor
int process_xmd_directive(const char* directive, store* var_store, char* output, size_t output_size);
int process_text_with_directives(const char* text, store* var_store, char* output, size_t output_size);
int process_complete_for_loop(const char* content, size_t for_start, size_t args_start, 
                             size_t args_end, store* var_store, char* output, size_t output_size);
int process_complete_if_statement(const char* content, size_t if_start, size_t args_start, 
                                 size_t args_end, store* var_store, char* output, size_t output_size);

// Use xmd_result from cli.h

// Internal XMD context structure
typedef struct xmd_context_internal {
    xmd_config* config;
    bool initialized;
    store* global_variables;
} xmd_context_internal;

// Function declarations
int preprocess_variables(const char* input, size_t input_length, store* var_store, 
                        char* output, size_t output_size);
int preprocess_for_loops(const char* input, size_t input_length, store* var_store, 
                        char* output, size_t output_size);
bool c_api_evaluate_condition(const char* condition, store* var_store);
int preprocess_if_statements(const char* input, size_t input_length, store* var_store, 
                            char* output, size_t output_size);
void* c_api_xmd_init(const char* config_path);
xmd_result* c_api_create_result(int error_code, const char* output, const char* error_message);
xmd_result* c_api_xmd_process_string(void* handle, const char* input, size_t input_length);
xmd_result* c_api_xmd_process_file(void* handle, const char* input_path, const char* output_path);
xmd_result* c_api_xmd_validate(void* handle, const char* input, size_t input_length);
int c_api_xmd_set_config(void* handle, const char* key, const char* value);
char* c_api_xmd_get_config(void* handle, const char* key);
void c_api_xmd_result_free(xmd_result* result);
void c_api_xmd_cleanup(void* handle);
const char* c_api_xmd_get_version(void);
int c_api_xmd_set_variable(void* processor, const char* key, const char* value);
char* c_api_xmd_get_variable(void* processor, const char* key);

#endif /* C_API_INTERNAL_H */