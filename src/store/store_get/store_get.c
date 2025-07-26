/**
 * @file store_get.c
 * @brief Store variable getter function
 * @author XMD Team
 *
 * Implementation of variable retrieval for the XMD store system.
 */

#include "../../../include/store_internal.h"

/**
 * @brief Get a variable from the store
 * @param s Store instance
 * @param name Variable name
 * @return Variable if found, NULL otherwise
 */
variable* store_get(store* s, const char* name) {
    if (s == NULL || name == NULL) {
        return NULL;
    }
    
    size_t hash = xmd_hash_key(name, s->capacity);
    
    store_entry* entry = s->buckets[hash];
    while (entry != NULL) {
        if (strcmp(entry->key, name) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    
    return NULL;
}