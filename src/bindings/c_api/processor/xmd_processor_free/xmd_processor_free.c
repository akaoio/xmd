/**
 * @file xmd_processor_free.c
 * @brief Free XMD processor and all resources
 * 
 * This file contains ONLY the xmd_processor_free function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/bindings_consolidated.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "../../../../../include/xmd.h"
#include "../../../../../include/store.h"
#include "../../../../utils/common/common_macros.h"
/**
 * @brief Free XMD processor and all resources
 * @param processor Processor to free
  * /
 */
void xmd_processor_free(xmd_processor* processor) {
    if (!processor) return;
    fflush(stdout);
    
    // Safely destroy stores with NULL checks
    if (processor->variables) {
        store_destroy(processor->variables);
    }
    
    if (processor->modules) {
        store_destroy(processor->modules);
    }
    
    if (processor->functions) {
        store_destroy(processor->functions);
    }
    
    if (processor->exports) {
        store_destroy(processor->exports);
    }
    
    if (processor->config) {
        XMD_FREE_SAFE(processor->config);
    }
    
    if (processor->current_file) {
        XMD_FREE_SAFE(processor->current_file);
    }
    
    XMD_FREE_SAFE(processor);
}
