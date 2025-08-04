/**
 * @file xmd_expand_array.c
 * @brief Expand array capacity
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Following Genesis "1→1→1" principle: 1 function → 1 file → 1 directory
 */

#include <stddef.h>
#include "../../../../include/utils.h"
#include "../../../../utils/common/common_macros.h"
/**
 * @brief Expand array capacity
 * @param array Pointer to array pointer
 * @param current_capacity Current capacity
 * @param element_size Size of each element
 * @return New capacity or 0 on failure
 */
size_t xmd_expand_array(void** array, size_t current_capacity, size_t element_size) {
    XMD_VALIDATE_PTRS(0, array);
    if (element_size == 0) {
        return 0;
    }
    size_t new_capacity = current_capacity == 0 ? 1 : current_capacity * 2;
    void* new_array = xmd_realloc(*array, new_capacity * element_size);
    if (!new_array) {
        return 0;
    }
    *array = new_array;
    return new_capacity;
}
