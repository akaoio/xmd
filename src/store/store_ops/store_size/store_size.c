/**
 * @file store_size.c
 * @brief Get number of variables in store
 * @author XMD Team
 */

#include "../../../../include/store_ops_internal.h"

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