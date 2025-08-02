/**
 * @file template.h
 * @brief Template processing header
 * @author XMD Team
 *
 * Defines template processing system for variable interpolation
 * and expression evaluation in XMD documents.
 */

#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <stddef.h>
#include <stdbool.h>
#include "variable.h"
#include "store.h"

/**
 * @struct template_context
 * @brief Template processing context
 */
typedef struct template_context template_context;

/**
 * @brief Create a new template context
 * @param store Variable store for lookups
 * @return New template context or NULL on failure
 */
template_context* template_context_create(store* store);

/**
 * @brief Destroy template context and free memory
 * @param ctx Template context to destroy (can be NULL)
 */
void template_context_destroy(template_context* ctx);

/**
 * @brief Process template string with variable interpolation
 * @param ctx Template context
 * @param template Template string with {{variable}} syntax
 * @return Processed string (must be freed) or NULL on error
 */
char* template_process(template_context* ctx, const char* template);

/**
 * @brief Extract variable references from template
 * @param template Template string
 * @param count Output parameter for number of references
 * @return Array of variable names (must be freed) or NULL on error
 */
char** template_extract_variables(const char* template, size_t* count);

/**
 * @brief Check if template string contains variable references
 * @param template Template string to check
 * @return true if contains {{variable}} syntax, false otherwise
 */
bool template_has_variables(const char* template);

/**
 * @brief Validate template syntax
 * @param template Template string to validate
 * @return true if syntax is valid, false otherwise
 */
bool template_validate(const char* template);

#endif /* TEMPLATE_H */
