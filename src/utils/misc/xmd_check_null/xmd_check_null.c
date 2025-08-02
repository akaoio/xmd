/**
 * @file xmd_check_null.c
 * @brief Check if pointer is NULL with error message
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Following Genesis "1→1→1" principle: 1 function → 1 file → 1 directory
 */

#include <stdio.h>
#include <stdbool.h>
#include "../../../../include/utils.h"
/**
 * @brief Check if pointer is NULL with error message
 * @param ptr Pointer to check
 * @param error_msg Error message to display if NULL
 * @return true if NULL, false otherwise
 */
bool xmd_check_null(const void* ptr, const char* error_msg) {
    if (ptr == NULL) {
        if (error_msg) {
            fprintf(stderr, "Error: %s\n", error_msg);
        }
        return true;
    }
    return false;
}
