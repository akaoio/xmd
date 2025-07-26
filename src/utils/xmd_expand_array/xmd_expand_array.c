/**
 * @file xmd_expand_array.c
 * @brief Array expansion utility function
 * @author XMD Team
 */

#include "../../../include/utils_internal.h"

/**
 * @brief Expand array capacity safely
 * @param ptr Pointer to array pointer
 * @param current_capacity Current capacity
 * @param element_size Size of each element
 * @return New capacity or 0 on failure
 */
size_t xmd_expand_array(void** ptr, size_t current_capacity, size_t element_size) {
    if (!ptr || element_size == 0) {
        return 0;
    }
    
    // Double capacity or start with 8 if capacity is 0
    size_t new_capacity = current_capacity > 0 ? current_capacity * 2 : 8;
    
    void* new_ptr = xmd_realloc(*ptr, new_capacity * element_size);
    if (!new_ptr) {
        return 0;
    }
    
    *ptr = new_ptr;
    return new_capacity;
}