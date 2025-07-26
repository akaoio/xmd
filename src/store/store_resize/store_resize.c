/**
 * @file store_resize.c
 * @brief Store hash table resize function
 * @author XMD Team
 *
 * Implementation of dynamic hash table resizing for the XMD store system.
 */

#include "../../../include/store_internal.h"

/**
 * @brief Resize store hash table
 * @param s Store to resize
 * @return true on success, false on failure
 */
bool store_resize(store* s) {
    if (s == NULL) {
        return false;
    }
    
    size_t old_capacity = s->capacity;
    store_entry** old_buckets = s->buckets;
    
    // Double capacity
    s->capacity *= 2;
    s->buckets = calloc(s->capacity, sizeof(store_entry*));
    if (s->buckets == NULL) {
        s->capacity = old_capacity;
        s->buckets = old_buckets;
        return false;
    }
    
    s->size = 0;
    
    // Rehash all entries
    for (size_t i = 0; i < old_capacity; i++) {
        store_entry* entry = old_buckets[i];
        while (entry != NULL) {
            store_entry* next = entry->next;
            
            // Rehash entry
            size_t hash = xmd_hash_key(entry->key, s->capacity);
            entry->next = s->buckets[hash];
            s->buckets[hash] = entry;
            s->size++;
            
            entry = next;
        }
    }
    
    free(old_buckets);
    return true;
}