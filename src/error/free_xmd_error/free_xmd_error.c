/**
 * @file free_xmd_error.c
 * @brief XMD error cleanup function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/error.h"

/**
 * @brief Free XMDError structure
 * @param error Error to free
 */
void free_xmd_error(XMDError* error) {
    if (!error) {
        return;
    }
    
    free(error->message);
    free(error->file);
    free(error);
}