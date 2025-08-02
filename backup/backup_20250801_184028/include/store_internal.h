/**
 * @file store_internal.h
 * @brief Internal header for store system functions
 * @author XMD Team
 */

#ifndef STORE_INTERNAL_H
#define STORE_INTERNAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "store.h"
#include "variable.h"
#include "utils.h"

#define INITIAL_CAPACITY 16
#define LOAD_FACTOR_THRESHOLD 0.75

/**
 * @struct store_entry
 * @brief Store entry for key-value pairs
 */
typedef struct store_entry {
    char* key;                     /**< Variable name (owned) */
    variable* value;               /**< Variable value (referenced) */
    struct store_entry* next;      /**< Next entry in collision chain */
} store_entry;

/**
 * @struct store
 * @brief Variable storage container
 */
struct store {
    store_entry** buckets;         /**< Hash table buckets */
    size_t capacity;               /**< Current capacity */
    size_t size;                   /**< Number of stored variables */
};

// Function declarations
store_entry* store_entry_create(const char* key, variable* value);
void store_entry_destroy(store_entry* entry);
bool store_resize(store* s);
bool store_has(store* s, const char* name);
bool store_remove(store* s, const char* name);
void store_clear(store* s);
size_t store_size(store* s);
char** store_keys(store* s, size_t* count);

#endif /* STORE_INTERNAL_H */
