/**
 * @file ast_process_directive_content.h
 * @brief Process XMD directive content using AST
 * @author XMD Team
 * @date 2025-07-29
 */

#ifndef AST_PROCESS_DIRECTIVE_CONTENT_H
#define AST_PROCESS_DIRECTIVE_CONTENT_H

#include "xmd_processor_internal.h"

/**
 * @brief Process XMD directive found in HTML comment
 * @param directive_content Content between <!-- xmd: and -->
 * @param ctx Processor context
 * @param output Output buffer for generated content
 * @param output_capacity Current capacity of output buffer
 * @param output_pos Current position in output buffer
 * @return 0 on success, -1 on error
 */
int ast_process_directive_content(const char* directive_content, 
                                 processor_context* ctx,
                                 char** output,
                                 size_t* output_capacity,
                                 size_t* output_pos);

#endif /* AST_PROCESS_DIRECTIVE_CONTENT_H */
