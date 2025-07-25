# XMD - eXtended MarkDown

[![Build Status](https://github.com/akaoio/xmd/workflows/CI/badge.svg)](https://github.com/akaoio/xmd/actions)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Version](https://img.shields.io/badge/version-1.0.0-blue.svg)](https://github.com/akaoio/xmd/releases)
[![C17](https://img.shields.io/badge/C-17-blue.svg)](https://en.wikipedia.org/wiki/C17_(C_standard_revision))
[![Documentation](https://img.shields.io/badge/docs-online-green.svg)](https://akaoio.github.io/xmd/)

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
- **Template System**: Parameterized content generation
- **Caching Layer**: Intelligent result caching for performance
- **Plugin Architecture**: Extend functionality with custom modules
- **Multi-threading**: Parallel execution for complex operations

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
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc)
sudo make install
```

### Your First XMD Document

Create `hello.md`:

```markdown
<!-- xmd:set user="Developer" -->
<!-- xmd:set project="MyApp" -->

# 👋 Hello {{user}}!

Welcome to **{{project}}** development environment.

## 📊 System Status
- Current time: <!-- xmd:exec date "+%Y-%m-%d %H:%M:%S" -->
- System load: <!-- xmd:exec uptime | awk '{print $10,$11,$12}' -->
- Available memory: <!-- xmd:exec free -h | awk 'NR==2{print $7}' -->

<!-- xmd:if user == "Developer" -->
## 🛠️ Development Tools Ready
Your development environment is configured and ready to use!

<!-- xmd:for tool in ["git", "cmake", "gcc"] -->
- ✅ {{tool}}: <!-- xmd:exec which {{tool}} && echo "Available" || echo "Not found" -->
<!-- xmd:endfor -->
<!-- xmd:endif -->
```

Process it:

```bash
xmd process hello.md -o hello-output.md
# or watch for changes
xmd watch hello.md
```

**Live Output:**
```markdown
# 👋 Hello Developer!

Welcome to **MyApp** development environment.

## 📊 System Status
- Current time: 2025-07-25 14:30:22
- System load: 0.45, 0.52, 0.48
- Available memory: 2.1Gi

## 🛠️ Development Tools Ready
Your development environment is configured and ready to use!

- ✅ git: Available
- ✅ cmake: Available  
- ✅ gcc: Available
```

## 📖 Syntax Reference

<details>
<summary><b>🔢 Variables & Data Types</b></summary>

```markdown
<!-- xmd:set name="Alice" -->
<!-- xmd:set age=25 -->
<!-- xmd:set active=true -->
<!-- xmd:set scores=[95, 87, 92] -->
<!-- xmd:set user={"name": "Bob", "role": "admin"} -->

Hello {{name}}, age {{age}}. Admin: {{user.role == "admin"}}
Your scores: {{scores[0]}}, {{scores[1]}}, {{scores[2]}}
```

</details>

<details>
<summary><b>🔄 Control Flow</b></summary>

```markdown
<!-- xmd:if user.role == "admin" -->
## 🔧 Admin Panel
<!-- xmd:elif user.role == "editor" -->
## ✏️ Editor Dashboard
<!-- xmd:else -->
## 👤 User Profile
<!-- xmd:endif -->

<!-- xmd:for server in servers -->
### {{server.name}} ({{server.env}})
Status: <!-- xmd:exec ping -c1 {{server.ip}} > /dev/null && echo "🟢 Online" || echo "🔴 Offline" -->
<!-- xmd:endfor -->

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
# Quick development build
make debug

# Optimized release build  
make release

# Run all tests
make test

# Code coverage analysis
make coverage

# Generate documentation
make docs

# Clean everything
make clean
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

**Current Status:** `v1.0.0-rc1` - Feature complete, stability testing

| Phase | Status | Features |
|-------|--------|----------|
| ✅ **Phase 1** | Complete | Core parser, variables, basic control flow |
| ✅ **Phase 2** | Complete | Command execution, modules, security sandbox |
| ✅ **Phase 3** | Complete | Advanced features, plugins, performance optimization |
| 🔄 **Phase 4** | In Progress | Testing, documentation, community tools |
| 📋 **Phase 5** | Planned | Language bindings, IDE integrations |

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