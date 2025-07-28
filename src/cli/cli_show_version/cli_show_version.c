/**
 * @file cli_show_version.c
 * @brief CLI version display function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>

// External function to get version
extern const char* xmd_get_version(void);

#define XMD_BUILD_DATE __DATE__

/**
 * @brief Show CLI version
 */
void cli_show_version(void) {
    printf("XMD version %s\n", xmd_get_version());
    printf("Built on %s\n", XMD_BUILD_DATE);
}