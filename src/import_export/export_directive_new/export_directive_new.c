/**
 * @file export_directive_new.c
 * @brief Create new export directive
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/import_export.h"

/**
 * @brief Create a new export directive
 * @param symbol_name Symbol name
 * @param value Variable value
 * @return New export directive or NULL on error
 */
ExportDirective* export_directive_new(const char* symbol_name, variable* value) {
    if (!symbol_name || !value) {
        return NULL;
    }
    
    ExportDirective* directive = malloc(sizeof(ExportDirective));
    if (!directive) {
        return NULL;
    }
    
    directive->symbol_name = strdup(symbol_name);
    directive->value = value;
    variable_ref(value); // Increment reference count
    
    if (!directive->symbol_name) {
        free(directive);
        return NULL;
    }
    
    return directive;
}