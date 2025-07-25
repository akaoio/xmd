---
title: XMD - eXtended MarkDown
description: A programmable markdown processor that transforms regular markdown into a powerful programming language
layout: default
---

# XMD - eXtended MarkDown

[![Build Status](https://github.com/akaoio/xmd/workflows/CI/badge.svg)](https://github.com/akaoio/xmd/actions)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Version](https://img.shields.io/badge/version-1.0.0-blue.svg)](https://github.com/akaoio/xmd/releases)

XMD transforms regular markdown into a powerful programming language while maintaining 100% valid markdown syntax. It uses invisible HTML comments with the `<!-- xmd: -->` namespace to add programming capabilities like variables, control flow, system commands, and modular imports.

## Key Features

- **100% Markdown Compatible**: Works with any markdown renderer
- **Zero Dependencies**: Single 2MB binary, no runtime requirements  
- **Security First**: Sandboxed execution with granular permissions
- **High Performance**: Sub-millisecond processing for most documents
- **Language Agnostic**: No ecosystem lock-in, works everywhere

## Quick Start

### Installation

```bash
# Download latest release
curl -L https://github.com/akaoio/xmd/releases/latest/download/xmd-linux-x64 -o xmd
chmod +x xmd

# Or build from source
git clone https://github.com/akaoio/xmd.git
cd xmd
mkdir build && cd build
cmake ..
make
```

### Basic Usage

Create a file `example.md`:

```markdown
<!-- xmd:set name="World" -->
<!-- xmd:set time=now -->

# Hello {{name}}!

Current time: <!-- xmd:exec date -->

<!-- xmd:if name == "World" -->
Welcome to XMD!
<!-- xmd:endif -->
```

Process it:

```bash
./xmd process example.md
```

Output:
```markdown
# Hello World!

Current time: Fri Jul 25 14:30:22 UTC 2025

Welcome to XMD!
```

## Syntax Overview

### Variables

```markdown
<!-- xmd:set user="Alice" -->
<!-- xmd:set role="admin" -->
<!-- xmd:set count=42 -->

Hello {{user}}, you have {{count}} items.
```

### Control Flow

```markdown
<!-- xmd:if role == "admin" -->
## Admin Panel
You have administrative privileges.
<!-- xmd:else -->
## User Dashboard  
Welcome back, {{user}}!
<!-- xmd:endif -->

<!-- xmd:for item in items -->
- {{item.name}}: {{item.value}}
<!-- xmd:endfor -->
```

### Command Execution

```markdown
<!-- xmd:exec echo "System info:" -->
- OS: <!-- xmd:exec uname -s -->
- Kernel: <!-- xmd:exec uname -r -->
- Uptime: <!-- xmd:exec uptime -p -->
```

### Modules

```markdown
<!-- xmd:import header from "templates/header.md" -->
<!-- xmd:import config from "config.json" -->

# {{config.site_name}}

Server status: <!-- xmd:exec systemctl is-active nginx -->
```

## Building from Source

XMD uses CMake for building:

```bash
# Debug build
mkdir build && cd build
cmake ..
make

# Release build
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make

# Run tests
make test

# Enable coverage
cmake -DENABLE_COVERAGE=ON ..
make
```

## Project Status

XMD is currently in active development. See the [implementation plan](dev/plans/20250725-1413-xmd-implementation/) for detailed roadmap and progress.

## Resources

- [Source Code](https://github.com/akaoio/xmd)
- [Development Documentation](dev/)
- [Issue Tracker](https://github.com/akaoio/xmd/issues)
- [Releases](https://github.com/akaoio/xmd/releases)

## Contributing

We welcome contributions! Please see [CONTRIBUTING.md](https://github.com/akaoio/xmd/blob/main/CONTRIBUTING.md) for guidelines.

## License

MIT License - see [LICENSE](https://github.com/akaoio/xmd/blob/main/LICENSE) for details.