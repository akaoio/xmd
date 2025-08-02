/**
 * @file variable_create_null.c
 * @brief Implementation of variable_create_null function
 * 
 * This file contains ONLY the variable_create_null function.
 * One function per file - Genesis principle compliance.
 * 
 * Extracted from: src/variable.c
 */

#include <stdlib.h>

#include "variable.h"
#include "variable_internal.h"

/**
 * @file variable.c
 * @brief Consolidated variable system implementation
 * @author XMD Team
 *
 * Complete implementation of the XMD variable system with type safety,
 * reference counting, and support for all basic data types including
 * arrays and objects. This consolidates all variable operations into
 * a single file for better maintainability and performance.
 */

#define _GNU_SOURCE  // For strdup - must be before includes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>
#include <limits.h>
#include "../include/variable_internal.h"
#include "../include/utils.h"

/* ============================================================================
 * VARIABLE CREATION FUNCTIONS
 * ============================================================================ */

/**
 * @brief Create a new null variable
 * @return New null variable or NULL on failure
 */
/**
 * @file variable.c
 * @brief Consolidated variable system implementation
 * @author XMD Team
 *
 * Complete implementation of the XMD variable system with type safety,
 * reference counting, and support for all basic data types including
 * arrays and objects. This consolidates all variable operations into
 * a single file for better maintainability and performance.
 */

#define _GNU_SOURCE  // For strdup - must be before includes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>
#include <limits.h>
#include "../include/variable_internal.h"
#include "../include/utils.h"

/* ============================================================================
 * VARIABLE CREATION FUNCTIONS
 * ============================================================================ */

/**
 * @brief Create a new null variable
 * @return New null variable or NULL on failure
 */
variable* variable_create_null(void) {
    variable* var = xmd_malloc(sizeof(variable));
    if (var == NULL) {
        return NULL;
    }
    
    var->type = VAR_NULL;
    var->ref_count = 1;
    
    return var;
}