#include <stdio.h>
#include <stdlib.h>
#include "include/flow.h"
#include "include/variable.h"

int main() {
    printf("=== Simple Flow Test ===\n");
    
    FlowContext* ctx = flow_context_new();
    variable* return_val = variable_create_boolean(1);
    
    printf("1. Initial status: %d\n", flow_check_status(ctx));
    
    flow_return_statement(ctx, return_val);
    printf("2. After return: %d (should be %d)\n", flow_check_status(ctx), FLOW_RETURN);
    
    flow_break_statement(ctx);
    printf("3. After break: %d (should still be %d)\n", flow_check_status(ctx), FLOW_RETURN);
    
    if (flow_check_status(ctx) == FLOW_RETURN) {
        printf("✓ PASS\n");
    } else {
        printf("✗ FAIL\n");
    }
    
    variable_unref(return_val);
    flow_context_free(ctx);
    
    return 0;
}