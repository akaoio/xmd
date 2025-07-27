/**
 * @file export_parse_directive.c
 * @brief Parse export directive
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../../include/import_export.h"

/**
 * @brief Parse export directive from XMD comment
 * @param directive_text XMD directive text
 * @param scope Current variable scope
 * @param export_dir Output export directive (caller must free)
 * @return ModuleResult indicating success/failure
 */
int export_parse_directive(const char* directive_text, store* scope, 
                          ExportDirective** export_dir) {
    if (!directive_text || !scope || !export_dir) {
        return MODULE_ERROR;
    }
    
    *export_dir = NULL;
    
    // Skip leading whitespace
    directive_text = skip_whitespace(directive_text);
    
    // Check for "export" keyword
    if (strncmp(directive_text, "export", 6) != 0) {
        return MODULE_ERROR;
    }
    
    directive_text += 6;
    directive_text = skip_whitespace(directive_text);
    
    // Extract symbol name
    char* symbol_name = NULL;
    const char* pos = directive_text;
    
    if (extract_word(pos, &symbol_name, &pos) == 0) {
        return MODULE_ERROR;
    }
    
    // Check if symbol exists in scope
    variable* var = store_get(scope, symbol_name);
    if (!var) {
        free(symbol_name);
        return MODULE_ERROR;
    }
    
    // Create export directive
    *export_dir = export_directive_new(symbol_name, var);
    free(symbol_name);
    
    return *export_dir ? MODULE_SUCCESS : MODULE_ERROR;
}