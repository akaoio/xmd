/**
 * @file store_clear.c
 * @brief Store clearing function
 * @author XMD Team
 *
 * Implementation of store clearing for the XMD store system.
 */

#include "../../../include/store_internal.h"

/**
 * @brief Clear all variables from store
 * @param s Store instance
 */
void store_clear(store* s) {
    if (s == NULL) {
        return;
    }
    
    for (size_t i = 0; i < s->capacity; i++) {
        store_entry* entry = s->buckets[i];
        while (entry != NULL) {
            store_entry* next = entry->next;
            store_entry_destroy(entry);
            entry = next;
        }
        s->buckets[i] = NULL;
    }
    s->size = 0;
}