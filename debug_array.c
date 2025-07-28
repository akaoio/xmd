#include <stdio.h>
#include <stdlib.h>
#include "include/ast_evaluator.h"

int main() {
    const char* test_input = "[\"apple\", \"banana\", \"cherry\"]";
    printf("Testing array literal: %s\n", test_input);
    
    variable* result = ast_parse_array_literal(test_input);
    if (result) {
        printf("Success! Array created with %zu elements\n", variable_array_size(result));
        variable_unref(result);
    } else {
        printf("Failed to parse array literal\n");
    }
    
    return 0;
}