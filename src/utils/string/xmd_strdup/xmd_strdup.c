/**
 * @file xmd_strdup.c
 * @brief Duplicate string safely
 * @author XMD Development Team
 * @date 2025-08-01
 * 
 * Following Genesis "1→1→1" principle: 1 function → 1 file → 1 directory
 */

#include <string.h>
#include <stdlib.h>
#include "../../../../include/utils.h"
#include "../../../../utils/common/common_macros.h"
#include "../../../../utils/common/validation_macros.h"
/**
 * @brief Duplicate string safely
 * @param str String to duplicate
 * @return Duplicated string or NULL on failure
 */
char* xmd_strdup(const char* str) {
    XMD_VALIDATE_PTR_RETURN(str, NULL);
    
    size_t len = strlen(str);
    char* dup;
    XMD_MALLOC_VALIDATED(dup, char, len + 1, NULL);
    
    strcpy(dup, str);
    return dup;
}
