/**
 * @file print_version.c
 * @brief Print XMD version information
 * 
 * Genesis Principle: 1 function → 1 file → 1 directory
 * Extracted from: src/main.c
 */

#include <stdio.h>

extern const char* xmd_get_version(void);

/**
 * @brief Print XMD version information
 */
void print_version(void) {
    printf("XMD v%s\n", xmd_get_version());
    printf("eXtended MarkDown - Programmable markdown processor\n");
    printf("Copyright (c) 2024 XMD Project\n");
    printf("License: MIT\n");
}
