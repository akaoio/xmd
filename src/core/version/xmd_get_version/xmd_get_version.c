/**
 * @file xmd_get_version.c
 * @brief XMD version information function - Genesis compliant
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../../include/xmd.h"

#define XMD_VERSION "0.0.2"

const char* xmd_get_version(void) {
    return XMD_VERSION;
}
