/**
 * @file parser_internal.h
 * @brief Internal declarations for CLI parser
 * @author XMD Team
 */

#ifndef PARSER_INTERNAL_H
#define PARSER_INTERNAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/cli.h"

// Function prototypes
int parse_command_type(const char* cmd_str);
bool is_flag(const char* arg);
cli_args* cli_parse_args(int argc, char** argv);

#endif /* PARSER_INTERNAL_H */
