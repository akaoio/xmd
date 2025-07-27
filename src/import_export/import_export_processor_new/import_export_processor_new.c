/**
 * @file import_export_processor_new.c
 * @brief Create new import/export processor
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/import_export.h"

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