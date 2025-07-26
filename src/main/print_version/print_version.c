/**
 * @file print_version.c
 * @brief Version information display function
 * @author XMD Team
 *
 * Implementation of version information display for the XMD main module.
 */

#include "../../../include/main_internal.h"

/**
 * @brief Print version information
 */
void print_version(void) {
    printf("XMD v%s\n", xmd_get_version());
    printf("eXtended MarkDown - Programmable markdown processor\n");
    printf("Copyright (c) 2024 XMD Project\n");
    printf("License: MIT\n");
}