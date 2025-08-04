/**
 * @file store_keys.c
 * @brief Implementation of store_keys function
 * 
 * This file contains ONLY the store_keys function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/store.c
 */

#include <stdlib.h>
#include "../../../../include/store.h"
#include "../../../../include/store_internal.h"
#include "../../../../include/utils.h"
#include "../../../../utils/common/common_macros.h"
#include "../../../../utils/common/validation_macros.h"

/**
 * @brief Get all keys from store
 * @param s Store instance
 * @param count Output parameter for number of keys
 * @return Array of key strings (must be freed) or NULL
 */
char** store_keys(store* s, size_t* count) {
    XMD_VALIDATE_PTRS(NULL, s, count);
    
    // Count keys
    size_t key_count = 0;
    FOR_EACH_INDEX(i, s->capacity) {
        store_entry* entry = s->buckets[i];
        while (entry) {
            key_count++;
            entry = entry->next;
        }
    }
    
    if (key_count == 0) {
        *count = 0;
        return NULL;
    }
    
    // Allocate array
    char** keys;
    XMD_MALLOC_DYNAMIC(keys, key_count * sizeof(char*), (*count = 0, NULL));
    
    // Fill array
    size_t idx = 0;
    FOR_EACH_INDEX(i, s->capacity) {
        if (idx >= key_count) break;
        store_entry* entry = s->buckets[i];
        while (entry && idx < key_count) {
            keys[idx] = xmd_strdup(entry->key);
            XMD_VALIDATE_OR_CLEANUP(keys[idx], {
                // Cleanup on allocation failure
                FOR_EACH_INDEX(j, idx) {
                    XMD_FREE_SAFE(keys[j]);
                }
                XMD_FREE_SAFE(keys);
                *count = 0;
            }, NULL);
            idx++;
            entry = entry->next;
        }
    }
    
    *count = key_count;
    return keys;
}
