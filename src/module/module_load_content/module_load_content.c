/**
 * @file module_load_content.c
 * @brief Module content loading function
 * @author XMD Team
 */

#include "../../../include/module_internal.h"

/**
 * @brief Load module content from file
 * @param module Module to load
 * @return ModuleResult indicating success/failure
 */
int module_load_content(Module* module) {
    if (!module) {
        return MODULE_ERROR;
    }
    
    if (module->loaded) {
        return MODULE_ALREADY_LOADED;
    }
    
    FILE* file = fopen(module->path, "r");
    if (!file) {
        return MODULE_NOT_FOUND;
    }
    
    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    if (file_size < 0) {
        fclose(file);
        return MODULE_ERROR;
    }
    
    // Allocate buffer and read content
    module->content = malloc(file_size + 1);
    if (!module->content) {
        fclose(file);
        return MODULE_ERROR;
    }
    
    size_t bytes_read = fread(module->content, 1, file_size, file);
    module->content[bytes_read] = '\0';
    
    fclose(file);
    module->loaded = true;
    
    return MODULE_SUCCESS;
}