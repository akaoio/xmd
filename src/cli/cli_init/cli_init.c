/**
 * @file cli_init.c
 * @brief CLI context initialization function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/cli.h"

/**
 * @brief Initialize CLI context
 * @param argc Argument count
 * @param argv Argument vector
 * @return CLI context or NULL on error
 */
cli_context* cli_init(int argc, char** argv) {
    if (argc < 1 || !argv) {
        return NULL;
    }
    
    cli_context* ctx = calloc(1, sizeof(cli_context));
    if (!ctx) {
        return NULL;
    }
    
    // Parse arguments
    ctx->args = cli_parse_args(argc, argv);
    if (!ctx->args) {
        free(ctx);
        return NULL;
    }
    
    // Store program name
    if (argv[0]) {
        ctx->program_name = strdup(argv[0]);
    }
    
    // Initialize XMD context
    ctx->xmd = NULL; // Will be initialized when processing starts
    ctx->exit_code = 0;
    
    return ctx;
}
