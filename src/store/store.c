/**
 * @file store.c
 * @brief Variable store implementation
 * @author XMD Team
 *
 * Implementation of variable storage system using a hash table
 * for efficient variable lookup and management.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "store.h"
#include "variable.h"
#include "../../include/utils.h"

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

// hash_key function moved to utils.c as xmd_hash_key

/**
 * @brief Create a new store entry
 * @param key Entry key (will be copied)
 * @param value Entry value (reference will be taken)
 * @return New entry or NULL on failure
 */
static store_entry* store_entry_create(const char* key, variable* value) {
    if (key == NULL) {
        return NULL;
    }
    
    store_entry* entry = malloc(sizeof(store_entry));
    if (entry == NULL) {
        return NULL;
    }
    
    // Copy key
    size_t key_len = strlen(key);
    entry->key = malloc(key_len + 1);
    if (entry->key == NULL) {
        free(entry);
        return NULL;
    }
    strcpy(entry->key, key);
    
    // Reference value
    entry->value = variable_ref(value);
    entry->next = NULL;
    
    return entry;
}

/**
 * @brief Destroy a store entry
 * @param entry Entry to destroy (can be NULL)
 */
static void store_entry_destroy(store_entry* entry) {
    if (entry == NULL) {
        return;
    }
    
    free(entry->key);
    variable_unref(entry->value);
    free(entry);
}

/**
 * @brief Resize store hash table
 * @param s Store to resize
 * @return true on success, false on failure
 */
static bool store_resize(store* s) {
    if (s == NULL) {
        return false;
    }
    
    size_t old_capacity = s->capacity;
    store_entry** old_buckets = s->buckets;
    
    // Double capacity
    s->capacity *= 2;
    s->buckets = calloc(s->capacity, sizeof(store_entry*));
    if (s->buckets == NULL) {
        s->capacity = old_capacity;
        s->buckets = old_buckets;
        return false;
    }
    
    s->size = 0;
    
    // Rehash all entries
    for (size_t i = 0; i < old_capacity; i++) {
        store_entry* entry = old_buckets[i];
        while (entry != NULL) {
            store_entry* next = entry->next;
            
            // Rehash entry
            size_t hash = xmd_hash_key(entry->key, s->capacity);
            entry->next = s->buckets[hash];
            s->buckets[hash] = entry;
            s->size++;
            
            entry = next;
        }
    }
    
    free(old_buckets);
    return true;
}

/**
 * @brief Create a new variable store
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

/**
 * @brief Set a variable in the store
 * @param s Store instance
 * @param name Variable name
 * @param var Variable to store (reference will be taken)
 * @return true on success, false on failure
 */
bool store_set(store* s, const char* name, variable* var) {
    if (s == NULL || name == NULL || var == NULL) {
        return false;
    }
    
    // Check if resize is needed
    if ((double)s->size / s->capacity >= LOAD_FACTOR_THRESHOLD) {
        if (!store_resize(s)) {
            return false;
        }
    }
    
    size_t hash = xmd_hash_key(name, s->capacity);
    
    // Check if key already exists
    store_entry* entry = s->buckets[hash];
    while (entry != NULL) {
        if (strcmp(entry->key, name) == 0) {
            // Replace existing value
            variable_unref(entry->value);
            entry->value = variable_ref(var);
            return true;
        }
        entry = entry->next;
    }
    
    // Create new entry
    store_entry* new_entry = store_entry_create(name, var);
    if (new_entry == NULL) {
        return false;
    }
    
    // Insert at head of chain
    new_entry->next = s->buckets[hash];
    s->buckets[hash] = new_entry;
    s->size++;
    
    return true;
}

/**
 * @brief Get a variable from the store
 * @param s Store instance
 * @param name Variable name
 * @return Variable pointer or NULL if not found
 */
variable* store_get(store* s, const char* name) {
    if (s == NULL || name == NULL) {
        return NULL;
    }
    
    size_t hash = xmd_hash_key(name, s->capacity);
    
    store_entry* entry = s->buckets[hash];
    while (entry != NULL) {
        if (strcmp(entry->key, name) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    
    return NULL;
}

/**
 * @brief Check if variable exists in store
 * @param s Store instance
 * @param name Variable name
 * @return true if variable exists, false otherwise
 */
bool store_has(store* s, const char* name) {
    return store_get(s, name) != NULL;
}

/**
 * @brief Remove a variable from the store
 * @param s Store instance
 * @param name Variable name
 * @return true if removed, false if not found
 */
bool store_remove(store* s, const char* name) {
    if (s == NULL || name == NULL) {
        return false;
    }
    
    size_t hash = xmd_hash_key(name, s->capacity);
    store_entry** entry_ptr = &s->buckets[hash];
    
    while (*entry_ptr != NULL) {
        if (strcmp((*entry_ptr)->key, name) == 0) {
            store_entry* to_remove = *entry_ptr;
            *entry_ptr = to_remove->next;
            store_entry_destroy(to_remove);
            s->size--;
            return true;
        }
        entry_ptr = &(*entry_ptr)->next;
    }
    
    return false;
}

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

/**
 * @brief Get number of variables in store
 * @param s Store instance
 * @return Number of variables
 */
size_t store_size(store* s) {
    if (s == NULL) {
        return 0;
    }
    return s->size;
}

/**
 * @brief Get all variable names
 * @param s Store instance
 * @param count Output parameter for array size
 * @return Array of variable names (must be freed)
 */
char** store_keys(store* s, size_t* count) {
    if (s == NULL || count == NULL) {
        if (count) *count = 0;
        return NULL;
    }
    
    if (s->size == 0) {
        *count = 0;
        return NULL;
    }
    
    char** keys = malloc(s->size * sizeof(char*));
    if (!keys) {
        *count = 0;
        return NULL;
    }
    
    size_t key_index = 0;
    for (size_t i = 0; i < s->capacity; i++) {
        store_entry* entry = s->buckets[i];
        while (entry != NULL && key_index < s->size) {
            keys[key_index] = strdup(entry->key);
            key_index++;
            entry = entry->next;
        }
    }
    
    *count = key_index;
    return keys;
}
