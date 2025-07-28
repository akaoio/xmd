/**
 * @file get_version.c
 * @brief Dynamic version detection implementation
 * @author XMD Team
 * @date 2025-07-28
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "version_info.h"

/**
 * @brief Get dynamically detected version string
 * @return Version string with git info if available
 */
char* get_version(void) {
    static char version_buffer[256] = {0};
    
    // If buffer is already filled, return it
    if (version_buffer[0] != '\0') {
        return version_buffer;
    }
    // Check if we have a git tag that matches the version
    if (strlen(XMD_GIT_TAG) > 0) {
        // This is a tagged release
        snprintf(version_buffer, sizeof(version_buffer), "%s", XMD_VERSION_STRING);
    } else if (strlen(XMD_GIT_COMMIT) > 0) {
        // This is a development build
        snprintf(version_buffer, sizeof(version_buffer), "%s-dev+%s", 
                 XMD_VERSION_STRING, XMD_GIT_COMMIT);
    } else {
        // Fallback to just version string
        snprintf(version_buffer, sizeof(version_buffer), "%s", XMD_VERSION_STRING);
    }
    
    return version_buffer;
}

/**
 * @brief Get detailed version information
 * @return Detailed version info including build date and git info
 */
char* get_version_detailed(void) {
    static char detailed_buffer[512] = {0};
    
    // If buffer is already filled, return it
    if (detailed_buffer[0] != '\0') {
        return detailed_buffer;
    }
    snprintf(detailed_buffer, sizeof(detailed_buffer),
             "XMD v%s\n"
             "Git commit: %s\n"
             "Git branch: %s\n"
             "Build date: %s\n"
             "Build type: %s",
             get_version(),
             strlen(XMD_GIT_COMMIT) > 0 ? XMD_GIT_COMMIT : "unknown",
             strlen(XMD_GIT_BRANCH) > 0 ? XMD_GIT_BRANCH : "unknown",
             XMD_BUILD_DATE,
             XMD_BUILD_TYPE);
    
    return detailed_buffer;
}