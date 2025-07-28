# XMD Development Principles

Core principles that guide XMD development and ensure maintainable, reliable code.

## Core Philosophy

XMD follows strict architectural principles to maintain simplicity, testability, and modularity. These principles ensure the codebase remains manageable as it grows.

### Test-Driven Development
Implement comprehensive unit tests before writing implementation code. Tests must validate real-world scenarios and edge cases to ensure system reliability.

### Code Isolation
Enforce strict separation: one function per file, one file per directory. This ensures modularity and maintainability through isolated code units.

### Naming Convention
Maintain naming consistency: function name = file name = directory name using snake_case. Structure: `parent/child/child.c` containing `child()` function.

### Code Organization
Place all reusable components in `src/common/` hierarchy. Eliminate code duplication by centralizing shared functionality. Example: `src/common/group/child/child.c`.

### File Size Constraints
Limit source files to maximum 200 lines of code. This enforces focused, single-purpose functions and maintains cognitive load within manageable bounds.

### Production-Ready Implementation
Prohibit placeholder code: no mocks, simplified stubs, TODO comments, or technical debt. All code must be complete, production-grade implementation.

### Documentation Standards
Create design notes before implementation: `docs/notes/<YYYYMMDD-HHMM-topic>.md` (≤100 lines). Use Doxygen-compatible comments with required tags: @brief, @struct, @input, @output. Update documentation and tests before code changes.

### Dependency Isolation
Prohibit external dependencies. Use exclusively standard C library (C17) and self-contained implementations to ensure portability and reduce attack surface.

### Implementation Planning
Mandatory planning before implementation: `docs/plans/<YYYYMMDD-HHMM-plan>/<phase>/phase-instructions.md`. Decompose work into phases with dedicated documentation per phase.

### Error Handling Protocol
Implement comprehensive error handling: return meaningful error codes, validate all inputs, handle edge cases. Every function must gracefully manage failure scenarios.

### Memory Management Discipline
Enforce strict memory hygiene: validate all pointers before use, free all allocated memory, implement RAII patterns. Zero tolerance for memory leaks or undefined behavior.

### Build System Architecture
Use CMake exclusively for build configuration. Prohibit manual Makefile edits. Organize artifacts: build outputs in `build/`, official tests in `test/`, temporary tests in `sandbox/`.

