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

// Function declarations
void print_usage(const char* program_name);
void print_version(void);
void cleanup_cmd_variables(cmd_variable_t cmd_variables[], int var_count);
int format_output(const char* content, const char* format, char* formatted_output, size_t buffer_size);
int cmd_process(int argc, char* argv[]);
int cmd_validate(int argc, char* argv[]);
bool looks_like_file_path(const char* arg);
int convert_shorthand_to_process(int argc, char* argv[], int* new_argc, char*** new_argv);
void free_converted_argv(int argc, char** argv);
int main(int argc, char* argv[]);

#endif /* MAIN_INTERNAL_H */