/**
 * @file store_size.c
 * @brief Store size getter function
 * @author XMD Team
 *
 * Implementation of store size access for the XMD store system.
 */

#include "../../../include/store_internal.h"

/**
 * @brief Get number of variables in store
 * @param s Store instance
 * @return Number of variables in store
 */
size_t store_size(store* s) {
    if (s == NULL) {
        return 0;
    }
    return s->size;
}