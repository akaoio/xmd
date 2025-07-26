/**
 * @file import_export.h
 * @brief Import/Export system for XMD modules
 * @author XMD Implementation Team
 * @date 2025-07-25
 */

#ifndef IMPORT_EXPORT_H
#define IMPORT_EXPORT_H

#include <stddef.h>
#include "module.h"
#include "store.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Import directive structure
 */
typedef struct import_directive {
    char* module_name;          /**< Name/path of module to import */
    char* symbol_name;          /**< Symbol to import (NULL for all) */
    char* alias;                /**< Alias for imported symbol */
    char* path;                 /**< Resolved module path */
} ImportDirective;

/**
 * @brief Export directive structure
 */
typedef struct export_directive {
    char* symbol_name;          /**< Name of symbol to export */
    variable* value;            /**< Value to export */
} ExportDirective;

/**
 * @brief Import/Export processor
 */
typedef struct import_export_processor {
    ModuleRegistry* registry;   /**< Module registry */
    store* current_scope;       /**< Current variable scope */
    char* last_error;           /**< Last error message */
} ImportExportProcessor;

/**
 * @brief Create a new import directive
 * @param module_name Module name or path
 * @param symbol_name Symbol to import (NULL for all)
 * @param alias Alias for symbol (NULL for no alias)
 * @return New import directive or NULL on error
 */
ImportDirective* import_directive_new(const char* module_name, 
                                     const char* symbol_name,
                                     const char* alias);

/**
 * @brief Free an import directive
 * @param directive Directive to free
 */
void import_directive_free(ImportDirective* directive);

/**
 * @brief Create a new export directive
 * @param symbol_name Symbol name
 * @param value Variable value
 * @return New export directive or NULL on error
 */
ExportDirective* export_directive_new(const char* symbol_name, variable* value);

/**
 * @brief Free an export directive
 * @param directive Directive to free
 */
void export_directive_free(ExportDirective* directive);

/**
 * @brief Create import/export processor
 * @param registry Module registry
 * @param scope Current variable scope
 * @return New processor or NULL on error
 */
ImportExportProcessor* import_export_processor_new(ModuleRegistry* registry, 
                                                   store* scope);

/**
 * @brief Free import/export processor
 * @param processor Processor to free
 */
void import_export_processor_free(ImportExportProcessor* processor);

/**
 * @brief Parse import directive from XMD comment
 * @param directive_text XMD directive text
 * @param import_dir Output import directive (caller must free)
 * @return ModuleResult indicating success/failure
 */
int import_parse_directive(const char* directive_text, ImportDirective** import_dir);

/**
 * @brief Parse export directive from XMD comment
 * @param directive_text XMD directive text
 * @param scope Current variable scope
 * @param export_dir Output export directive (caller must free)
 * @return ModuleResult indicating success/failure
 */
int export_parse_directive(const char* directive_text, store* scope, 
                          ExportDirective** export_dir);

/**
 * @brief Process import directive
 * @param processor Import/export processor
 * @param directive Import directive to process
 * @return ModuleResult indicating success/failure
 */
int import_process(ImportExportProcessor* processor, ImportDirective* directive);

/**
 * @brief Process export directive
 * @param processor Import/export processor
 * @param directive Export directive to process
 * @return ModuleResult indicating success/failure
 */
int export_process(ImportExportProcessor* processor, ExportDirective* directive);

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
                 const char* alias);

/**
 * @brief Import all symbols from module
 * @param processor Import/export processor
 * @param module_name Module name or path
 * @return ModuleResult indicating success/failure
 */
int import_all_symbols(ImportExportProcessor* processor, const char* module_name);

/**
 * @brief Export symbol to current module
 * @param processor Import/export processor
 * @param symbol_name Symbol name
 * @param value Variable value
 * @return ModuleResult indicating success/failure
 */
int export_symbol(ImportExportProcessor* processor, 
                 const char* symbol_name, 
                 variable* value);

#ifdef __cplusplus
}
#endif

#endif /* IMPORT_EXPORT_H */
