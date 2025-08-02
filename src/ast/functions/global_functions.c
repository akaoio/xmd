/**
 * @file global_functions.c
 * @brief Global functions store for XMD
 * 
 * Genesis principle: 1 function → 1 file → 1 directory
 */

#include "../../../include/store.h"

/**
 * @brief Global functions store singleton
 */
store* global_functions = NULL;

/**
 * @brief Initialize global functions store
 */
void init_global_functions(void) {
    if (!global_functions) {
        global_functions = store_create(32);
    }
}

/**
 * @brief Cleanup global functions store
 */
void cleanup_global_functions(void) {
    if (global_functions) {
        store_destroy(global_functions);
        global_functions = NULL;
    }
}