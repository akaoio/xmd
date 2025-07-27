# 🚀 XMD Quick Start Guide

Welcome to XMD! This guide will get you up and running in under 5 minutes.

## Installation

### Option 1: One-Line Install (Recommended)

```bash
curl -fsSL https://raw.githubusercontent.com/akaoio/xmd/main/install.sh | bash
```

### Option 2: Manual Download

```bash
# Download for your platform
curl -L https://github.com/akaoio/xmd/releases/latest/download/xmd-linux-x64 -o xmd
chmod +x xmd
sudo mv xmd /usr/local/bin/

# Verify installation
xmd --version
```

### Option 3: Build from Source

```bash
git clone https://github.com/akaoio/xmd.git
cd xmd
make clean && make
make test  # Verify all 27 tests pass

# Install system-wide (optional)
sudo cp xmd /usr/local/bin/
```

## Your First XMD Document

Create a file called `hello.md`:

```markdown
<!-- xmd:
set name="World"
set services=["nginx", "docker", "postgresql"]
set environment="development"
-->

# Hello {{name}}! 👋

Welcome to XMD at <!-- xmd:exec date "+%Y-%m-%d %H:%M:%S" -->

## System Information
- Hostname: <!-- xmd:exec hostname -->
- OS: <!-- xmd:exec uname -s -->
- Environment: **{{environment}}**

<!-- xmd:if environment == "development" -->
## 🚀 Development Services Status
<!-- xmd:for service in services -->
- {{service}}: <!-- xmd:exec systemctl is-active {{service}} 2>/dev/null || echo "not installed" -->
<!-- xmd:endfor -->
<!-- xmd:endif -->
- User: <!-- xmd:exec whoami -->

<!-- xmd:if name == "World" -->
## Getting Started

You're running your first XMD document! Here are some next steps:

1. Try changing the `name` variable above
2. Add your own commands with `<!-- xmd:exec command -->`
3. Explore our [examples](examples/) for more ideas
<!-- xmd:endif -->
```

Process it with different options:

```bash
# Basic processing
xmd process hello.md

# With command-line variables
xmd process hello.md -v name="Alice" 

# Output to file with HTML format
xmd process hello.md -o output.html --format html

# Generate execution trace for debugging
xmd process hello.md --trace

# Safe mode (no command execution)
xmd process hello.md --no-exec
```

You'll see output like:

```markdown
# Hello World! 👋

Welcome to XMD at 2025-07-25 14:30:22

## System Information
- Hostname: mycomputer
- OS: Linux
- User: developer

## Getting Started

You're running your first XMD document! Here are some next steps:

1. Try changing the `name` variable above
2. Add your own commands with `<!-- xmd:exec command -->`
3. Explore our [examples](examples/) for more ideas
```

## Key Concepts

### 1. Variables

```markdown
<!-- Set variables -->
<!-- xmd:set project="MyApp" -->
<!-- xmd:set version="1.0.0" -->
<!-- xmd:set developers=["Alice", "Bob", "Charlie"] -->

# {{project}} v{{version}}

Team: {{developers[0]}}, {{developers[1]}}, and {{developers[2]}}
```

### 2. Commands

```markdown
<!-- Execute system commands -->
Current directory: <!-- xmd:exec pwd -->
Files count: <!-- xmd:exec ls -1 | wc -l -->
Disk usage: <!-- xmd:exec df -h / | tail -1 | awk '{print $5}' -->
```

### 3. Conditionals

```markdown
<!-- xmd:set environment="production" -->

<!-- xmd:if environment == "production" -->
🔴 **PRODUCTION** - Be careful!
<!-- xmd:elif environment == "staging" -->
🟡 **STAGING** - Testing environment
<!-- xmd:else -->
🟢 **DEVELOPMENT** - Safe to experiment
<!-- xmd:endif -->
```

### 4. Loops

```markdown
<!-- Array loops -->
<!-- xmd:set services=["web", "api", "db"] -->

## Service Status

<!-- xmd:for service in services -->
- **{{service}}**: <!-- xmd:exec systemctl is-active {{service}} 2>/dev/null || echo "inactive" -->
<!-- xmd:endfor -->

<!-- Range loops -->
<!-- xmd:for i in 1..5 -->
### Server {{i}}
Status: Checking...
<!-- xmd:endfor -->

<!-- Advanced ranges with variables -->
<!-- xmd:set start=1 -->
<!-- xmd:set end=3 -->
<!-- xmd:for port in start..end -->
- Port 808{{port}}: <!-- xmd:exec netstat -ln | grep :808{{port}} >/dev/null && echo "Open" || echo "Closed" -->
<!-- xmd:endfor -->
```

## Advanced Features

### Command-Line Variables

You can set variables directly from the command line:

```bash
# Set variables when processing
xmd process template.md -v env="production" -v version="2.1.0"

# Use in your document
# Environment: {{env}}
# Version: {{version}}
```

### Output Formats

Choose different output formats:

```bash
# HTML output with styling
xmd process doc.md --format html -o output.html

# JSON output with metadata  
xmd process doc.md --format json -o output.json

# Default markdown (same as no --format)
xmd process doc.md --format markdown
```

### Debugging & Tracing

Debug your documents with tracing:

```bash
# Generate detailed execution trace
xmd process complex.md --trace
# Creates complex.md.trace with step-by-step processing

# Enable debug information
xmd process doc.md --debug
# Shows processing time and memory usage

# Combine for full debugging
xmd process doc.md --trace --debug --format json
```

### Security Options

Control command execution:

```bash
# Safe mode - disable all command execution
xmd process untrusted.md --no-exec

# Use configuration file for detailed security settings
xmd process doc.md --config security.conf
```

## Common Use Cases

### DevOps Dashboard

Create `status.md`:

```markdown
<!-- xmd:set servers=["web1", "web2", "db1"] -->

# Infrastructure Status Report

Generated: <!-- xmd:exec date -->

## Server Health

<!-- xmd:for server in servers -->
### {{server}}
- Status: <!-- xmd:exec ping -c1 {{server}} >/dev/null 2>&1 && echo "🟢 Online" || echo "🔴 Offline" -->
- Load: <!-- xmd:exec ssh {{server}} "uptime | awk '{print \\$(NF-2)}'" 2>/dev/null || echo "N/A" -->
<!-- xmd:endfor -->
```

### API Documentation

Create `api-status.md`:

```markdown
<!-- xmd:set api_base="https://api.example.com" -->

# API Status

Base URL: {{api_base}}

## Endpoints

### Health Check
- URL: `{{api_base}}/health`
- Status: <!-- xmd:exec curl -s {{api_base}}/health | jq -r '.status' 2>/dev/null || echo "Down" -->

### Version
- Current: <!-- xmd:exec curl -s {{api_base}}/version | jq -r '.version' 2>/dev/null || echo "Unknown" -->
```

### Project README

Create `project-info.md`:

```markdown
<!-- xmd:set project_name="awesome-project" -->

# {{project_name}}

## Quick Stats

- Files: <!-- xmd:exec find . -type f -name "*.py" | wc -l --> Python files
- Lines of code: <!-- xmd:exec find . -name "*.py" -exec wc -l {} + | tail -1 | awk '{print $1}' -->
- Last commit: <!-- xmd:exec git log -1 --pretty=format:"%h - %s (%cr)" -->
- Contributors: <!-- xmd:exec git shortlog -sn | wc -l -->

## Recent Activity

<!-- xmd:exec git log --oneline -5 -->
```

## Next Steps

1. **Explore Examples**: Check out our [examples directory](examples/) for real-world use cases
2. **Read the Docs**: Visit our [full documentation](https://akaoio.github.io/xmd/) for advanced features
3. **Join the Community**: Connect with other users on [Discord](https://discord.gg/xmd)
4. **Contribute**: Help improve XMD by contributing on [GitHub](https://github.com/akaoio/xmd)

## Getting Help

- 📖 **Documentation**: [akaoio.github.io/xmd](https://akaoio.github.io/xmd/)
- 💬 **Discord**: [discord.gg/xmd](https://discord.gg/xmd)
- 🐛 **Issues**: [github.com/akaoio/xmd/issues](https://github.com/akaoio/xmd/issues)
- 💡 **Discussions**: [github.com/akaoio/xmd/discussions](https://github.com/akaoio/xmd/discussions)

---

**Happy documenting with XMD!** 🎉