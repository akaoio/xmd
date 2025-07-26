/**
 * @file export.c
 * @brief Export functionality implementation
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
    
    if (!directive->symbol_name) {
        free(directive);
        return NULL;
    }
    
    // Add reference to the variable
    variable_ref(value);
    
    return directive;
}

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
 * @brief Extract symbol name from export directive
 * @param str String to extract from
 * @param symbol_name Output buffer for symbol name (caller must free)
 * @return Length of extracted symbol name, 0 if none found
 */
static size_t extract_symbol_name(const char* str, char** symbol_name) {
    if (!str || !symbol_name) {
        return 0;
    }
    
    str = skip_whitespace(str);
    if (!*str) {
        *symbol_name = NULL;
        return 0;
    }
    
    const char* start = str;
    size_t len = 0;
    
    // Symbol names can contain letters, numbers, and underscores
    while (*str && (isalnum(*str) || *str == '_')) {
        str++;
        len++;
    }
    
    if (len > 0) {
        *symbol_name = malloc(len + 1);
        if (*symbol_name) {
            strncpy(*symbol_name, start, len);
            (*symbol_name)[len] = '\0';
        }
    } else {
        *symbol_name = NULL;
    }
    
    return len;
}

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
    if (extract_symbol_name(directive_text, &symbol_name) == 0) {
        return MODULE_ERROR;
    }
    
    // Look up variable in scope
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

/**
 * @brief Export symbol to current module
 * @param processor Import/export processor
 * @param symbol_name Symbol name
 * @param value Variable value
 * @return ModuleResult indicating success/failure
 */
int export_symbol(ImportExportProcessor* processor, 
                 const char* symbol_name, 
                 variable* value) {
    if (!processor || !symbol_name || !value) {
        return MODULE_ERROR;
    }
    
    // Note: In a real implementation, we would need to track the current module
    // being processed. For now, we'll just add it to the current scope.
    // This would typically be done through a module context or processor state.
    
    variable_ref(value);
    bool result = store_set(processor->current_scope, symbol_name, value);
    
    return result ? MODULE_SUCCESS : MODULE_ERROR;
}

/**
 * @brief Create import/export processor
 * @param registry Module registry
 * @param scope Current variable scope
 * @return New processor or NULL on error
 */
ImportExportProcessor* import_export_processor_new(ModuleRegistry* registry, 
                                                   store* scope) {
    if (!registry || !scope) {
        return NULL;
    }
    
    ImportExportProcessor* processor = malloc(sizeof(ImportExportProcessor));
    if (!processor) {
        return NULL;
    }
    
    processor->registry = registry;
    processor->current_scope = scope;
    processor->last_error = NULL;
    
    return processor;
}

/**
 * @brief Free import/export processor
 * @param processor Processor to free
 */
void import_export_processor_free(ImportExportProcessor* processor) {
    if (!processor) {
        return;
    }
    
    free(processor->last_error);
    free(processor);
}

/**
 * @brief Set error message in processor
 * @param processor Import/export processor
 * @param message Error message
 */
static void set_processor_error(ImportExportProcessor* processor, const char* message) {
    if (!processor || !message) {
        return;
    }
    
    free(processor->last_error);
    processor->last_error = strdup(message);
}

/**
 * @brief Process import directive
 * @param processor Import/export processor
 * @param directive Import directive to process
 * @return ModuleResult indicating success/failure
 */
int import_process(ImportExportProcessor* processor, ImportDirective* directive) {
    if (!processor || !directive) {
        return MODULE_ERROR;
    }
    
    if (directive->symbol_name) {
        // Import specific symbol
        return import_symbol(processor, directive->module_name, 
                           directive->symbol_name, directive->alias);
    } else {
        // Import all symbols
        return import_all_symbols(processor, directive->module_name);
    }
}

/**
 * @brief Process export directive
 * @param processor Import/export processor
 * @param directive Export directive to process
 * @return ModuleResult indicating success/failure
 */
int export_process(ImportExportProcessor* processor, ExportDirective* directive) {
    if (!processor || !directive) {
        return MODULE_ERROR;
    }
    
    return export_symbol(processor, directive->symbol_name, directive->value);
}
