/**
 * @file store_entry_destroy.c
 * @brief Store entry destruction function
 * @author XMD Team
 *
 * Implementation of store entry cleanup for the XMD store system.
 */

#include "../../../include/store_internal.h"

/**
 * @brief Destroy a store entry
 * @param entry Entry to destroy (can be NULL)
 */
void store_entry_destroy(store_entry* entry) {
    if (entry == NULL) {
        return;
    }
    
    free(entry->key);
    variable_unref(entry->value);
    free(entry);
}