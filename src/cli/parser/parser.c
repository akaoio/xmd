/**
 * @file parser.c
 * @brief Command-line argument parsing
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../../include/cli.h"

/**
 * @brief Parse command type from string
 * @param cmd_str Command string
 * @return Command type or -1 if invalid
 */
static int parse_command_type(const char* cmd_str) {
    if (!cmd_str) {
        return -1;
    }
    
    if (strcmp(cmd_str, "process") == 0) {
        return CLI_CMD_PROCESS;
    } else if (strcmp(cmd_str, "watch") == 0) {
        return CLI_CMD_WATCH;
    } else if (strcmp(cmd_str, "validate") == 0) {
        return CLI_CMD_VALIDATE;
    } else if (strcmp(cmd_str, "config") == 0) {
        return CLI_CMD_CONFIG;
    } else if (strcmp(cmd_str, "help") == 0) {
        return CLI_CMD_HELP;
    } else if (strcmp(cmd_str, "version") == 0) {
        return CLI_CMD_VERSION;
    }
    
    return -1;
}

/**
 * @brief Check if argument is a flag
 * @param arg Argument string
 * @return true if it's a flag, false otherwise
 */
static bool is_flag(const char* arg) {
    return arg && arg[0] == '-';
}

/**
 * @brief Parse command line arguments
 * @param argc Argument count
 * @param argv Argument vector
 * @return Parsed arguments or NULL on error
 */
cli_args* cli_parse_args(int argc, char** argv) {
    if (argc < 1 || !argv) {
        return NULL;
    }
    
    cli_args* args = calloc(1, sizeof(cli_args));
    if (!args) {
        return NULL;
    }
    
    int i = 1; // Skip program name
    
    // Check for global flags first
    while (i < argc && is_flag(argv[i])) {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            args->help = true;
            i++;
        } else if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-v") == 0) {
            args->version = true;
            i++;
        } else if (strcmp(argv[i], "--verbose") == 0) {
            args->verbose = true;
            i++;
        } else if (strcmp(argv[i], "--quiet") == 0 || strcmp(argv[i], "-q") == 0) {
            args->quiet = true;
            i++;
        } else if (strcmp(argv[i], "--debug") == 0 || strcmp(argv[i], "-d") == 0) {
            args->debug = true;
            i++;
        } else {
            // Unknown flag, skip for now
            i++;
        }
    }
    
    // If help or version requested, return immediately
    if (args->help || args->version) {
        return args;
    }
    
    // Parse command
    if (i >= argc) {
        free(args);
        return NULL; // No command specified
    }
    
    int cmd_type = parse_command_type(argv[i]);
    if (cmd_type == -1) {
        free(args);
        return NULL; // Invalid command
    }
    
    args->command = (cli_command_type)cmd_type;
    i++;
    
    // Parse command-specific arguments
    switch (args->command) {
        case CLI_CMD_PROCESS:
        case CLI_CMD_VALIDATE:
            // Expect input file
            if (i >= argc || is_flag(argv[i])) {
                free(args);
                return NULL;
            }
            args->input_file = strdup(argv[i]);
            i++;
            
            // Check for optional output file
            while (i < argc) {
                if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
                    i++;
                    if (i < argc && !is_flag(argv[i])) {
                        args->output_file = strdup(argv[i]);
                        i++;
                    }
                } else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--config") == 0) {
                    i++;
                    if (i < argc && !is_flag(argv[i])) {
                        args->config_file = strdup(argv[i]);
                        i++;
                    }
                } else if (strcmp(argv[i], "--verbose") == 0) {
                    args->verbose = true;
                    i++;
                } else if (strcmp(argv[i], "--debug") == 0 || strcmp(argv[i], "-d") == 0) {
                    args->debug = true;
                    i++;
                } else if (strcmp(argv[i], "--quiet") == 0 || strcmp(argv[i], "-q") == 0) {
                    args->quiet = true;
                    i++;
                } else {
                    i++; // Skip unknown arguments
                }
            }
            break;
            
        case CLI_CMD_WATCH:
            // Expect directory path
            if (i >= argc || is_flag(argv[i])) {
                free(args);
                return NULL;
            }
            args->watch_directory = strdup(argv[i]);
            i++;
            
            // Check for optional flags
            while (i < argc) {
                if (strcmp(argv[i], "--verbose") == 0) {
                    args->verbose = true;
                    i++;
                } else if (strcmp(argv[i], "--debug") == 0 || strcmp(argv[i], "-d") == 0) {
                    args->debug = true;
                    i++;
                } else if (strcmp(argv[i], "--quiet") == 0 || strcmp(argv[i], "-q") == 0) {
                    args->quiet = true;
                    i++;
                } else {
                    i++; // Skip unknown arguments
                }
            }
            break;
            
            
        case CLI_CMD_CONFIG:
        case CLI_CMD_HELP:
        case CLI_CMD_VERSION:
            // No additional arguments required
            break;
    }
    
    return args;
}
