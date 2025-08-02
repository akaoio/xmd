/**
 * @file hash_key.c
 * @brief Implementation of hash_key function
 * 
 * This file contains ONLY the hash_key function.
 * One function per file - Genesis principle compliance.
 * 
 * Extracted from: src/store.c
 */

#include "store_internal.h"

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