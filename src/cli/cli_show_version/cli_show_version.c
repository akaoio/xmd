/**
 * @file cli_show_version.c
 * @brief CLI version display function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>

#define XMD_VERSION "1.0.0"
#define XMD_BUILD_DATE __DATE__

/**
 * @brief Show CLI version
 */
void cli_show_version(void) {
    printf("XMD version %s\n", XMD_VERSION);
    printf("Built on %s\n", XMD_BUILD_DATE);
}