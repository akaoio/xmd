/**
 * @file process_set.c
 * @brief Process set directive implementation (AST-based)
 * @author XMD Team
 * @date 2025-07-28
 */

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <ctype.h>
#include "../../../include/xmd_processor_internal.h"
#include "../../../include/variable.h"
#include "../../../include/ast_evaluator.h"

/**
 * @brief Process set directive using AST parsing and evaluation
 * @param args Arguments for set directive (variable assignment)
 * @param ctx Processor context
 * @param output Buffer to store output (unused for set)
 * @param output_size Size of output buffer
 * @return 0 on success, -1 on error
 */
int process_set(const char* args, processor_context* ctx, char* output, size_t output_size) {
    // Use the new AST-based implementation
    return process_set_ast(args, ctx, output, output_size);
}
