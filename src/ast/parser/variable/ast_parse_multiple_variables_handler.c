/**
 * @file ast_parse_multiple_variables_handler.c
 * @brief Implementation of ast_parse_multiple_variables_handler function
 * 
 * This file contains ONLY the ast_parse_multiple_variables_handler function.
 * One function per file - Genesis principle compliance.
 * Extracted from: src/ast_consolidated.c
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "ast_node.h"
#include "ast_parser.h"
#include "error.h"
#include "module.h"
#include "performance.h"
#include "store_internal.h"
#include "token.h"
#include "variable.h"
/**
 * @brief Parse assignment with Genesis comma disambiguation: set varname value
 * @param pos Pointer to current position
 * @return Assignment AST node or NULL (or program node for multiple assignments)
 */
// Static guard to prevent infinite recursion
