/**
 * @file store_create.c
 * @brief Implementation of store_create function
 * 
 * This file contains ONLY the store_create function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/store.c
 */

#include <stdlib.h>
#include "../../../include/store.h"
#include "../../../include/store_internal.h"
#include "../../../include/utils.h"
#include "../../utils/common/common_macros.h"

/**
 * @brief Create new store
 * @return New store instance or NULL on error
 */
store* store_create(void) {
    XMD_CREATE_VALIDATED(s, store, sizeof(store), NULL);
    
    s->capacity = 16;
    s->size = 0;
    XMD_CALLOC_STANDARD(s->buckets, s->capacity, store_entry*, NULL);
    return s;
}
