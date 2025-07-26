/**
 * @file import.c
 * @brief Import functionality implementation
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

/**
 * @brief Skip whitespace in string
 * @param str String pointer
 * @return Pointer to first non-whitespace character
 */
static const char* skip_whitespace(const char* str) {
    while (str && isspace(*str)) {
        str++;
    }
    return str;
}

/**
 * @brief Extract word from string
 * @param str String to extract from
 * @param word Output buffer for word (caller must free)
 * @param next Output pointer to next position in string
 * @return Length of extracted word, 0 if no word found
 */
static size_t extract_word(const char* str, char** word, const char** next) {
    if (!str || !word) {
        return 0;
    }
    
    str = skip_whitespace(str);
    if (!*str) {
        *word = NULL;
        *next = str;
        return 0;
    }
    
    const char* start = str;
    size_t len = 0;
    
    // Handle quoted strings
    if (*str == '"' || *str == '\'') {
        char quote = *str;
        str++; // Skip opening quote
        start = str;
        
        while (*str && *str != quote) {
            str++;
            len++;
        }
        
        if (*str == quote) {
            str++; // Skip closing quote
        }
    } else {
        // Regular word
        while (*str && !isspace(*str)) {
            str++;
            len++;
        }
    }
    
    if (len > 0) {
        *word = malloc(len + 1);
        if (*word) {
            strncpy(*word, start, len);
            (*word)[len] = '\0';
        }
    } else {
        *word = NULL;
    }
    
    *next = str;
    return len;
}

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

/**
 * @brief Import specific symbol from module
 * @param processor Import/export processor
 * @param module_name Module name or path
 * @param symbol_name Symbol to import
 * @param alias Alias for symbol (NULL for no alias)
 * @return ModuleResult indicating success/failure
 */
int import_symbol(ImportExportProcessor* processor, 
                 const char* module_name,
                 const char* symbol_name, 
                 const char* alias) {
    if (!processor || !module_name || !symbol_name) {
        return MODULE_ERROR;
    }
    
    // Find module in registry
    Module* module = module_registry_find(processor->registry, module_name);
    if (!module) {
        return MODULE_NOT_FOUND;
    }
    
    // Get exported variable
    variable* exported_var = module_get_export(module, symbol_name);
    if (!exported_var) {
        return MODULE_ERROR;
    }
    
    // Determine import name (alias or original name)
    const char* import_name = alias ? alias : symbol_name;
    
    // Add to current scope
    variable_ref(exported_var);
    bool result = store_set(processor->current_scope, import_name, exported_var);
    
    return result ? MODULE_SUCCESS : MODULE_ERROR;
}

/**
 * @brief Import all symbols from module
 * @param processor Import/export processor
 * @param module_name Module name or path
 * @return ModuleResult indicating success/failure
 */
int import_all_symbols(ImportExportProcessor* processor, const char* module_name) {
    if (!processor || !module_name) {
        return MODULE_ERROR;
    }
    
    // Find module in registry
    Module* module = module_registry_find(processor->registry, module_name);
    if (!module) {
        return MODULE_NOT_FOUND;
    }
    
    // Get all export keys
    size_t key_count = 0;
    char** keys = store_keys(module->exports, &key_count);
    if (!keys && key_count > 0) {
        return MODULE_ERROR;
    }
    
    // Import each exported symbol
    for (size_t i = 0; i < key_count; i++) {
        variable* exported_var = store_get(module->exports, keys[i]);
        if (exported_var) {
            variable_ref(exported_var);
            store_set(processor->current_scope, keys[i], exported_var);
        }
    }
    
    // Free keys array
    for (size_t i = 0; i < key_count; i++) {
        free(keys[i]);
    }
    free(keys);
    
    return MODULE_SUCCESS;
}
