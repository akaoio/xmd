/**
 * @file native_xmd.h  
 * @brief Native XMD system public API - Genesis's mobile-first programming language
 * @author XMD Team - Genesis Vision Implementation
 */

#ifndef NATIVE_XMD_H
#define NATIVE_XMD_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Evaluate native XMD program and return output
 * @param input Native XMD source code
 * @return Allocated string with program output (caller must free)
 */
char* native_evaluate_program(const char* input);

/**
 * @brief Dispatch XMD content to appropriate processor (HTML vs native)
 * @param content Input content to process
 * @return Processed output (caller must free)
 */
char* xmd_dispatch_content(const char* content);

/**
 * @brief Check if content uses Genesis's native syntax
 * @param content Input content to analyze
 * @return true if native XMD syntax detected
 */
bool xmd_is_native_syntax(const char* content);

/**
 * @brief Get syntax type name for debugging
 * @param content Input content to analyze  
 * @return Human-readable syntax type name
 */
const char* xmd_get_syntax_name(const char* content);

#ifdef __cplusplus
}
#endif

#endif /* NATIVE_XMD_H */
