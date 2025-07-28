<!-- xmd:
set principles = ["test_driven.md", "isolation.md", "naming.md", "organizing.md", "file_size_limits.md", "real_implementation.md", "documentation.md", "no_dependencies.md", "planning.md", "error_handling.md", "memory_management.md", "build_system.md"]
set content
for principle in principles
    content += "### " + import principle + "\n\n"
-->
# XMD Development Principles

Core principles that guide XMD development and ensure maintainable, reliable code.

## Core Philosophy

XMD follows strict architectural principles to maintain simplicity, testability, and modularity. These principles ensure the codebase remains manageable as it grows.

{{ content }}