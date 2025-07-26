/**
 * @file xmd_check_null.c
 * @brief NULL pointer checking utility function
 * @author XMD Team
 */

#include "../../../include/utils_internal.h"

/**
 * @brief Check if pointer is NULL and handle error
 * @param ptr Pointer to check
 * @param error_msg Error message if NULL
 * @return true if NULL (error), false if valid
 */
bool xmd_check_null(const void* ptr, const char* error_msg) {
    if (!ptr) {
        if (error_msg) {
            fprintf(stderr, "Error: %s\n", error_msg);
        }
        return true;
    }
    return false;
}