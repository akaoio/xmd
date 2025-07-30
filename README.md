# XMD - eXtended MarkDown

A powerful markdown preprocessor that adds programming capabilities to markdown files with advanced scripting features.

## Features

- **Advanced Scripting**: Array literals, for loops, string concatenation with `+` operator
- **Dynamic Imports**: Import files using variables and expressions
- **Variables & Templates**: Define and use variables throughout your markdown
- **Command Execution**: Run shell commands and embed their output with dynamic buffer allocation
- **Control Flow**: If/else conditions and array iteration loops
- **Functions**: Built-in print() and cmd() functions
- **Multiline Support**: Clean syntax for complex operations with script-like blocks
- **Dynamic Content**: Generate content programmatically with full expression evaluation
- **Watch Mode**: Real-time file processing and monitoring

## Quick Start

```bash
# Install (downloads latest release)
curl -fsSL https://raw.githubusercontent.com/akaoio/xmd/main/install.sh | bash

# Verify installation
xmd version

# Process a file
xmd input.md -o output.md

# Process to stdout
xmd input.md

# Upgrade to latest version
xmd upgrade
```

## Syntax Examples

### Variables
```markdown
<!-- xmd: set name = "World" -->
Hello, {{name}}!
```

### Advanced Scripting with Arrays
```markdown
<!-- xmd:
set items = ["apple", "banana", "cherry"]
set result = ""
for item in items
    result += "- " + item + "\n"
-->
{{result}}
```

### Dynamic Imports
```markdown
<!-- xmd:
set files = ["config.md", "setup.md", "deploy.md"]
set content = ""
for file in files
    content += "## " + import file + "\n\n"
-->
{{content}}
```

### Command Execution
```markdown
<!-- xmd: exec date -->

<!-- xmd:
set files = exec ls -la
-->
Files: {{files}}
```

### Functions
```markdown
<!-- xmd:
set user = exec whoami
print(user)
-->
```

### Control Flow
```markdown
<!-- xmd: if exists("DEBUG") -->
Debug mode is ON
<!-- xmd: else -->
Debug mode is OFF  
<!-- xmd: endif -->
```

### Watch Mode
```bash
# Watch source directory and output to dist/
xmd watch src/ dist/

# Watch with custom patterns
xmd watch docs/ build/ --pattern "*.md"
```

## Team Collaboration & Agent Integration

XMD is perfect for team collaboration and AI agent coordination! Here's how to set up your collaborative workspace:

### Quick Setup for Teams/Agents

```bash
# 1. Clone XMD to your project
git clone https://github.com/akaoio/xmd.git
cd xmd

# 2. Build the project
./build.sh

# 3. Create team workspace
mkdir teamwork && cd teamwork
mkdir update  # Individual team member files go here
```

### Team Dashboard Template

Create `dashboard.md` in your teamwork directory:

```markdown
# Team Dashboard
Last updated: <!-- xmd:exec date '+%Y-%m-%d %H:%M:%S' -->

<!-- xmd:import update/developer.md -->
<!-- xmd:import update/designer.md -->
<!-- xmd:import update/tester.md -->
<!-- xmd:import update/coordinator.md -->

## Team Status
Members active: 4
```

### Individual Team Member Files

Each team member creates `update/<role>.md`:

```markdown
### Developer Update

**Role:** Backend Developer  
**Name:** Agent/Person Name  
**Status:** Working on authentication system

#### Progress:
- ✅ Database schema completed
- 🔄 API endpoints in progress
- ⏳ Testing pending

#### Next Steps:
- Complete API documentation
- Set up automated tests
```

### Live Dashboard with Watch Mode

```bash
# Auto-update dashboard when any team file changes
../xmd watch dashboard.md dashboard_output.md

# Now edit any file in update/ and see live updates!
```

### Agent Prompt Templates

**For AI Agents joining teamwork:**
```
You are now part of a collaborative XMD-based team. Your workspace is in `/teamwork/update/<your-role>.md`. 

Instructions:
1. Edit only your assigned file: update/<your-role>.md
2. Use the template format shown in README.md
3. Update your progress regularly
4. Dashboard auto-updates when you save

Your role file template:
```markdown
### <Your Role> Update

**Role:** <Your Specialization>
**Name:** <Agent Name/ID>
**Status:** <Current Task>

#### Progress:
- Status updates here

#### Next Steps:
- Planned tasks
```

Never edit dashboard.md directly - it's auto-generated.
```

**For Project Owners:**
```
To add XMD team collaboration to your project:

1. Add XMD as submodule: git submodule add https://github.com/akaoio/xmd.git
2. Create teamwork/ directory with dashboard.md template
3. Set up watch mode: xmd/xmd watch teamwork/dashboard.md teamwork/output.md
4. Give agents the workspace path and role templates

Your team can now collaborate in real-time with auto-updating dashboard!
```

## Documentation

- [Quick Start Guide](docs/quick-start.md)
- [CLI Reference](docs/cli-reference.md)
- [Multiline Directives](docs/multiline-directives.md)
- [Team Collaboration Guide](docs/collaboration.md)
- [Developer Guide](docs/dev/index.md)

## Contributing

1. Fork the repository
2. Create your feature branch: `git checkout -b feature/amazing-feature`
3. Commit your changes: `git commit -m 'Add amazing feature'`
4. Push to branch: `git push origin feature/amazing-feature`
5. Open a Pull Request

For AI agents: Use the team workspace setup above to collaborate with other contributors!

## License

MIT License - see [LICENSE](LICENSE) file for details.