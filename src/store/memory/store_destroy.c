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
#include "store.h"
#include "store_internal.h"
#include "variable.h"

/**
 * @brief Destroy store
 * @param s Store to destroy
 */
void store_destroy(store* s) {
    if (!s) {
        return;
    }
    
    printf("DEBUG: store_destroy - checking %zu buckets\n", s->capacity);
    fflush(stdout);
    for (size_t i = 0; i < s->capacity; i++) {
        store_entry* entry = s->buckets[i];
        while (entry) {
            printf("DEBUG: store_destroy - processing entry with key: %s\n", entry->key ? entry->key : "(null)");
            fflush(stdout);
            
            store_entry* next = entry->next;
            if (entry->key) {
                printf("DEBUG: store_destroy - freeing key\n");
                fflush(stdout);
                free(entry->key);
            }
            if (entry->value) {
                printf("DEBUG: store_destroy - about to call variable_unref\n");
                variable_unref(entry->value);
                printf("DEBUG: store_destroy - variable_unref completed\n");
            }
            printf("DEBUG: store_destroy - freeing entry\n");
            free(entry);
            entry = next;
        }
    }
    printf("DEBUG: store_destroy - freeing buckets\n");
    free(s->buckets);
    printf("DEBUG: store_destroy - freeing store\n");
    free(s);
    printf("DEBUG: store_destroy - completed\n");
}
