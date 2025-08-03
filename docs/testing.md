# 🧪 Testing Guide

XMD has a comprehensive test suite ensuring reliability and stability across all features.

## 📊 Test Coverage Overview

**Total Tests: 27** (100% pass rate)

### Functional Tests (25 tests)
- **Core Components**: token, lexer, parser, variables, store
- **Control Flow**: conditionals, loops, error handling
- **System Integration**: executor, CLI, modules, security
- **Performance**: benchmarks, resource monitoring
- **Documentation**: docs validation, examples testing

### Stress Tests (2 tests)
- **Brutal Nesting**: 50-level nested loops and complex control structures
- **Resource Exhaustion**: Memory bombs, infinite loops, security attacks

## 🚀 Running Tests

### Quick Test Run

```bash
# Run all 27 tests
make test

# Expected output:
# 100% tests passed, 0 tests failed out of 27
# Total Test time (real) = ~1.92 sec
```

### Individual Test Categories

```bash
# Run functional tests only (built by default)
make test

# Run stress tests manually (not included in main suite by default)
./test_brutal_nesting
./test_resource_exhaustion
```

### Verbose Test Output

```bash
# Show detailed test information
ctest --verbose

# List all available tests
ctest -N
```

## 🎯 Test Categories

### 1. Core Engine Tests

**Token Tests** (`test_token_simple`)
- Token creation, duplication, equality
- Memory management and cleanup
- Type validation

**Lexer Tests** (`test_lexer`)
- XMD directive parsing
- HTML comment extraction
- Variable reference detection
- Multiline directive support

**Variable Tests** (`test_variable`)
- String, number, boolean, array types
- Object creation and manipulation
- Type conversion and validation

**Store Tests** (`test_store`)
- Variable storage and retrieval
- Scope management
- Memory cleanup

### 2. Processing Tests

**Template Tests** (`test_template`)
- Variable substitution
- Complex expressions
- Nested variable references

**Conditional Tests** (`test_conditional`)
- If/elif/else/endif blocks
- Logical operators (`&&`, `||`, `!`)
- Cross-comment conditionals

**Loop Tests** (`test_loop`)
- For loops with arrays and ranges
- While loops with conditions
- Nested loop structures

**Flow Control Tests** (`test_flow`)
- Break and continue statements
- Return values
- Error propagation

### 3. System Integration Tests

**Executor Tests** (`test_executor`)
- Command execution with sandboxing
- Timeout handling
- Error capture and processing

**CLI Tests** (`test_cli`)
- Argument parsing
- Shorthand detection
- Variable passing
- Output formatting

**Security Tests** (`test_security`)
- Path validation
- Command sandboxing
- Input sanitization

**Import/Export Tests** (`test_import_export`)
- Module loading and symbol resolution
- Selective imports
- Re-export functionality

### 4. Performance Tests

**Resource Tests** (`test_resource`)
- Memory usage monitoring
- Performance profiling
- Resource limiting

**Performance Tests** (`test_performance`)
- Benchmark execution
- Optimization validation
- Statistical analysis

### 5. Stress Tests

**Brutal Nesting Tests** (`test_brutal_nesting`)
```bash
./test_brutal_nesting
```
- **50-level nested loops**: Memory management under extreme nesting
- **Mixed nesting patterns**: for + if + while combinations
- **Large datasets**: 1000+ element arrays in nested loops
- **Malformed structures**: Error handling resilience

**Resource Exhaustion Tests** (`test_resource_exhaustion`)
```bash
./test_resource_exhaustion
```
- **Infinite loop detection**: Timeout and emergency break mechanisms
- **Variable explosion**: 1000+ variables with large content (memory bomb)
- **Command injection stress**: Security validation against attack vectors
- **Recursive templates**: Circular reference detection and limits

## 🔍 Test Implementation

### Test Structure

All tests follow INSTRUCTIONS.md Rule 2 (one function per file):

```c
// test/category/test_name.c
int main(void) {
    // Test setup
    // Test execution  
    // Assertions
    // Cleanup
    return 0;
}
```

### Memory Management Testing

All tests verify:
- ✅ No memory leaks
- ✅ Proper cleanup on error paths
- ✅ Null pointer checks
- ✅ Buffer overflow protection

### Error Handling Testing

Tests validate:
- ✅ Meaningful error codes returned
- ✅ Graceful handling of edge cases
- ✅ Error message clarity
- ✅ Recovery mechanisms

## 📈 Performance Benchmarks

### Typical Performance Metrics

**Small Documents (< 1KB)**
- Processing time: < 1ms
- Memory usage: < 100KB
- Test completion: < 0.01s

**Medium Documents (1-10KB)**
- Processing time: 1-5ms
- Memory usage: 100KB-1MB
- Test completion: < 0.1s

**Large Documents (> 10KB)**
- Processing time: 5-50ms
- Memory usage: 1-10MB
- Test completion: < 1s

**Stress Test Benchmarks**
- 50-level nesting: ~5ms processing time
- 1000+ variables: ~450ms processing time (memory intensive)
- Complex conditionals: ~10ms processing time

## 🛠️ Adding New Tests

### Test File Structure

```c
/**
 * @file test_new_feature.c
 * @brief Test implementation for new feature
 * @author XMD Team
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../include/xmd.h"

int main(void) {
    printf("🧪 Testing new feature...\n");
    
    // Test setup
    xmd_processor* processor = xmd_processor_create(NULL);
    assert(processor != NULL);
    
    // Test execution
    const char* input = "<!-- xmd set test=true -->{{test}}";
    xmd_result* result = xmd_process_string(processor, input, strlen(input));
    
    // Assertions
    assert(result != NULL);
    assert(result->error_code == XMD_SUCCESS);
    assert(strcmp(result->output, "true") == 0);
    
    // Cleanup
    xmd_result_free(result);
    xmd_processor_free(processor);
    
    printf("✅ New feature test passed\n");
    return 0;
}
```

### Adding to CMakeLists.txt

```cmake
# Add executable
add_executable(test_new_feature test/category/test_new_feature.c)
xmd_target_link_libraries(test_new_feature)

# Add to test suite
add_test(NAME new_feature_tests COMMAND test_new_feature)
```

## 🐛 Debugging Failed Tests

### Common Test Failures

**Memory Leaks**
```bash
# Run with valgrind
valgrind --leak-check=full ./test_name
```

**Segmentation Faults**
```bash
# Run with gdb
gdb ./test_name
(gdb) run
(gdb) bt  # Show backtrace on crash
```

**Performance Issues**
```bash
# Profile with perf
perf record ./test_name
perf report
```

### Test-Specific Debugging

**Stress Tests**
- Use `--debug` flag for detailed memory usage
- Check system resources during execution
- Monitor for infinite loops or hangs

**Integration Tests**
- Verify file permissions for command execution
- Check environment variables and paths
- Validate input/output file handling

## 📋 Test Maintenance

### Regular Test Updates

1. **Add tests for new features** following Rule 4 (test-driven development)
2. **Update tests when APIs change** to maintain compatibility
3. **Add edge cases** discovered in production usage
4. **Performance benchmarks** for optimization tracking

### Quality Assurance

- ✅ All tests must pass before commits
- ✅ No memory leaks in any test
- ✅ Tests must be deterministic (no flaky tests)
- ✅ Clear, descriptive test output

### Continuous Integration

```bash
# Pre-commit hook
make clean && make && make test

# Expected result: 27/27 tests passing
# Total time: < 2 seconds
# Memory usage: Stable and predictable
```

The XMD test suite ensures rock-solid reliability with comprehensive coverage of all features, from basic parsing to extreme stress scenarios.