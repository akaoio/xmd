#define _GNU_SOURCE  // For strdup - must be before includes

/**
 * @file cli.c
 * @brief CLI argument parsing function
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "../../../include/cli.h"

/**
 * @brief Parse command line arguments
 * @param argc Argument count
 * @param argv Argument vector
 * @return Parsed arguments structure or NULL on error
 */
cli_args* cli_parse_args(int argc, char** argv) {
    if (argc < 1 || !argv) {
        return NULL;
    }
    
    cli_args* args = calloc(1, sizeof(cli_args));
    if (!args) {
        return NULL;
    }
    
    // Default values
    args->command = CLI_CMD_HELP;
    args->verbose = false;
    args->quiet = false;
    args->debug = false;
    args->help = false;
    args->version = false;
    
    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"version", no_argument, 0, 'V'},
        {"output", required_argument, 0, 'o'},
        {"config", required_argument, 0, 'c'},
        {"verbose", no_argument, 0, 'v'},
        {"quiet", no_argument, 0, 'q'},
        {"debug", no_argument, 0, 'd'},
        {0, 0, 0, 0}
    };
    
    int option_index = 0;
    int c;
    
    while ((c = getopt_long(argc, argv, "hVo:c:vqd", long_options, &option_index)) != -1) {
        switch (c) {
            case 'h':
                args->help = true;
                args->command = CLI_CMD_HELP;
                return args;
            case 'V':
                args->version = true;
                args->command = CLI_CMD_VERSION;
                return args;
            case 'o':
                args->output_file = strdup(optarg);
                break;
            case 'c':
                args->config_file = strdup(optarg);
                break;
            case 'v':
                args->verbose = true;
                break;
            case 'q':
                args->quiet = true;
                break;
            case 'd':
                args->debug = true;
                break;
            case '?':
                free(args);
                return NULL;
            default:
                free(args);
                return NULL;
        }
    }
    
    // Parse command
    if (optind < argc) {
        const char* command = argv[optind];
        
        if (strcmp(command, "process") == 0) {
            args->command = CLI_CMD_PROCESS;
            if (optind + 1 < argc) {
                args->input_file = strdup(argv[optind + 1]);
            }
        } else if (strcmp(command, "watch") == 0) {
            args->command = CLI_CMD_WATCH;
            if (optind + 1 < argc) {
                args->watch_directory = strdup(argv[optind + 1]);
            }
        } else if (strcmp(command, "validate") == 0) {
            args->command = CLI_CMD_VALIDATE;
            if (optind + 1 < argc) {
                args->input_file = strdup(argv[optind + 1]);
            }
        } else if (strcmp(command, "config") == 0) {
            args->command = CLI_CMD_CONFIG;
        } else if (strcmp(command, "help") == 0) {
            args->command = CLI_CMD_HELP;
        } else if (strcmp(command, "version") == 0) {
            args->command = CLI_CMD_VERSION;
        } else {
            fprintf(stderr, "Unknown command: %s\n", command);
            free(args);
            return NULL;
        }
    }
    
    return args;
}

