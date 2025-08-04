/**
 * @file ast_evaluate_date.c
 * @brief Implementation of ast_evaluate_date function
 * 
 * This file contains ONLY the ast_evaluate_date function.
 * One function per file - Genesis principle compliance.
 * Evaluates Date operations (Date.now, Date(), .diff)
 */

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "variable.h"
#include "utils/common/common_macros.h"
#include "utils/common/validation_macros.h"
#include "date_functions.h"

/**
 * @brief Evaluate Date function call (Date.now, Date(), etc.)
 * @param node Function call AST node
 * @param evaluator AST evaluator context
 * @return Date value or NULL on error
 */
ast_value* ast_evaluate_date(ast_node* node, ast_evaluator* evaluator) {
    XMD_VALIDATE_PARAMS_2(NULL, node, evaluator);
    
    if (node->type != AST_FUNCTION_CALL) {
        XMD_ERROR_RETURN(NULL, "ast_evaluate_date called on non-function-call node");
    }
    
    const char* func_name = node->data.function_call.name;
    
    if (STR_EQUALS(func_name, "Date.now")) {
        // Return current timestamp
        double now = get_current_timestamp_ms();
        return ast_value_create_number(now);
    }
    else if (STR_EQUALS(func_name, "Date")) {
        if (node->data.function_call.argument_count > 0) {
            // Parse date from string argument
            ast_value* arg = ast_evaluate(node->data.function_call.arguments[0], evaluator);
            if (arg && arg->type == AST_VAL_STRING) {
                double timestamp = parse_date_string(arg->value.string_value);
                ast_value_free(arg);
                return ast_value_create_number(timestamp);
            }
            if (arg) ast_value_free(arg);
        }
        
        // Return current timestamp if no arguments
        double now = get_current_timestamp_ms();
        return ast_value_create_number(now);
    }
    else if (strstr(func_name, ".diff")) {
        // Handle date difference calculation
        // This would typically be called on a date object, but for simplicity
        // we'll treat it as a static method
        
        if (node->data.function_call.argument_count >= 2) {
            ast_value* date1 = ast_evaluate(node->data.function_call.arguments[0], evaluator);
            ast_value* date2 = ast_evaluate(node->data.function_call.arguments[1], evaluator);
            
            if (date1 && date2 && date1->type == AST_VAL_NUMBER && date2->type == AST_VAL_NUMBER) {
                const char* unit = "seconds";
                
                // Check for unit argument
                if (node->data.function_call.argument_count >= 3) {
                    ast_value* unit_arg = ast_evaluate(node->data.function_call.arguments[2], evaluator);
                    if (unit_arg && unit_arg->type == AST_VAL_STRING) {
                        unit = unit_arg->value.string_value;
                    }
                }
                
                double diff = calculate_date_diff(date1->value.number_value, 
                                                date2->value.number_value, 
                                                unit);
                
                ast_value_free(date1);
                ast_value_free(date2);
                
                return ast_value_create_number(diff);
            }
            
            if (date1) ast_value_free(date1);
            if (date2) ast_value_free(date2);
        }
        
        XMD_ERROR_RETURN(NULL, "Invalid arguments for date difference calculation");
    }
    
    XMD_ERROR_RETURN(NULL, "Unknown date function: %s", func_name);
}