# XMD Testing Infrastructure

## Overview

This directory contains the comprehensive testing infrastructure for the XMD language implementation, designed to ensure quality, performance, and compliance with the Genesis language specification.

## Test Suites

### 1. Basic Test Runner (`test_runner.sh`)
- **Purpose**: Quick validation of core XMD features
- **Tests**: 8 fundamental language features
- **Runtime**: ~1 minute
- **Use Case**: Quick sanity checks during development

### 2. Comprehensive Test Suite (`comprehensive_test_suite.sh`)
- **Purpose**: Full validation of all 20+ Genesis language features
- **Tests**: 90+ tests across 18 feature categories
- **Runtime**: ~5-10 minutes
- **Features Tested**:
  - Variables and assignments
  - Mathematical expressions
  - Conditionals (if/elif/else)
  - Loops (for/while)
  - Functions and methods
  - Arrays and objects
  - Classes and inheritance
  - Import/export system
  - Error handling
  - String operations
  - Async/await
  - Generators
  - Lambda functions
  - Formal logic
  - Shell execution
  - Markdown integration
  - HTML comment syntax

### 3. Deployment Readiness Checker (`deployment_readiness.sh`)
- **Purpose**: Verify system is production-ready
- **Checks**:
  - Build system integrity
  - Runtime stability
  - Core feature functionality
  - Memory safety
  - Documentation completeness
  - Genesis compliance
- **Output**: Pass/fail decision for deployment

### 4. Continuous Monitoring (`continuous_monitoring.sh`)
- **Purpose**: Automated continuous testing
- **Features**:
  - Runs tests every 5 minutes
  - Maintains test logs
  - Generates JSON status files
  - Cleans old logs automatically
- **Use Case**: CI/CD integration, monitoring dashboards

### 5. Performance Benchmarks (`performance_benchmark.sh`)
- **Purpose**: Measure execution performance
- **Benchmarks**:
  - Simple variable operations
  - Multiple variable handling
  - String interpolation
  - Large text processing
  - Mathematical expressions
  - Nested structures
  - Loop performance
- **Output**: Milliseconds per operation, JSON results

### 6. Test Report Generator (`generate_test_report.sh`)
- **Purpose**: Create comprehensive test reports
- **Formats**:
  - Markdown (human-readable)
  - HTML (web dashboard)
  - JSON (machine-readable)
- **Features**:
  - Executive summary
  - Detailed test results
  - Implementation status matrix
  - Recommendations
  - Historical tracking

## CI/CD Integration

### GitHub Actions Workflow (`.github/workflows/test.yml`)
- **Triggers**: Push to main/develop, pull requests
- **Jobs**:
  1. **Language Tests**: Runs all test suites
  2. **Memory Safety**: Valgrind analysis
  3. **Code Coverage**: LCOV reports
- **Features**:
  - Artifact uploads
  - PR comments with results
  - Coverage integration

## Usage

### Running Individual Test Suites

```bash
# Basic tests (quick)
./test_infrastructure/test_runner.sh

# All features (comprehensive)
./test_infrastructure/comprehensive_test_suite.sh

# Check deployment readiness
./test_infrastructure/deployment_readiness.sh

# Run performance benchmarks
./test_infrastructure/performance_benchmark.sh

# Generate test reports
./test_infrastructure/generate_test_report.sh
```

### Continuous Testing

```bash
# Start continuous monitoring
./test_infrastructure/continuous_monitoring.sh

# Monitor will run tests every 5 minutes
# Press Ctrl+C to stop
```

### CI/CD Pipeline

The testing infrastructure automatically runs on:
- Every push to main or develop branches
- All pull requests
- Manual workflow dispatch

## Directory Structure

```
test_infrastructure/
├── test_runner.sh                    # Basic test suite
├── comprehensive_test_suite.sh       # Full feature tests
├── deployment_readiness.sh           # Production checker
├── continuous_monitoring.sh          # Automated runner
├── performance_benchmark.sh          # Performance tests
├── generate_test_report.sh          # Report generator
├── README.md                        # This file
├── language_tests/                  # Generated test files
├── benchmarks/                      # Performance test files
├── reports/                         # Test reports
│   ├── latest.md                   # Latest markdown report
│   ├── latest.html                 # Latest HTML report
│   └── latest.json                 # Latest JSON report
└── logs/                           # Test execution logs
```

## Test Status Indicators

- ✅ **PASSED**: Feature working correctly
- ❌ **FAILED**: Feature has errors
- ⏭️ **SKIPPED**: Feature not yet implemented
- ⚠️ **PARTIAL**: Feature partially working

## Genesis Compliance

The test infrastructure ensures compliance with Genesis directives:
- Tests all 20+ specified language features
- No mock or stub implementations
- Real AST parser validation
- "Single source of truth" verification

## Contributing

When adding new XMD features:
1. Add tests to `comprehensive_test_suite.sh`
2. Update feature status in test reports
3. Ensure tests pass before marking complete
4. Run deployment readiness check

## Support

For issues with the testing infrastructure:
- Check test logs in `logs/` directory
- Review latest reports in `reports/`
- Ensure XMD binary is built before running tests
- Verify file permissions are correct