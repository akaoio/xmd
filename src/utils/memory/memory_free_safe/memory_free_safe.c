/**
 * @file memory_free_safe.c
 * @brief Safe free with NULL pointer check
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Following Genesis "1→1→1" principle: 1 function → 1 file → 1 directory
 */

#include <stdlib.h>
#include "../../../../include/utils.h"
/**
 * @brief Safe free with NULL pointer check
 * @param ptr Pointer to pointer to free
 */
void memory_free_safe(void** ptr) {
    if (ptr && *ptr) {
        XMD_FREE_SAFE(*ptr);
        *ptr = NULL;
    }
}
