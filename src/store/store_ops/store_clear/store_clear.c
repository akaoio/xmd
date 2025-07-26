/**
 * @file store_clear.c
 * @brief Clear all variables from store
 * @author XMD Team
 */

#include "../../../../include/store_ops_internal.h"

/**
 * @brief Clear all variables from store
 * @param s Store instance
 */
void store_clear(store* s) {
    if (s == NULL) {
        return;
    }
    
    // Free all entries
    for (size_t i = 0; i < s->capacity; i++) {
        store_entry* entry = s->buckets[i];
        while (entry != NULL) {
            store_entry* next = entry->next;
            free(entry->key);
            variable_unref(entry->value);
            free(entry);
            entry = next;
        }
        s->buckets[i] = NULL;
    }
    
    s->size = 0;
}