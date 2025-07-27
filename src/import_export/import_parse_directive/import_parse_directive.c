/**
 * @file import_parse_directive.c
 * @brief Import directive parsing function
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../../../include/import_export.h"

/**
 * @brief Parse import directive from XMD comment
 * @param directive_text XMD directive text
 * @param import_dir Output import directive (caller must free)
 * @return ModuleResult indicating success/failure
 */
int import_parse_directive(const char* directive_text, ImportDirective** import_dir) {
    if (!directive_text || !import_dir) {
        return MODULE_ERROR;
    }
    
    *import_dir = NULL;
    
    // Skip leading whitespace
    directive_text = skip_whitespace(directive_text);
    
    // Check for "import" keyword
    if (strncmp(directive_text, "import", 6) != 0) {
        return MODULE_ERROR;
    }
    
    directive_text += 6;
    directive_text = skip_whitespace(directive_text);
    
    char* symbol_name = NULL;
    char* alias = NULL;
    char* module_name = NULL;
    const char* pos = directive_text;
    
    // Parse symbol name or * for all
    if (*pos == '*') {
        pos++;
        symbol_name = NULL; // Import all
    } else {
        if (extract_word(pos, &symbol_name, &pos) == 0) {
            return MODULE_ERROR;
        }
    }
    
    pos = skip_whitespace(pos);
    
    // Check for "as" keyword (alias)
    if (strncmp(pos, "as", 2) == 0) {
        pos += 2;
        pos = skip_whitespace(pos);
        
        if (extract_word(pos, &alias, &pos) == 0) {
            free(symbol_name);
            return MODULE_ERROR;
        }
        
        pos = skip_whitespace(pos);
    }
    
    // Check for "from" keyword
    if (strncmp(pos, "from", 4) != 0) {
        free(symbol_name);
        free(alias);
        return MODULE_ERROR;
    }
    
    pos += 4;
    pos = skip_whitespace(pos);
    
    // Extract module name
    if (extract_word(pos, &module_name, &pos) == 0) {
        free(symbol_name);
        free(alias);
        return MODULE_ERROR;
    }
    
    // Create import directive
    *import_dir = import_directive_new(module_name, symbol_name, alias);
    
    free(symbol_name);
    free(alias);
    free(module_name);
    
    return *import_dir ? MODULE_SUCCESS : MODULE_ERROR;
}