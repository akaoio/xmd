/**
 * @file xmd_strcpy_safe.c
 * @brief Safe string copy with bounds checking
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Following Genesis "1→1→1" principle: 1 function → 1 file → 1 directory
 */

#include <string.h>
#include <stddef.h>
#include "../../../../include/utils.h"
#include "../../../utils/common/common_macros.h"
/**
 * @brief Safe string copy with bounds checking
 * @param dest Destination buffer
 * @param src Source string
 * @param dest_size Size of destination buffer
 * @return 0 on success, -1 on failure
 */
int xmd_strcpy_safe(char* dest, const char* src, size_t dest_size) {
    XMD_VALIDATE_PTRS(-1, dest, src);
    if (dest_size == 0) {
        return -1;
    }
    size_t src_len = strlen(src);
    if (src_len >= dest_size) {
        return -1; // Not enough space
    }
    strcpy(dest, src);
    return 0;
}
