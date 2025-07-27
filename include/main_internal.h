/**
 * @file main_internal.h
 * @brief Internal header for main module functions
 * @author XMD Team
 */

#ifndef MAIN_INTERNAL_H
#define MAIN_INTERNAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include "config.h"
#include "xmd_processor_internal.h"
#include "xmd.h"

// Command variable structure
typedef struct {
    char* key;
    char* value;
} cmd_variable_t;

// Command process options structure  
typedef struct {
    const char* input_file;
    const char* output_file;
    const char* config_file;
    const char* format;
    bool debug_mode;
    bool trace_execution;
    bool allow_exec;
} cmd_process_options_t;

// Function declarations
void print_usage(const char* program_name);
void print_version(void);
void cleanup_cmd_variables(cmd_variable_t cmd_variables[], int var_count);
int format_output(const char* content, const char* format, char* formatted_output, size_t buffer_size);
int cmd_process(int argc, char* argv[]);
int cmd_validate(int argc, char* argv[]);
int cmd_watch(int argc, char* argv[]);
bool looks_like_file_path(const char* arg);
int convert_shorthand_to_process(int argc, char* argv[], int* new_argc, char*** new_argv);
void free_converted_argv(int argc, char** argv);
int main(int argc, char* argv[]);

// New refactored function declarations
int cmd_process_parse_args(int argc, char* argv[], cmd_process_options_t* options, 
                          cmd_variable_t cmd_variables[], int* var_count);
xmd_config* cmd_process_create_config(const cmd_process_options_t* options);
xmd_processor* cmd_process_setup_processor(xmd_config* config, 
                                          const cmd_variable_t cmd_variables[], 
                                          int var_count);
xmd_result* cmd_process_handle_input(xmd_processor* processor, 
                                    const cmd_process_options_t* options);
int cmd_process_format_output(const xmd_result* result, 
                             const cmd_process_options_t* options);

#endif /* MAIN_INTERNAL_H */