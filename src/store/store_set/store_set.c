/**
 * @file store_set.c
 * @brief Store variable setter function
 * @author XMD Team
 *
 * Implementation of variable storage for the XMD store system.
 */

#include "../../../include/store_internal.h"

/**
 * @brief Set a variable in the store
 * @param s Store instance
 * @param name Variable name
 * @param var Variable to store (reference will be taken)
 * @return true on success, false on failure
 */
bool store_set(store* s, const char* name, variable* var) {
    if (s == NULL || name == NULL || var == NULL) {
        return false;
    }
    
    // Check if resize is needed
    if ((double)s->size / s->capacity >= LOAD_FACTOR_THRESHOLD) {
        if (!store_resize(s)) {
            return false;
        }
    }
    
    size_t hash = xmd_hash_key(name, s->capacity);
    
    // Check if key already exists
    store_entry* entry = s->buckets[hash];
    while (entry != NULL) {
        if (strcmp(entry->key, name) == 0) {
            // Replace existing value
            variable_unref(entry->value);
            entry->value = variable_ref(var);
            return true;
        }
        entry = entry->next;
    }
    
    // Create new entry
    store_entry* new_entry = store_entry_create(name, var);
    if (new_entry == NULL) {
        return false;
    }
    
    // Insert at head of chain
    new_entry->next = s->buckets[hash];
    s->buckets[hash] = new_entry;
    s->size++;
    
    return true;
}