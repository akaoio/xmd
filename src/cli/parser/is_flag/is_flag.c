/**
 * @file is_flag.c
 * @brief Check if argument is a flag
 * @author XMD Team
 */

#include "../../../../include/parser_internal.h"

/**
 * @brief Check if argument is a flag
 * @param arg Argument string
 * @return true if it's a flag, false otherwise
 */
bool is_flag(const char* arg) {
    return arg && arg[0] == '-';
}