# Brutal Panic Battle Tests - Stress Testing XMD Engine

**Date:** 2025-07-27 16:30  
**Author:** Claude  
**Status:** Adding extreme stress tests for XMD engine

## Objective

Create brutal panic battle tests to find edge cases and breaking points:
1. **Nested for loops với độ sâu vô hạn** (limited by system resources)
2. **Complex nested if/elif/else/endif** + deep nested for loops
3. **Memory stress tests** với large datasets
4. **Performance limits** và resource exhaustion

## Test Categories

### 1. Deep Nesting Tests
- **Infinite depth simulation**: 50+ levels nested for loops
- **Mixed nesting**: for + if + while + try/catch
- **Cross-comment nesting**: Multiline directives across multiple comments

### 2. Memory Stress Tests  
- **Large arrays**: 10,000+ elements in for loops
- **Deep recursion**: Template includes with circular references
- **Memory leaks**: Repeated allocations without cleanup

### 3. Resource Exhaustion
- **CPU stress**: Complex mathematical calculations in loops
- **I/O stress**: File operations trong nested loops
- **Time limits**: Long-running operations với timeouts

### 4. Edge Case Combinations
- **Malformed nested structures**: Unbalanced if/endif
- **Variable scope explosion**: 1000+ variables trong nested contexts
- **Command injection stress**: Security validation với complex inputs

## Implementation Plan (Following INSTRUCTIONS.md)

1. **Rule 17**: All tests in `test/stress/` (official tests)
2. **Rule 4**: Test-driven approach - write brutal tests first
3. **Rule 13**: Error handling - tests should validate error codes
4. **Rule 14**: Memory management - monitor for leaks

## Expected Outcomes

1. **Find breaking points** trong XMD engine
2. **Validate error handling** under extreme conditions  
3. **Performance benchmarks** for optimization
4. **Security validation** against resource attacks