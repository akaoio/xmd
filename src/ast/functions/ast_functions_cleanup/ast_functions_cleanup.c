/**
 * @file ast_functions_cleanup.c
 * @brief Implementation of ast_functions_cleanup function
 * 
 * This file contains ONLY the ast_functions_cleanup function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include "ast_node.h"
#include "store.h"
/**
 * @brief Clean up global functions store
 */
void ast_functions_cleanup(void) {
    if (global_functions) {
        store_destroy(global_functions);
        global_functions = NULL;
    }
}
