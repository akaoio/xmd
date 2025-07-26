/**
 * @file store_has.c
 * @brief Store existence checker function
 * @author XMD Team
 *
 * Implementation of variable existence checking for the XMD store system.
 */

#include "../../../include/store_internal.h"

/**
 * @brief Check if store contains a variable
 * @param s Store instance
 * @param name Variable name
 * @return true if variable exists, false otherwise
 */
bool store_has(store* s, const char* name) {
    return store_get(s, name) != NULL;
}