/**
 * @file store_entry_create.c
 * @brief Store entry creation function
 * @author XMD Team
 *
 * Implementation of store entry creation for the XMD store system.
 */

#include "../../../include/store_internal.h"

/**
 * @brief Create a new store entry
 * @param key Variable name key
 * @param value Variable value
 * @return New store entry or NULL on failure
 */
store_entry* store_entry_create(const char* key, variable* value) {
    if (key == NULL) {
        return NULL;
    }
    
    store_entry* entry = malloc(sizeof(store_entry));
    if (entry == NULL) {
        return NULL;
    }
    
    // Copy key
    size_t key_len = strlen(key);
    entry->key = malloc(key_len + 1);
    if (entry->key == NULL) {
        free(entry);
        return NULL;
    }
    strcpy(entry->key, key);
    
    // Reference value
    entry->value = variable_ref(value);
    entry->next = NULL;
    
    return entry;
}