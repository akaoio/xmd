/**
 * @file file_exists.c
 * @brief File existence checker function
 * @author XMD Team
 */

#include "../../../include/module_internal.h"

/**
 * @brief Check if file exists
 * @param path File path to check
 * @return true if file exists, false otherwise
 */
bool file_exists(const char* path) {
    struct stat st;
    return stat(path, &st) == 0 && S_ISREG(st.st_mode);
}