/**
 * @file process_for.c
 * @brief Process for directive implementation (now uses AST)
 * @author XMD Team
 * @date 2025-07-28
 */

#include "../../../include/xmd_processor_internal.h"
#include "../../../include/ast_evaluator.h"

/**
 * @brief Process for directive with range and collection support (now uses AST)
 * @param args Loop arguments for for directive (item in collection/range)
 * @param ctx Processor context
 * @param output Buffer to store loop content processed for each iteration
 * @param output_size Size of output buffer
 * @return 0 on success, -1 on error
 */
int process_for(const char* args, processor_context* ctx, char* output, size_t output_size) {
    return ast_process_for(args, ctx, output, output_size);
}
