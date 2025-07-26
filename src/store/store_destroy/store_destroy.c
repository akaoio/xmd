/**
 * @file store_destroy.c
 * @brief Store destruction function
 * @author XMD Team
 *
 * Implementation of store cleanup for the XMD store system.
 */

#include "../../../include/store_internal.h"

/**
 * @brief Destroy store and free memory
 * @param s Store to destroy (can be NULL)
 */
void store_destroy(store* s) {
    if (s == NULL) {
        return;
    }
    
    // Free all entries
    for (size_t i = 0; i < s->capacity; i++) {
        store_entry* entry = s->buckets[i];
        while (entry != NULL) {
            store_entry* next = entry->next;
            store_entry_destroy(entry);
            entry = next;
        }
    }
    
    free(s->buckets);
    free(s);
}