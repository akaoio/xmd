/**
 * @file xmd_hash_key.c
 * @brief DJB2 hash function
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Following Genesis "1→1→1" principle: 1 function → 1 file → 1 directory
 */

#include <stddef.h>
#include "../../../../include/utils.h"
#include "utils/common/common_macros.h"
/**
 * @brief DJB2 hash function
 * @param key String to hash
 * @param capacity Hash table capacity
 * @return Hash value
 */
size_t xmd_hash_key(const char* key, size_t capacity) {
    XMD_VALIDATE_PTRS(0, key);
    if (capacity == 0) {
        return 0;
    }
    unsigned long hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return hash % capacity;
}
