#include <stdio.h>
#include <stdlib.h>
#include "include/store.h"
#include "include/variable.h"
#include "include/ast_evaluator.h"

int main() {
    // Create store and set role = "admin"
    store* vars = store_create();
    variable* role_var = variable_create_string("admin");
    store_set(vars, "role", role_var);
    
    // Test the condition that should evaluate to true
    const char* condition = "role == \"admin\"";
    bool result = ast_evaluate_condition(condition, vars);
    
    printf("Condition: %s\n", condition);
    printf("Result: %s\n", result ? "true" : "false");
    
    // Check what the variable actually contains
    variable* check_var = store_get(vars, "role");
    if (check_var) {
        printf("Variable 'role' value: '%s'\n", variable_to_string(check_var));
    } else {
        printf("Variable 'role' not found\n");
    }
    
    store_destroy(vars);
    return 0;
}