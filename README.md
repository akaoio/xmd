# XMD - eXtended MarkDown

> **📖 [View Official Documentation](https://akaoio.github.io/xmd/)** | **🚀 [Quick Start Guide](docs/quick-start.md)** | **📚 [API Reference](docs/api/)**

**XMD** (eXtended MarkDown) transforms regular markdown into a powerful, programmable language while maintaining 100% markdown compatibility. Using invisible HTML comments with the `<!-- xmd: -->` namespace, XMD adds variables, control flow, system integration, and modular composition to markdown without breaking existing renderers.

## 🎯 Why XMD?

- **🆓 Completely Free**: Open source with no restrictions, subscriptions, or enterprise tiers
- **⚡ Zero Dependencies**: Single 2MB binary, no runtime requirements
- **🔒 Security First**: Sandboxed execution with granular permission controls
- **🚀 High Performance**: Sub-millisecond processing for most documents
- **🌍 Universal**: Works with any markdown renderer and platform
- **👥 AI-Friendly**: Perfect documentation format for both humans and AI systems

## ✨ Core Capabilities

### 🔧 Programming Constructs
- **Variables & Data Types**: Strings, numbers, arrays, objects with full JSON support
- **Control Flow**: if/else conditionals, for/while loops, try/catch error handling
- **Functions**: Built-in utilities and custom function definitions
- **Modules**: Import/export system for reusable components

### 🖥️ System Integration  
- **Command Execution**: Run shell commands with sandboxed permissions
- **File Operations**: Read/write files with access controls
- **Environment Access**: System variables and configuration management
- **Network Requests**: HTTP/API integration with security policies

### 🏗️ Advanced Features
- **Module System**: Import/export with selective symbol loading and re-export
- **Security Sandbox**: Command execution with granular permission controls
- **Memory Management**: Intelligent resource monitoring and limits
- **Performance Optimization**: Sub-millisecond processing with stress-tested reliability

## 🚀 Quick Start

### One-Line Installation

```bash
# Install with our automated script
curl -fsSL https://raw.githubusercontent.com/akaoio/xmd/main/install.sh | bash
```

### Manual Installation

```bash
# Download latest release
curl -L https://github.com/akaoio/xmd/releases/latest/download/xmd-linux-x64 -o xmd
chmod +x xmd
sudo mv xmd /usr/local/bin/

# Verify installation
xmd --version
```

### Build from Source

```bash
git clone https://github.com/akaoio/xmd.git
cd xmd
make clean && make
make test  # Run all 27 tests to verify build

# Install system-wide (optional)
sudo cp xmd /usr/local/bin/
```

### Your First XMD Document

Create `hello.md`:

```markdown
<!-- xmd:
set user="Developer"
set project="MyApp"
set tools=["git", "cmake", "gcc"]
-->

# 👋 Hello {{user}}!

Welcome to **{{project}}** development environment.

## 📊 System Status
- Current time: <!-- xmd:exec date "+%Y-%m-%d %H:%M:%S" -->
- System load: <!-- xmd:exec uptime | awk '{print $10,$11,$12}' -->
- Available memory: <!-- xmd:exec free -h | awk 'NR==2{print $7}' -->

<!-- xmd:if user == "Developer" -->
## 🛠️ Development Tools Ready
Your development environment is configured and ready to use!

<!-- xmd:for i in 1..3 -->
Tool {{i}}: Ready ✅
<!-- xmd:endfor -->

<!-- xmd:for tool in tools -->
- ✅ {{tool}}: <!-- xmd:exec which {{tool}} && echo "Available" || echo "Not found" -->
<!-- xmd:endfor -->
<!-- xmd:endif -->
```

Process with various options:

```bash
# Basic processing
xmd process hello.md -o hello-output.md

# With variables from command line
xmd process hello.md -v user="Alice" -v project="WebApp"

# Different output formats
xmd process hello.md --format html -o output.html
xmd process hello.md --format json -o output.json

# With execution tracing for debugging
xmd process hello.md --trace --debug

# Secure mode (disable command execution)
xmd process hello.md --no-exec
```

**Live Output:**
```markdown
# 👋 Hello Developer!

Welcome to **MyApp** development environment.

## 📊 System Status
- Current time: 2025-07-26 10:45:15
- System load: 0.45, 0.52, 0.48
- Available memory: 2.1Gi

## 🛠️ Development Tools Ready
Your development environment is configured and ready to use!

Tool 1: Ready ✅
Tool 2: Ready ✅
Tool 3: Ready ✅

- ✅ git: Available
- ✅ cmake: Available  
- ✅ gcc: Available
```

## 🎯 Command Line Reference

### Core Commands

```bash
# Process a file
xmd process <file> [options]

# Watch directory for changes and auto-process
xmd watch <input_dir> [output_dir] [options]

# Validate syntax without processing  
xmd validate <file>

# Show version information
xmd version

# Display help
xmd help
```

### Options

| Option | Description | Example |
|--------|-------------|---------|
| `-o, --output <file>` | Output file (default: stdout) | `xmd process doc.md -o output.md` |
| `--output-dir <dir>` | Output directory for watch command | `xmd watch src/ --output-dir dist/` |
| `-v, --variable <k=v>` | Set variables (multiple allowed) | `xmd process doc.md -v env=prod -v region=us` |
| `--config <file>` | Use configuration file | `xmd process doc.md --config settings.conf` |
| `--format <fmt>` | Output format: `markdown`, `html`, `json` | `xmd process doc.md --format html` |
| `--verbose` | Enable verbose output | `xmd watch src/ dist/ --verbose` |
| `--trace` | Enable execution tracing | `xmd process doc.md --trace` |
| `--debug` | Enable debug mode | `xmd process doc.md --debug` |
| `--no-exec` | Disable command execution | `xmd process doc.md --no-exec` |

### Output Formats

**Markdown (default)**
```bash
xmd process doc.md --format markdown
# Outputs processed markdown as-is
```

**HTML**
```bash
xmd process doc.md --format html
# Outputs complete HTML document with CSS styling
```

**JSON**
```bash  
xmd process doc.md --format json
# Outputs structured JSON with metadata:
# {
#   "status": "success",
#   "format": "json", 
#   "processor": "XMD v1.0.0",
#   "content": "processed content"
# }
```

### Variable Management

```bash
# Set single variable
xmd process doc.md -v name="Alice"

# Set multiple variables
xmd process doc.md -v env="production" -v region="us-east" -v debug=true

# Variables can be used in document - work in ALL contexts including markdown headers
# {{name}}, {{env}}, {{region}}, {{debug}}
```

### 🔍 Watch Command (Live Development)

The watch command provides a powerful live development workflow by automatically processing markdown files when they change.

**Shorthand Syntax:**
```bash
# Watch input directory, output to another directory
xmd watch src/ dist/

# Watch with specific format
xmd watch docs/ build/ --format html

# Watch with verbose output (recommended for development)
xmd watch project/ output/ --verbose
```

**Standard Option Syntax:**
```bash
# Using --output-dir option
xmd watch src/ --output-dir dist/ --format html

# Output to stdout (no output directory)
xmd watch src/ --verbose

# JSON format for API documentation  
xmd watch api-docs/ --output-dir dist/ --format json
```

**Key Features:**
- **🔄 Recursive Directory Scanning**: Finds `.md` files in all subdirectories
- **📁 Directory Structure Mirroring**: Preserves relative paths in output
- **⚡ Real-time Processing**: Detects file changes instantly
- **🎯 Format Control**: Output as `markdown`, `html`, or `json`
- **🛡️ All XMD Features**: Full support for variables, imports, commands, loops

**Example Development Workflow:**
```bash
# Start watching your documentation project
xmd watch docs/ dist/ --format html --verbose

# 🔍 Watching directory: docs/
# 📝 Monitoring .md files for changes...
# 📁 Output directory: dist/
# 📄 Output format: html
# 
# Found 5 markdown file(s):
#   docs/getting-started.md
#   docs/api/authentication.md
#   docs/guides/deployment.md
# 
# ✅ docs/getting-started.md → dist/getting-started.html
# ✅ docs/api/authentication.md → dist/api/authentication.html
# ✅ docs/guides/deployment.md → dist/guides/deployment.html
# 
# ✅ Initial processing complete. Watching for changes...
```

When you edit any `.md` file in the `docs/` directory (or subdirectories), XMD automatically reprocesses it and updates the corresponding output file with all XMD directives executed.

## 🆕 Latest Improvements (v1.0.0)

### ✅ **Complete Test Suite - 27/27 Tests Pass**
- **100% pass rate** across all functional and stress tests
- **Stress testing** with brutal panic battle tests (50-level nested loops, resource exhaustion)
- **Full integration testing** including multiline directives and security features

### 🎨 **Multiline Directive Support**
- **Clean multiline syntax**: Write multiple commands in single comment blocks
- **Cross-comment control flow**: `if/endif` and `for/endfor` span multiple comments
- **Enhanced readability**: No need for `<!-- xmd:` on every line

```markdown
<!-- xmd:
set name="Alice"
set role="admin"
set permissions=["read", "write", "admin"]
-->
```

### 🔍 **Enhanced Watch Command**
- **Recursive Directory Scanning**: Automatically finds `.md` files in all subdirectories
- **Directory Structure Mirroring**: Preserves relative paths in output directory
- **Shorthand Syntax**: `xmd watch src/ dist/` for quick development workflows
- **Multiple Output Formats**: Support for `markdown`, `html`, and `json` formats
- **Real-time Processing**: Instant file change detection and reprocessing

### 🔧 **Enhanced Variable Substitution**
- **Universal Support**: Variables work in ALL contexts including markdown headers (`# {{title}}`)
- **Complex Templates**: Multi-variable expressions in conditionals and loops
- **JSON Support**: Full object and array manipulation with dot notation

### 🎯 **Complete Control Flow**
- **Full Conditionals**: `if/elif/else/endif` with logical operators (`&&`, `||`, `!`)
- **Advanced Loops**: `for/endfor` with arrays, ranges, and complex collections
- **Error Handling**: `try/catch` blocks for robust error management

### 🚀 **Production-Ready CLI**
- **Shorthand Support**: `xmd input.md output.md` auto-converts to process commands
- **Stdin/Pipe Support**: Seamless integration with shell pipelines
- **Multiple Formats**: Output to markdown, HTML, JSON with proper formatting

### Debugging & Tracing

```bash
# Generate execution trace
xmd process doc.md --trace
# Creates doc.md.trace with detailed processing steps

# Debug mode with performance stats
xmd process doc.md --debug
# Shows processing time and memory usage

# Combined debugging
xmd process doc.md --trace --debug --format json
```

## 📖 Syntax Reference

<details>
<summary><b>🔢 Variables & Data Types</b></summary>

```markdown
<!-- xmd:
set name="Alice"
set age=25
set active=true
set scores=[95, 87, 92]
set user={"name": "Bob", "role": "admin"}
-->

Hello {{name}}, age {{age}}. Admin: {{user.role == "admin"}}
Your scores: {{scores[0]}}, {{scores[1]}}, {{scores[2]}}

<!-- Also supports single-line syntax -->
<!-- xmd:set temperature=22.5 -->
<!-- xmd:set status="online" -->
```

</details>

<details>
<summary><b>🔄 Control Flow</b></summary>

```markdown
<!-- Conditionals -->
<!-- xmd:if user.role == "admin" -->
## 🔧 Admin Panel
<!-- xmd:elif user.role == "editor" -->
## ✏️ Editor Dashboard
<!-- xmd:else -->
## 👤 User Profile
<!-- xmd:endif -->

<!-- For loops with arrays -->
<!-- xmd:for server in servers -->
### {{server.name}} ({{server.env}})
Status: <!-- xmd:exec ping -c1 {{server.ip}} > /dev/null && echo "🟢 Online" || echo "🔴 Offline" -->
<!-- xmd:endfor -->

<!-- For loops with ranges -->
<!-- xmd:for i in 1..5 -->
- Item {{i}}
<!-- xmd:endfor -->

<!-- Advanced range patterns -->
<!-- xmd:for i in start..end -->    <!-- Variables as range bounds -->
<!-- xmd:for i in 10..1 -->         <!-- Reverse ranges -->
<!-- xmd:for i in var..5 -->        <!-- Mixed variable/literal -->
<!-- xmd:endfor -->

<!-- While loops -->
<!-- xmd:while count < 5 -->
- Item {{count}}
<!-- xmd:set count=count+1 -->
<!-- xmd:endwhile -->
```

</details>

<details>
<summary><b>⚡ Command Execution</b></summary>

```markdown
<!-- System information -->
- OS: <!-- xmd:exec uname -s -->
- Architecture: <!-- xmd:exec uname -m -->
- Kernel: <!-- xmd:exec uname -r -->
- Uptime: <!-- xmd:exec uptime -p -->

<!-- Git repository info -->
- Branch: <!-- xmd:exec git branch --show-current -->
- Last commit: <!-- xmd:exec git log -1 --pretty=format:"%h - %s (%cr)" -->
- Status: <!-- xmd:exec git status --porcelain | wc -l --> changes pending

<!-- Docker containers -->
<!-- xmd:exec docker ps --format "table {{.Names}}\t{{.Status}}" -->
```

</details>

<details>
<summary><b>📦 Modules & Imports</b></summary>

```markdown
<!-- Import templates and data -->
<!-- xmd:import header from "templates/header.md" -->
<!-- xmd:import config from "config/settings.json" -->
<!-- xmd:import servers from "data/servers.yaml" -->

# {{config.project_name}} Dashboard

<!-- xmd:for env in ["dev", "staging", "prod"] -->
## {{env|upper}} Environment

<!-- xmd:for server in servers[env] -->
### {{server.name}}
- URL: {{server.url}}
- Health: <!-- xmd:exec curl -sf {{server.url}}/health && echo "✅" || echo "❌" -->
<!-- xmd:endfor -->
<!-- xmd:endfor -->
```

</details>

<details>
<summary><b>🎨 Advanced Features</b></summary>

```markdown
<!-- Error handling -->
<!-- xmd:try -->
Database status: <!-- xmd:exec pg_isready -h localhost -->
<!-- xmd:catch -->
❌ Database connection failed
<!-- xmd:endtry -->

<!-- Custom functions -->
<!-- xmd:function formatBytes(bytes) -->
<!-- xmd:return bytes > 1024*1024*1024 ? (bytes/1024/1024/1024).toFixed(1) + "GB" : (bytes/1024/1024).toFixed(1) + "MB" -->
<!-- xmd:endfunction -->

Memory usage: {{formatBytes(memoryUsed)}}

<!-- Caching expensive operations -->
<!-- xmd:cache key="system_info" ttl=300 -->
System load: <!-- xmd:exec uptime | awk '{print $(NF-2)}' -->
<!-- xmd:endcache -->
```

</details>

## 🔧 Development & Building

### Prerequisites
- **C17 compatible compiler** (GCC 7+, Clang 6+, MSVC 2019+)
- **CMake 3.15+**
- **Git** for version control

### Build Commands

```bash
# Standard build
make

# Clean and rebuild
make clean && make

# Run all 27 tests (functional + stress)
make test

# Run specific stress tests manually
./test_brutal_nesting
./test_resource_exhaustion

# Clean build artifacts
./clean.sh
```

### Advanced Build Options

```bash
# Cross-compilation for ARM64
cmake -DCMAKE_TOOLCHAIN_FILE=cmake/arm64.cmake ..

# Static linking for distribution
cmake -DBUILD_STATIC=ON ..

# Enable AddressSanitizer for debugging
cmake -DENABLE_ASAN=ON ..

# Build with all features
cmake -DENABLE_ALL_FEATURES=ON ..
```

## 🚀 Use Cases & Examples

- **📋 [DevOps Automation](examples/devops/README.md)**: Live infrastructure monitoring and deployment reports
- **📚 [API Documentation](examples/api-docs/README.md)**: Self-updating API references with live examples  
- **🔍 [System Monitoring](examples/monitoring/README.md)**: Real-time system health dashboards
- **📊 [Data Reports](examples/reports/README.md)**: Dynamic data visualization and analysis
- **🏗️ [CI/CD Integration](examples/ci-cd/README.md)**: Build status and deployment pipelines

## 🛣️ Roadmap

**Current Status:** `v1.0.0` - Stable release with comprehensive testing

| Phase | Status | Features |
|-------|--------|----------|
| ✅ **Phase 1** | Complete | Core parser, variables, control flow |
| ✅ **Phase 2** | Complete | Command execution, modules, security sandbox |
| ✅ **Phase 3** | Complete | Multiline directives, stress testing, performance optimization |
| ✅ **Phase 4** | Complete | 27/27 tests passing, comprehensive documentation |
| 📋 **Phase 5** | Planned | Language bindings, IDE integrations, ecosystem tools |

See [implementation plan](docs/dev/plans/20250725-1413-xmd-implementation/) for detailed progress.

## 🤝 Community & Support

- **💬 [Discord Community](https://discord.gg/xmd)**: Real-time chat and support
- **📖 [Documentation](https://akaoio.github.io/xmd/)**: Complete guides and API reference
- **🐛 [Issue Tracker](https://github.com/akaoio/xmd/issues)**: Bug reports and feature requests
- **💡 [Discussions](https://github.com/akaoio/xmd/discussions)**: Ideas and community feedback
- **📧 [Mailing List](mailto:xmd-dev@googlegroups.com)**: Development updates

### Contributing

We welcome all contributions! Please see our [Contributing Guide](CONTRIBUTING.md) for:
- Code style guidelines
- Development setup
- Pull request process
- Community guidelines

**Quick ways to contribute:**
- 🐛 Report bugs or request features
- 📝 Improve documentation and examples
- 🧪 Add test cases and benchmarks
- 🔌 Create plugins and integrations
- 🌍 Translate documentation

## 📄 License

XMD is **completely free** and open source under the MIT License.

```
MIT License - Copyright (c) 2025 XMD Project

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

[Full license text in LICENSE file]
```

---

<div align="center">

**🌟 Star us on GitHub** | **🐦 Follow [@XMDProject](https://twitter.com/XMDProject)** | **💝 [Sponsor Development](https://github.com/sponsors/akaoio)**

*Made with ❤️ by developers, for developers*

</div>