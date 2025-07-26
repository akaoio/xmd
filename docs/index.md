---
title: XMD - eXtended MarkDown
description: Transform markdown into a powerful programming language while maintaining 100% compatibility
layout: default
---

<div align="center">

# XMD - eXtended MarkDown

[![Build Status](https://github.com/akaoio/xmd/workflows/CI/badge.svg)](https://github.com/akaoio/xmd/actions)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Version](https://img.shields.io/badge/version-1.0.0-blue.svg)](https://github.com/akaoio/xmd/releases)
[![C17](https://img.shields.io/badge/C-17-blue.svg)](https://en.wikipedia.org/wiki/C17_(C_standard_revision))
[![Documentation](https://img.shields.io/badge/docs-online-green.svg)](https://akaoio.github.io/xmd/)

**Transform markdown into a powerful programming language**  
*while maintaining 100% compatibility with existing renderers*

[**🚀 Get Started**](quick-start/) • [**📖 Documentation**](dev/) • [**💻 Examples**](https://github.com/akaoio/xmd/tree/main/examples) • [**💬 Community**](https://discord.gg/xmd)

</div>

---

## 🎯 What is XMD?

**XMD** (eXtended MarkDown) revolutionizes documentation by adding programming capabilities to markdown through invisible HTML comments. Write once, render everywhere – from static sites to dynamic dashboards.

```markdown
<!-- xmd:set user="Developer" -->
<!-- xmd:set servers=["web1", "web2", "db1"] -->

# Hello {{user}}! 👋

## Server Status (Live)
<!-- xmd:for server in servers -->
- **{{server}}**: <!-- xmd:exec ping -c1 {{server}} && echo "🟢 Online" || echo "🔴 Offline" -->
<!-- xmd:endfor -->

Updated: <!-- xmd:exec date "+%Y-%m-%d %H:%M:%S" -->
```

**Renders as:**
```markdown
# Hello Developer! 👋

## Server Status (Live)
- **web1**: 🟢 Online
- **web2**: 🟢 Online  
- **db1**: 🔴 Offline

Updated: 2025-07-25 14:30:22
```

## ✨ Why Choose XMD?

<div class="feature-grid">

### 🆓 **Completely Free**
Open source with no restrictions, subscriptions, or enterprise tiers. Built by developers, for developers.

### ⚡ **Zero Dependencies**
Single 2MB binary with no runtime requirements. Works on Linux, macOS, Windows, and more.

### 🔒 **Security First**
Sandboxed execution with granular permission controls. Your system stays safe.

### 🚀 **Lightning Fast**
Sub-millisecond processing for most documents. Real-time updates and live dashboards.

### 🌍 **Universal Compatibility**
Works with any markdown renderer. No vendor lock-in or proprietary formats.

### 👥 **AI & Human Friendly**
Perfect documentation format for both human readers and AI systems.

</div>

## 🚀 Get Started in 60 Seconds

### 1. Install XMD

```bash
# One-line installation
curl -fsSL https://raw.githubusercontent.com/akaoio/xmd/main/install.sh | bash

# Verify installation
xmd --version
```

### 2. Create Your First Document

Save this as `hello.md`:

```markdown
<!-- xmd:set name="World" -->
<!-- xmd:set project="XMD" -->

# Welcome to {{project}}, {{name}}! 🎉

## System Information
- **Time**: <!-- xmd:exec date "+%Y-%m-%d %H:%M:%S" -->
- **Host**: <!-- xmd:exec hostname -->
- **User**: <!-- xmd:exec whoami -->

<!-- xmd:if name == "World" -->
## Next Steps
1. Try changing the `name` variable above
2. Add your own system commands  
3. Explore our [examples](https://github.com/akaoio/xmd/tree/main/examples)
<!-- xmd:endif -->
```

### 3. Process and See the Magic

```bash
xmd process hello.md
```

**Live Output:**
```markdown
# Welcome to XMD, World! 🎉

## System Information
- **Time**: 2025-07-25 14:30:22
- **Host**: mycomputer
- **User**: developer

## Next Steps
1. Try changing the `name` variable above
2. Add your own system commands  
3. Explore our examples
```

<div align="center">
  <strong>🎊 That's it! You're now using programmable markdown!</strong>
</div>

## 🎨 Core Syntax

<div class="syntax-grid">

<div class="syntax-card">

### 🔢 Variables & Data
```markdown
<!-- xmd:set name="Alice" -->
<!-- xmd:set age=25 -->
<!-- xmd:set skills=["Python", "Go", "Rust"] -->
<!-- xmd:set user={"name": "Bob", "role": "admin"} -->

Hello {{name}}, you're {{age}} years old!
Skills: {{skills[0]}}, {{skills[1]}}, {{skills[2]}}
```

</div>

<div class="syntax-card">

### 🔄 Control Flow
```markdown
<!-- xmd:if user.role == "admin" -->
## 🔧 Admin Panel
<!-- xmd:else -->
## 👤 User Dashboard
<!-- xmd:endif -->

<!-- xmd:for skill in skills -->
- ✨ {{skill}}
<!-- xmd:endfor -->

<!-- xmd:for i in 1..5 -->
- Step {{i}}: Complete
<!-- xmd:endfor -->
```

</div>

<div class="syntax-card">

### ⚡ Command Execution
```markdown
<!-- System information -->
- OS: <!-- xmd:exec uname -s -->
- Uptime: <!-- xmd:exec uptime -p -->
- Load: <!-- xmd:exec uptime | awk '{print $(NF-2)}' -->

<!-- Git repository status -->
- Branch: <!-- xmd:exec git branch --show-current -->
- Status: <!-- xmd:exec git status --porcelain | wc -l --> changes
```

</div>

<div class="syntax-card">

### 📦 Modules & Templates
```markdown
<!-- xmd:import header from "templates/header.md" -->
<!-- xmd:import config from "config/settings.json" -->

# {{config.app_name}} Dashboard

<!-- xmd:for env in config.environments -->
## {{env|upper}} Environment
Status: <!-- xmd:exec curl -f {{config.urls[env]}}/health && echo "🟢" || echo "🔴" -->
<!-- xmd:endfor -->
```

</div>

</div>

## 🚀 Real-World Use Cases

<div class="use-cases">

### 📋 **DevOps Automation**
Create live infrastructure dashboards, deployment reports, and monitoring systems that update in real-time.

### 📚 **API Documentation**  
Build self-updating API docs with live endpoint testing, response examples, and status monitoring.

### 📊 **Business Reports**
Generate dynamic sales reports, analytics dashboards, and KPI summaries with live data integration.

### 🔍 **System Monitoring**
Monitor server health, application performance, and resource usage with automated alerting.

### 📖 **Living Documentation**
Create documentation that stays current with your codebase, automatically updating examples and references.

</div>

## 🌟 Community & Ecosystem

<div align="center">

### Join Our Growing Community

[![Discord](https://img.shields.io/discord/123456789?color=7289da&label=Discord&logo=discord&logoColor=white)](https://discord.gg/xmd)
[![GitHub Stars](https://img.shields.io/github/stars/akaoio/xmd?style=social)](https://github.com/akaoio/xmd)
[![GitHub Forks](https://img.shields.io/github/forks/akaoio/xmd?style=social)](https://github.com/akaoio/xmd/fork)

**💬 [Discord Chat](https://discord.gg/xmd)** • **🐛 [Report Issues](https://github.com/akaoio/xmd/issues)** • **💡 [Discussions](https://github.com/akaoio/xmd/discussions)** • **📚 [Examples](https://github.com/akaoio/xmd/tree/main/examples)**

## 📖 Documentation

### Getting Started
- **[🚀 Quick Start Guide](quick-start.md)** - Get running in under 5 minutes
- **[🔧 CLI Reference](cli-reference.md)** - Complete command-line documentation
- **[🔢 Range Syntax](range-syntax.md)** - Advanced range expressions for loops
- **[🔧 Troubleshooting](troubleshooting.md)** - Common issues and solutions

### Advanced Topics
- **[📘 Developer Guide](dev/)** - Architecture and development setup
- **[🔒 Security Guide](security.md)** - Security best practices and sandboxing
- **[⚡ Performance Guide](performance.md)** - Optimization tips and benchmarks
- **[🔌 Plugin Development](plugins.md)** - Creating custom extensions

</div>

### 🏗️ Built by the Community

XMD is **100% free and open source**, built by developers who believe great tools should be accessible to everyone.

- **No subscriptions** or enterprise tiers
- **No vendor lock-in** or proprietary formats  
- **No tracking** or data collection
- **No limits** on usage or distribution

### 🤝 Contributing

We welcome all contributions! Whether you're:

- **🐛 Reporting bugs** and requesting features
- **📝 Writing documentation** and tutorials  
- **💻 Contributing code** and improvements
- **🎨 Creating examples** and templates
- **💬 Helping others** in the community

Check out our [Contributing Guide](https://github.com/akaoio/xmd/blob/main/CONTRIBUTING.md) to get started.

## 📄 License & Credits

XMD is released under the **MIT License** - completely free for personal and commercial use.

```
MIT License - Copyright (c) 2025 XMD Project Contributors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software...
```

**Full license:** [LICENSE](https://github.com/akaoio/xmd/blob/main/LICENSE)

---

<div align="center">

**Ready to transform your documentation?**

[**🚀 Get Started Now**](quick-start/) • [**📖 Read the Docs**](dev/) • [**⭐ Star on GitHub**](https://github.com/akaoio/xmd)

*Made with ❤️ by developers, for developers*

</div>