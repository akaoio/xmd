/**
 * @file template_internal.h
 * @brief Internal header for template functions
 * @author XMD Team
 */

#ifndef TEMPLATE_INTERNAL_H
#define TEMPLATE_INTERNAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "template.h"
#include "variable.h"
#include "store.h"

/**
 * @brief Template processing context structure
 */
struct template_context {
    store* variable_store;  /**< Variable store for lookups */
};

// Internal function declarations
bool find_next_variable(const char* template, size_t start, 
                       size_t* var_start, size_t* var_end);
char* extract_variable_name(const char* template, size_t start, size_t end);

// Public function declarations
template_context* template_context_create(store* store);
void template_context_destroy(template_context* ctx);
char* template_process(template_context* ctx, const char* template);
char** template_extract_variables(const char* template, size_t* count);
bool template_has_variables(const char* template);
bool template_validate(const char* template);

#endif /* TEMPLATE_INTERNAL_H */
