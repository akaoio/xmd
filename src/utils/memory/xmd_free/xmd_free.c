/**
 * @file xmd_free.c
 * @brief Safe free wrapper
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Following Genesis "1→1→1" principle: 1 function → 1 file → 1 directory
 */

#include <stdlib.h>
#include "../../../../include/utils.h"
/**
 * @brief Safe free wrapper
 * @param ptr Pointer to free
 */
void ast_value_free(void* ptr) {
    if (ptr) {
        XMD_FREE_SAFE(ptr);
    }
}
