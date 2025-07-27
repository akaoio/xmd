/**
 * @file import_directive_free.c
 * @brief Import directive cleanup function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/import_export.h"

/**
 * @brief Free an import directive
 * @param directive Directive to free
 */
void import_directive_free(ImportDirective* directive) {
    if (!directive) {
        return;
    }
    
    free(directive->module_name);
    free(directive->symbol_name);
    free(directive->alias);
    free(directive->path);
    free(directive);
}