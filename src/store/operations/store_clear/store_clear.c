/**
 * @file store_clear.c
 * @brief Implementation of store_clear function
 * 
 * This file contains ONLY the store_clear function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/store.c
 */

#include <stdlib.h>
#include "../../../../include/store.h"
#include "../../../../include/store_internal.h"
#include "../../../../include/variable.h"
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"

/**
 * @brief Clear all entries from store
 * @param s Store to clear
 */
void store_clear(store* s) {
    XMD_ENTRY_VALIDATE_VOID(s);
    
    FOR_EACH_INDEX(i, s->capacity) {
        store_entry* entry = s->buckets[i];
        while (entry) {
            store_entry* next = entry->next;
            XMD_FREE_SAFE(entry->key);
            variable_unref(entry->value);
            XMD_FREE_SAFE(entry);
            entry = next;
        }
        s->buckets[i] = NULL;
    }
    s->size = 0;
}
