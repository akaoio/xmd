# Cross-Platform Compatibility Issues

## Problem
Tests pass on Termux but fail on Armbian Orange Pi 5 (76% pass rate, 9/38 tests fail).

## Environment Differences
- **Termux**: Android userland, different libc implementation
- **Armbian Orange Pi 5**: aarch64, glibc 2.36, gcc 12.2.0, Linux 6.1.115-vendor-rk35xx

## Root Causes Analysis

### Memory Corruption
- `real_performance_tests`: "malloc(): corrupted top size" at 100KB file processing
- Indicates heap corruption, likely buffer overflow or double-free

### Segfaults (Empty Output)  
- `upgrade_version_tests`, `cli_e2e_tests`, `sandbox_tests`
- Immediate crashes suggest initialization issues or null pointer dereference

### Assertion Failures (String Handling)
- `truncate_fix_tests`: Line count assertion failed  
- `advanced_scripting_tests`: String concatenation failed
- `variable_advanced_tests`: String length assertion failed
- `multiline_enhanced_tests`: Output accumulation failed
- `advanced_integration_tests`: Documentation generation failed

## Technical Issues Identified
1. **Memory alignment**: Different architectures have different alignment requirements
2. **Buffer management**: Inadequate bounds checking in string operations  
3. **Null pointer handling**: Missing validation in critical paths
4. **Error propagation**: Poor error handling masking root causes

## Fix Strategy
Phase 1: Core memory and string handling
Phase 2: Platform-specific initialization  
Phase 3: Enhanced error handling and validation