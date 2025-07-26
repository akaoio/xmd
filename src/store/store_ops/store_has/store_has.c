/**
 * @file store_has.c
 * @brief Check if variable exists in store
 * @author XMD Team
 */

#include "../../../../include/store_ops_internal.h"

/**
 * @brief Check if variable exists in store
 * @param s Store instance
 * @param name Variable name
 * @return true if variable exists, false otherwise
 */
bool store_has(store* s, const char* name) {
    return store_get(s, name) != NULL;
}