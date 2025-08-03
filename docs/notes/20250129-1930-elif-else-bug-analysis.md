# elif/else Bug Analysis

## Date: 2025-01-29 19:30

## Summary
Analysis of the reported elif/else bug where both elif and else branches execute.

## Bug Investigation

### Code Flow Analysis

1. **if directive** (line 401-402):
   ```c
   ctx->if_stack[ctx->if_stack_size].condition_met = result;
   ctx->if_stack[ctx->if_stack_size].branch_executed = result;
   ```

2. **elif directive** (line 412-423):
   ```c
   if (!current->branch_executed) {
       // Evaluate elif condition
       current->condition_met = result;
       if (result) {
           current->branch_executed = true;
       }
   } else {
       current->condition_met = false;
   }
   ```

3. **else directive** (line 431):
   ```c
   current->condition_met = !current->branch_executed;
   ```

4. **should_execute_block** checks ALL stack levels:
   ```c
   for (int i = 0; i < ctx->if_stack_size; i++) {
       if (!ctx->if_stack[i].condition_met) {
           return false;
       }
   }
   ```

### Potential Bug Scenario

The bug might occur in this sequence:
1. `if false` - condition_met=false, branch_executed=false
2. `elif true` - condition_met=true, branch_executed=true
3. `else` - condition_met=false (because branch_executed=true)

At this point:
- The elif content has already been output
- The else sets condition_met=false
- But the content between elif and else was already processed

### Root Cause

The issue appears to be timing-related:
- Content is processed and output as it's parsed
- The else directive changes condition_met AFTER elif content is output
- There's no look-ahead to prevent outputting content before else

### Possible Fix

The fix would require:
1. Buffering content between conditional directives
2. Only outputting after the full if/elif/else chain is parsed
3. Or tracking execution state more precisely

### Testing Needed

Create test case:
```
<!-- xmd if false -->
Should not appear
<!-- xmd elif true -->
Should appear once
<!-- xmd else -->
Should not appear
<!-- xmd endif -->
```

If bug exists, both "Should appear once" and "Should not appear" would be output.

---
*Analysis by XOAI - elif/else Bug Investigation*