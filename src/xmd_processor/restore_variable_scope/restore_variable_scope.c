/**
 * @file restore_variable_scope.c
 * @brief Variable scope restoration function after loop completion
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/variable.h"
#include "../../../include/store.h"

/**
 * @brief Restore variable scope after loop
 * @param variables Variable store to restore to
 * @param backup Backup store to restore from
 * @param loop_var_name Loop variable name (unused in current implementation)
 */
void restore_variable_scope(store* variables, store* backup, const char* loop_var_name) {
    // Clear current variables
    store_clear(variables);
    
    // Restore from backup
    size_t count;
    char** keys = store_keys(backup, &count);
    if (!keys) return;
    
    for (size_t i = 0; i < count; i++) {
        variable* var = store_get(backup, keys[i]);
        if (var) {
            variable* copy = variable_copy(var);
            if (copy) {
                store_set(variables, keys[i], copy);
                variable_unref(copy);
            }
        }
        free(keys[i]);
    }
    free(keys);
}