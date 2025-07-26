/**
 * @file config.c
 * @brief Configuration system - modular version
 * @author XMD Team
 *
 * This file has been refactored to comply with INSTRUCTIONS.md Rule 2:
 * All functions have been extracted to individual files.
 * Only includes and global variable definition remain.
 */

#include "../../include/config_internal.h"

// Global configuration instance definition
xmd_internal_config* g_config = NULL;

// No functions in this file - all extracted to separate files in subdirectories
// See */config_*.c for individual function implementations