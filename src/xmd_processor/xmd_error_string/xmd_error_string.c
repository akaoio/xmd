/**
 * @file xmd_error_string.c
 * @brief Get error string for error code implementation
 * @author XMD Team
 * @date 2025-07-26
 */

#include "../../../include/xmd_processor_internal.h"

/**
 * @brief Get error string for error code
 * @param code Error code to get string for
 * @return String description of error code
 */
const char* xmd_error_string(xmd_error_code code) {
    switch (code) {
        case XMD_SUCCESS: return "Success";
        case XMD_ERROR_INVALID_ARGUMENT: return "Invalid argument";
        case XMD_ERROR_OUT_OF_MEMORY: return "Out of memory";
        case XMD_ERROR_FILE_NOT_FOUND: return "File not found";
        case XMD_ERROR_PERMISSION: return "Permission denied";
        case XMD_ERROR_SYNTAX: return "Syntax error";
        case XMD_ERROR_TIMEOUT: return "Timeout";
        default: return "Unknown error";
    }
}
