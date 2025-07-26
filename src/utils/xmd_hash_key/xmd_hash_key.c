/**
 * @file xmd_hash_key.c
 * @brief String hash function
 * @author XMD Team
 */

#include "../../../include/utils_internal.h"

/**
 * @brief Calculate hash for a string key using djb2 algorithm
 * @param key String key to hash
 * @param capacity Capacity of hash table (for modulo)
 * @return Hash value
 */
size_t xmd_hash_key(const char* key, size_t capacity) {
    if (key == NULL) {
        return 0;
    }
    
    size_t hash = 5381;
    while (*key) {
        hash = ((hash << 5) + hash) + (unsigned char)*key;
        key++;
    }
    
    return hash % capacity;
}