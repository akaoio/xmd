/**
 * @file import_export_processor_free.c
 * @brief Free import/export processor
 * @author XMD Implementation Team
 * @date 2025-07-27
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../include/import_export.h"

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