/**
 * @file ast_functions_init.c
 * @brief Implementation of ast_functions_init function
 * 
 * This file contains ONLY the ast_functions_init function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include "ast_node.h"
#include "store.h"
// Global function registry for storing user-defined functions
store* global_functions = NULL;
/**
 * @brief Initialize global functions store
 */
void ast_functions_init(void) {
    if (!global_functions) {
        global_functions = store_create();
    }
}
