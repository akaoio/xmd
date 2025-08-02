/**
 * @file module_internal.h
 * @brief Internal header for module functions
 * @author XMD Team
 */

#ifndef MODULE_INTERNAL_H
#define MODULE_INTERNAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include "module.h"

// Function declarations
Module* module_new(const char* name, const char* path);
void module_free(Module* module);
int module_load_content(Module* module);
int module_add_dependency(Module* module, const char* dependency_name);
int module_export(Module* module, const char* name, variable* value);
variable* module_get_export(Module* module, const char* name);
ModuleRegistry* module_registry_new(void);
void module_registry_free(ModuleRegistry* registry);
int module_registry_add_search_path(ModuleRegistry* registry, const char* path);
int module_registry_register(ModuleRegistry* registry, Module* module);
Module* module_registry_find(ModuleRegistry* registry, const char* name);
int module_registry_load(ModuleRegistry* registry, const char* name);
bool file_exists(const char* path);
int module_resolve_path(ModuleRegistry* registry, const char* name, char** resolved_path);

#endif /* MODULE_INTERNAL_H */
