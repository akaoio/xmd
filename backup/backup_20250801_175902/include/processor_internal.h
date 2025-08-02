#ifndef XMD_PROCESSOR_INTERNAL_H
#define XMD_PROCESSOR_INTERNAL_H

#include <stdbool.h>
#include "xmd.h"
#include "store_ops_internal.h"
#include "config_internal.h"

/**
 * Internal processor structure for XMD
 * This replaces the stub implementation to properly manage state
 * Per Genesis directive: NO STUBS - ALL REAL IMPLEMENTATIONS
 */
struct xmd_processor {
    store* variables;           // Variable storage
    xmd_config* config;         // Configuration (owned copy)
    store* modules;             // Loaded modules cache
    store* functions;           // User-defined functions
    store* exports;             // Exported symbols
    void* ast_context;          // AST evaluator context
    bool initialized;           // Initialization state
    char* current_file;         // Current file being processed
};

#endif // XMD_PROCESSOR_INTERNAL_H
