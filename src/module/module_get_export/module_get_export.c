/**
 * @file module_get_export.c
 * @brief Module export getter function
 * @author XMD Team
 */

#include "../../../include/module_internal.h"

/**
 * @brief Get exported variable from module
 * @param module Module to get from
 * @param name Variable name
 * @return Variable or NULL if not found
 */
variable* module_get_export(Module* module, const char* name) {
    if (!module || !name) {
        return NULL;
    }
    
    return store_get(module->exports, name);
}