/**
 * @file xmd_get_syntax_name.c
 * @brief XMD syntax name information function - Genesis compliant
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../../include/xmd.h"

#define XMD_SYNTAX_NAME "XMD"

const char* xmd_get_syntax_name(void) {
    return XMD_SYNTAX_NAME;
}
