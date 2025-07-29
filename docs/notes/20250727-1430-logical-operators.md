# Logical Operators Implementation

## Overview
The conditional tests expect logical operators (&&, ||, !) but they aren't implemented.

## Required Functions (per INSTRUCTIONS.md Rule 2&3)
- `condition_logical_and/condition_logical_and.c` 
- `condition_logical_or/condition_logical_or.c`
- `condition_logical_not/condition_logical_not.c`

## Test Requirements
From test_conditional_simple.c:45-47:
```c
assert(condition_evaluate(ctx, " && ", s) == CONDITION_TRUE);
assert(condition_evaluate(ctx, " || ", s) == CONDITION_TRUE);  
assert(condition_evaluate(ctx, "!", s) == CONDITION_TRUE);
```

## Implementation Plan
1. Add logical operator constants to conditional.h
2. Implement parsing functions following existing pattern in condition.c
3. Update condition_evaluate.c to use new functions
4. Follow Rule 5: max 200 lines per file
5. Follow Rule 13: proper error handling
6. Follow Rule 14: memory management

## Architecture
Each operator gets its own function file per Rule 2.