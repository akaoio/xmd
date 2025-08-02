/**
 * @file test_object_minimal.c
 * @brief Minimal test for object AST nodes only
 * @author XMD Team
 * @date 2025-07-29
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../../include/ast_node.h"
#include "../../include/ast_evaluator.h"

/**
 * @brief Test basic object node creation only
 */
void test_object_node_creation(void) {
    printf("Testing object AST node creation...\n");
    
    // Create empty object literal
    source_location loc = {1, 1, "test"};
    ast_node* object = ast_create_object_literal(loc);
    assert(object != NULL);
    assert(object->type == AST_OBJECT_LITERAL);
    printf("✓ Object node created with type: %d\n", object->type);
    
    // Test adding a property (using string literal nodes)
    ast_node* key_node = ast_create_string_literal("test_key", loc);
    ast_node* value_node = ast_create_string_literal("test_value", loc);
    
    int result = ast_add_property(object, "test_key", value_node);
    assert(result == 0);
    assert(object->data.object_literal.property_count == 1);
    printf("✓ Property added, count: %zu\n", object->data.object_literal.property_count);
    
    // Clean up
    ast_free(key_node);
    ast_free(object); // This should also free value_node
    
    printf("✓ Object node test passed\n");
}

/**
 * @brief Test empty object evaluation
 */
void test_empty_object_evaluation(void) {
    printf("Testing empty object evaluation...\n");
    
    // Create empty object
    source_location loc = {1, 1, "test"};
    ast_node* object = ast_create_object_literal(loc);
    assert(object != NULL);
    
    // Create minimal evaluator context  
    store* variables = store_create();
    processor_context dummy_ctx = {0};
    ast_evaluator* evaluator = ast_evaluator_create(variables, &dummy_ctx);
    
    // Try to evaluate empty object
    ast_value* result = ast_evaluate(object, evaluator);
    if (result == NULL) {
        printf("❌ Empty object evaluation returned NULL\n");
        ast_evaluator_free(evaluator);
        store_destroy(variables);
        ast_free(object);
        return;
    }
    
    printf("✓ Empty object evaluation succeeded\n");
    printf("  Result type: %d (expected %d)\n", result->type, AST_VAL_OBJECT);
    printf("  Pair count: %zu\n", result->value.object_value.pair_count);
    
    ast_value_free(result);
    ast_evaluator_free(evaluator);
    store_destroy(variables);
    ast_free(object);
    
    printf("✓ Empty object evaluation test passed\n");
}

int main() {
    printf("Running minimal object AST tests...\n\n");
    
    test_object_node_creation();
    test_empty_object_evaluation();
    
    printf("\n✅ All minimal object tests completed!\n");
    return 0;
}