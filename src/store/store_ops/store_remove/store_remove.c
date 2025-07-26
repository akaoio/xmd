/**
 * @file store_remove.c
 * @brief Remove a variable from the store
 * @author XMD Team
 */

#include "../../../../include/store_ops_internal.h"

/**
 * @brief Remove a variable from the store
 * @param s Store instance
 * @param name Variable name
 * @return true if removed, false if not found
 */
bool store_remove(store* s, const char* name) {
    if (s == NULL || name == NULL) {
        return false;
    }
    
    size_t hash = xmd_hash_key(name, s->capacity);
    store_entry* entry = s->buckets[hash];
    store_entry* prev = NULL;
    
    while (entry != NULL) {
        if (strcmp(entry->key, name) == 0) {
            // Remove entry from chain
            if (prev != NULL) {
                prev->next = entry->next;
            } else {
                s->buckets[hash] = entry->next;
            }
            
            // Free entry
            free(entry->key);
            variable_unref(entry->value);
            free(entry);
            s->size--;
            
            return true;
        }
        
        prev = entry;
        entry = entry->next;
    }
    
    return false;
}