/**
 * @file backup_variable_scope.c
 * @brief Variable scope backup function for loop isolation
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/variable.h"
#include "../../../include/store.h"

/**
 * @brief Create variable scope backup for loop isolation
 * @param variables Original variable store
 * @param loop_var_name Loop variable name to exclude
 * @return Backup store or NULL on error
 */
store* backup_variable_scope(store* variables, const char* loop_var_name) {
    store* backup = store_create();
    if (!backup) return NULL;
    
    // Get all keys from original store
    size_t count;
    char** keys = store_keys(variables, &count);
    if (!keys) return backup;
    
    // Copy all variables except the loop variable
    for (size_t i = 0; i < count; i++) {
        if (strcmp(keys[i], loop_var_name) != 0) {
            variable* var = store_get(variables, keys[i]);
            if (var) {
                variable* copy = variable_copy(var);
                if (copy) {
                    store_set(backup, keys[i], copy);
                    variable_unref(copy);
                }
            }
        }
        free(keys[i]);
    }
    free(keys);
    
    return backup;
}