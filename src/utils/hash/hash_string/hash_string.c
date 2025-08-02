/**
 * @file hash_string.c
 * @brief Simple hash function for strings
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Following Genesis "1→1→1" principle: 1 function → 1 file → 1 directory
 */

#include "../../../../include/utils.h"
/**
 * @brief Simple hash function for strings
 * @param key String key to hash
 * @return Hash value
 */
unsigned int hash_string(const char* key) {
    if (!key) {
        return 0;
    }
    unsigned int hash = 0;
    const char* p = key;
    while (*p) {
        hash = hash * 31 + *p;
        p++;
    }
    return hash;
}
