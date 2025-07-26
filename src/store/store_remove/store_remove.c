/**
 * @file store_remove.c
 * @brief Store variable removal function
 * @author XMD Team
 *
 * Implementation of variable removal for the XMD store system.
 */

#include "../../../include/store_internal.h"

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
    store_entry** entry_ptr = &s->buckets[hash];
    
    while (*entry_ptr != NULL) {
        if (strcmp((*entry_ptr)->key, name) == 0) {
            store_entry* to_remove = *entry_ptr;
            *entry_ptr = to_remove->next;
            store_entry_destroy(to_remove);
            s->size--;
            return true;
        }
        entry_ptr = &(*entry_ptr)->next;
    }
    
    return false;
}