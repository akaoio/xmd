/**
 * @file export_directive_free.c
 * @brief Free export directive
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/import_export.h"

/**
 * @brief Free an export directive
 * @param directive Directive to free
 */
void export_directive_free(ExportDirective* directive) {
    if (!directive) {
        return;
    }
    
    free(directive->symbol_name);
    if (directive->value) {
        variable_unref(directive->value);
    }
    free(directive);
}