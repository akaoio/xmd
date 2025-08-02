/**
 * @file config_internal.h
 * @brief Internal header for config system functions
 * @author XMD Team
 */

#ifndef CONFIG_INTERNAL_H
#define CONFIG_INTERNAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include "config.h"

// Global configuration instance (declaration)
extern xmd_internal_config* g_config;

// Function declarations
xmd_resource_limits create_default_limits(void);
xmd_buffer_config create_default_buffers(void);
xmd_paths_config create_default_paths(void);
xmd_security_config create_default_security(void);
xmd_timing_config create_default_timing(void);
xmd_precision_config create_default_precision(void);
xmd_internal_config* xmd_internal_config_new(void);
void free_paths_config(xmd_paths_config* paths);
void free_security_config(xmd_security_config* security);
void xmd_internal_config_free(xmd_internal_config* config);
size_t parse_env_size_t(const char* env_name, size_t default_value);
double parse_env_double(const char* env_name, double default_value);
bool parse_env_bool(const char* env_name, bool default_value);
int xmd_internal_config_load_env(xmd_internal_config* config);
int xmd_internal_config_load_file(xmd_internal_config* config, const char* file_path);
int xmd_internal_config_save_file(const xmd_internal_config* config, const char* file_path);
xmd_internal_config* xmd_internal_config_get_global(void);
void xmd_internal_config_set_global(xmd_internal_config* config);
int xmd_internal_config_add_module_path(xmd_internal_config* config, const char* path);
int xmd_internal_config_add_exec_whitelist(xmd_internal_config* config, const char* executable);
int xmd_internal_config_set_exec_whitelist(xmd_internal_config* config, const char** executables, size_t count);
int xmd_internal_config_load_whitelist_env(xmd_internal_config* config, const char* env_name);

#endif /* CONFIG_INTERNAL_H */
