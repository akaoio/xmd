/**
 * @file config_globals.c
 * @brief Global configuration variables
 * 
 * This file contains global configuration state.
 * One purpose per file - Genesis principle compliance.
 */

#include "../../../include/config_internal.h"

// Global configuration instance
xmd_internal_config* g_config = NULL;

// Global audit state for security module
void* audit_state = NULL;