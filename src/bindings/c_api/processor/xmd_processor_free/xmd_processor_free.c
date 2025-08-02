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
/**
 * @brief Free XMD processor and all resources
 * @param processor Processor to free
  * /
 */
void xmd_processor_free(xmd_processor* processor) {
    if (!processor) return;
    printf("DEBUG: xmd_processor_free starting\n");
    fflush(stdout);
    
    // Safely destroy stores with NULL checks
    if (processor->variables) {
        printf("DEBUG: About to destroy variables store\n");
        store_destroy(processor->variables);
        printf("DEBUG: Variables store destroyed\n");
    }
    
    if (processor->modules) {
        printf("DEBUG: About to destroy modules store\n");
        store_destroy(processor->modules);
        printf("DEBUG: Modules store destroyed\n");
    }
    
    if (processor->functions) {
        printf("DEBUG: About to destroy functions store\n");
        store_destroy(processor->functions);
        printf("DEBUG: Functions store destroyed\n");
    }
    
    if (processor->exports) {
        printf("DEBUG: About to destroy exports store\n");
        store_destroy(processor->exports);
        printf("DEBUG: Exports store destroyed\n");
    }
    
    if (processor->config) {
        printf("DEBUG: About to free config\n");
        free(processor->config);
        printf("DEBUG: Config freed\n");
    }
    
    if (processor->current_file) {
        printf("DEBUG: About to free current_file\n");
        free(processor->current_file);
        printf("DEBUG: Current_file freed\n");
    }
    
    printf("DEBUG: About to free processor\n");
    free(processor);
    printf("DEBUG: xmd_processor_free completed\n");
}
