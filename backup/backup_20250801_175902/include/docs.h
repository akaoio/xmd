/**
 * @file docs.h
 * @brief Documentation generation and management utilities
 * @author XMD Development Team
 */

#ifndef DOCS_H
#define DOCS_H

#include <stdbool.h>
#include <stddef.h>

/**
 * @brief Documentation configuration structure
 */
typedef struct docs_config {
    char* output_dir;          /**< Output directory for generated docs */
    char* header_dir;          /**< Header directory for source scanning */
    bool generate_examples;    /**< Generate example documentation */
    bool generate_reference;   /**< Generate API reference */
    bool generate_tutorials;   /**< Generate tutorial documentation */
    bool include_source;       /**< Include source code in docs */
} docs_config;

// Documentation generation API
docs_config* docs_create_default_config(void);
void docs_free_config(docs_config* config);
int docs_generate_all(const docs_config* config);

#endif /* DOCS_H */