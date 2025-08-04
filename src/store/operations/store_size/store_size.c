/**
 * @file store_size.c
 * @brief Implementation of store_size function
 * 
 * This file contains ONLY the store_size function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/store.c
 */

#include <stddef.h>
#include "../../../../include/store.h"
#include "../../../../include/store_internal.h"
#include "utils/common/common_macros.h"
/**
 * @brief Get store size
 */
size_t store_size(store* s) {
    XMD_NULL_CHECK(s, 0);
    return s->size;
}
