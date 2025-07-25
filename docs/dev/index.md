---
title: XMD Development Documentation
description: Development documentation, architecture, and implementation plans for XMD
layout: default
---

# XMD Development Documentation

This section contains documentation for developers working on the XMD project.

## Core Documentation

- [Development Instructions](INSTRUCTIONS.md) - Coding standards and development rules
- [Product Requirements Document](PRD.md) - Product requirements and specifications
- [Doxygen Configuration](Doxyfile.in) - API documentation generation setup

## Architecture & Planning

- [Implementation Plans](plans/) - Detailed implementation roadmaps and phase documentation
- [Development Notes](notes/) - Development notes and decisions

## Implementation Phases

The project follows a structured implementation approach with documented phases:

- **Phase 1**: Core lexing and parsing
- **Phase 2**: Basic template processing
- **Phase 3**: Control flow (conditionals, loops)
- **Phase 4**: Command execution
- **Phase 5**: Module system
- **Phase 6**: Performance optimization
- **Phase 7**: CLI interface  
- **Phase 8**: Documentation and developer tools

See the [main implementation plan](plans/20250725-1413-xmd-implementation/) for detailed progress and specifications.

## Building & Testing

The project uses CMake for building and includes comprehensive test suites. See the main [project documentation](../) for build instructions.

```bash
# Build the project
mkdir build && cd build
cmake ..
make

# Run all tests
make test
```

---

[← Back to Main Documentation](../)