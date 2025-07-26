/**
 * @file store_ops_internal.h
 * @brief Internal declarations for store operations
 * @author XMD Team
 */

#ifndef STORE_OPS_INTERNAL_H
#define STORE_OPS_INTERNAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/store.h"
#include "../include/variable.h"
#include "../include/utils.h"

// Store entry structure
typedef struct store_entry {
    char* key;                     /**< Variable name (owned) */
    variable* value;               /**< Variable value (referenced) */
    struct store_entry* next;      /**< Next entry in collision chain */
} store_entry;

// Store structure
struct store {
    store_entry** buckets;         /**< Hash table buckets */
    size_t capacity;               /**< Current capacity */
    size_t size;                   /**< Number of stored variables */
};

// Function prototypes
bool store_has(store* s, const char* name);
bool store_remove(store* s, const char* name);
void store_clear(store* s);
size_t store_size(store* s);
char** store_keys(store* s, size_t* count);

#endif /* STORE_OPS_INTERNAL_H */