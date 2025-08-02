/**
 * @file ast_parse_program.c
 *
 *
 * @brief Implementation of ast_parse_program function
 * 
 * This file contains ONLY the ast_parse_program function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdlib.h>
#include "ast_node.h"
#include "ast_parser.h"
/**
 * @brief Parse XMD program - function needed by native_xmd_consolidated.c
 * @param input Input string to parse
 * @return AST program node or NULL
 */
ast_node* ast_parse_program(const char* input) {
    if (!input) {
        return NULL;
    }
    
    // Create program node
    ast_node* program = ast_create_program();
    if (!program) {
        return NULL;
    }
    
    // Parse statements from input
    const char* pos = input;
    while (*pos) {
        // Skip whitespace
        while (*pos && (*pos == ' ' || *pos == '\t' || *pos == '\n' || *pos == '\r')) {
            pos++;
        }
        
        if (!*pos) break; // End of input
        // Parse next statement
        ast_node* stmt = ast_parse_statement(&pos);
        if (stmt) {
            // Add statement to program using existing ast_add_statement function
            if (ast_add_statement(program, stmt) != 0) {
                ast_free(stmt);
                break;
            }
        }
    }
    
    return program;
}
