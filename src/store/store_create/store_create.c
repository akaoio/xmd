/**
 * @file store_create.c
 * @brief Store creation function
 * @author XMD Team
 *
 * Implementation of store creation for the XMD store system.
 */

#include "../../../include/store_internal.h"

/**
 * @brief Create a new store
 * @return New store instance or NULL on failure
 */
store* store_create(void) {
    store* s = malloc(sizeof(store));
    if (s == NULL) {
        return NULL;
    }
    
    s->capacity = INITIAL_CAPACITY;
    s->size = 0;
    s->buckets = calloc(s->capacity, sizeof(store_entry*));
    if (s->buckets == NULL) {
        free(s);
        return NULL;
    }
    
    return s;
}