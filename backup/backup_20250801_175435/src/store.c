/**
 * @file store.c
 * @brief Hash map storage system for variables
 * @author XMD Development Team
 * @date 2025-07-31
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/store_internal.h"
#include "../include/utils.h"

/**
 * @brief Simple hash function
 */
static unsigned int hash_key(const char* key) {
    unsigned int hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

/**
 * @brief Create new store
 */
store* store_create(void) {
    store* s = xmd_malloc(sizeof(store));
    if (!s) {
        return NULL;
    }
    
    s->capacity = 16;
    s->size = 0;
    s->buckets = xmd_calloc(s->capacity, sizeof(store_entry*));
    if (!s->buckets) {
        free(s);
        return NULL;
    }
    
    return s;
}

/**
 * @brief Destroy store
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
                fflush(stdout);
                variable_unref(entry->value);
                printf("DEBUG: store_destroy - variable_unref completed\n");
                fflush(stdout);
            }
            
            printf("DEBUG: store_destroy - freeing entry\n");
            fflush(stdout);
            free(entry);
            entry = next;
        }
    }
    
    printf("DEBUG: store_destroy - freeing buckets\n");
    fflush(stdout);
    free(s->buckets);
    printf("DEBUG: store_destroy - freeing store\n");
    fflush(stdout);
    free(s);
    printf("DEBUG: store_destroy - completed\n");
    fflush(stdout);
}

/**
 * @brief Set value in store
 */
bool store_set(store* s, const char* key, variable* value) {
    if (!s || !key || !value) {
        return false;
    }
    
    unsigned int index = hash_key(key) % s->capacity;
    store_entry* entry = s->buckets[index];
    
    // Check if key already exists
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            variable_unref(entry->value);
            entry->value = value;
            variable_ref(value);
            return true;
        }
        entry = entry->next;
    }
    
    // Create new entry
    entry = xmd_malloc(sizeof(store_entry));
    if (!entry) {
        return false;
    }
    
    entry->key = xmd_strdup(key);
    entry->value = value;
    variable_ref(value);
    entry->next = s->buckets[index];
    s->buckets[index] = entry;
    s->size++;
    
    return 0;
}

/**
 * @brief Get value from store
 */
variable* store_get(store* s, const char* key) {
    if (!s || !key) {
        return NULL;
    }
    
    unsigned int index = hash_key(key) % s->capacity;
    store_entry* entry = s->buckets[index];
    
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    
    return NULL;
}

/**
 * @brief Check if store has key
 */
bool store_has(store* s, const char* key) {
    return store_get(s, key) != NULL;
}

/**
 * @brief Remove key from store
 */
bool store_remove(store* s, const char* key) {
    if (!s || !key) {
        return false;
    }
    
    unsigned int index = hash_key(key) % s->capacity;
    store_entry* entry = s->buckets[index];
    store_entry* prev = NULL;
    
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            if (prev) {
                prev->next = entry->next;
            } else {
                s->buckets[index] = entry->next;
            }
            
            free(entry->key);
            variable_unref(entry->value);
            free(entry);
            s->size--;
            return true;
        }
        prev = entry;
        entry = entry->next;
    }
    
    return false;
}

/**
 * @brief Get store size
 */
size_t store_size(store* s) {
    return s ? s->size : 0;
}

/**
 * @brief Clear all entries from store
 */
void store_clear(store* s) {
    if (!s) {
        return;
    }
    
    for (size_t i = 0; i < s->capacity; i++) {
        store_entry* entry = s->buckets[i];
        while (entry) {
            store_entry* next = entry->next;
            free(entry->key);
            variable_unref(entry->value);
            free(entry);
            entry = next;
        }
        s->buckets[i] = NULL;
    }
    
    s->size = 0;
}

/**
 * @brief Get all keys from store
 * @param s Store
 * @param count Output count of keys
 * @return Array of key strings or NULL
 */
char** store_keys(store* s, size_t* count) {
    if (!s || !count) {
        if (count) *count = 0;
        return NULL;
    }
    
    // Count keys first
    size_t key_count = 0;
    for (size_t i = 0; i < s->capacity; i++) {
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
    char** keys = xmd_malloc(key_count * sizeof(char*));
    if (!keys) {
        *count = 0;
        return NULL;
    }
    
    // Fill array
    size_t idx = 0;
    for (size_t i = 0; i < s->capacity && idx < key_count; i++) {
        store_entry* entry = s->buckets[i];
        while (entry && idx < key_count) {
            keys[idx] = xmd_strdup(entry->key);
            idx++;
            entry = entry->next;
        }
    }
    
    *count = key_count;
    return keys;
}