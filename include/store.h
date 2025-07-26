/**
 * @file store.h
 * @brief Variable store header
 * @author XMD Team
 *
 * Defines variable storage system for managing collections
 * of named variables with scoping support.
 */

#ifndef STORE_H
#define STORE_H

#include <stddef.h>
#include <stdbool.h>
#include "variable.h"

/**
 * @struct store
 * @brief Variable storage container
 */
typedef struct store store;

/**
 * @brief Create a new variable store
 * @return New store instance or NULL on failure
 */
store* store_create(void);

/**
 * @brief Destroy store and free memory
 * @param s Store to destroy (can be NULL)
 */
void store_destroy(store* s);

/**
 * @brief Set a variable in the store
 * @param s Store instance
 * @param name Variable name
 * @param var Variable to store (reference will be taken)
 * @return true on success, false on failure
 */
bool store_set(store* s, const char* name, variable* var);

/**
 * @brief Get a variable from the store
 * @param s Store instance
 * @param name Variable name
 * @return Variable pointer or NULL if not found
 */
variable* store_get(store* s, const char* name);

/**
 * @brief Check if variable exists in store
 * @param s Store instance
 * @param name Variable name
 * @return true if variable exists, false otherwise
 */
bool store_has(store* s, const char* name);

/**
 * @brief Remove a variable from the store
 * @param s Store instance
 * @param name Variable name
 * @return true if removed, false if not found
 */
bool store_remove(store* s, const char* name);

/**
 * @brief Clear all variables from store
 * @param s Store instance
 */
void store_clear(store* s);

/**
 * @brief Get number of variables in store
 * @param s Store instance
 * @return Number of variables
 */
size_t store_size(store* s);

/**
 * @brief Get all variable names
 * @param s Store instance
 * @param count Output parameter for array size
 * @return Array of variable names (must be freed)
 */
char** store_keys(store* s, size_t* count);

#endif /* STORE_H */
