/**
 * @file store_destroy.c
 * @brief Implementation of store_destroy function
 * 
 * This file contains ONLY the store_destroy function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/store.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/store.h"
#include "../../../include/store_internal.h"
#include "../../../include/variable.h"
#include "../../utils/common/common_macros.h"

/**
 * @brief Destroy store
 * @param s Store to destroy
 */
void store_destroy(store* s) {
    XMD_ENTRY_VALIDATE_VOID(s);
    
    fflush(stdout);
    // USE MACRO INSTEAD OF BOILERPLATE
    FOR_EACH_INDEX(i, s->capacity) {
        store_entry* entry = s->buckets[i];
        // USE MACRO INSTEAD OF BOILERPLATE
        WHILE_NOT_NULL(entry) {
            fflush(stdout);
            
            store_entry* next = entry->next;
            // USE MACRO INSTEAD OF BOILERPLATE
            if (entry->key) {
                fflush(stdout);
                XMD_FREE_AND_NULL(entry->key);
            }
            if (entry->value) {
                variable_unref(entry->value);
            }
            free(entry);
            entry = next;
        }
    }
    free(s->buckets);
    free(s);
}
