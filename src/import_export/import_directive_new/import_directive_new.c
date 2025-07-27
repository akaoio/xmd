/**
 * @file import_directive_new.c
 * @brief Create new import directive
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../include/import_export.h"

/**
 * @brief Create a new import directive
 * @param module_name Module name or path
 * @param symbol_name Symbol to import (NULL for all)
 * @param alias Alias for symbol (NULL for no alias)
 * @return New import directive or NULL on error
 */
ImportDirective* import_directive_new(const char* module_name, 
                                     const char* symbol_name,
                                     const char* alias) {
    if (!module_name) {
        return NULL;
    }
    
    ImportDirective* directive = malloc(sizeof(ImportDirective));
    if (!directive) {
        return NULL;
    }
    
    directive->module_name = strdup(module_name);
    directive->symbol_name = symbol_name ? strdup(symbol_name) : NULL;
    directive->alias = alias ? strdup(alias) : NULL;
    directive->path = NULL;
    
    if (!directive->module_name) {
        import_directive_free(directive);
        return NULL;
    }
    
    return directive;
}
