/**
 * @file sandbox_internal.h
 * @brief Internal header for sandbox functions
 * @author XMD Team
 */

#ifndef SANDBOX_INTERNAL_H
#define SANDBOX_INTERNAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sandbox.h"

// Internal function declarations
int extract_command_name(const char* command, char* cmd_name, size_t cmd_name_size);

// Public function declarations
SandboxConfig* sandbox_config_new(void);
void sandbox_config_free(SandboxConfig* config);
int sandbox_config_add_whitelist(SandboxConfig* config, const char* command);
int sandbox_config_add_allowed_path(SandboxConfig* config, const char* path);
SandboxContext* sandbox_context_new(SandboxConfig* config);
void sandbox_context_free(SandboxContext* ctx);
int sandbox_check_command_allowed(SandboxContext* ctx, const char* command);
int sandbox_check_path_allowed(SandboxContext* ctx, const char* path);
int sandbox_apply_limits(SandboxContext* ctx);

#endif /* SANDBOX_INTERNAL_H */