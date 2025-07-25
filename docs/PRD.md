# Product Requirements Document: XMD - eXtended MarkDown

## Executive Summary

### Product Vision
XMD transforms markdown from a static documentation format into a dynamic, programmable language that maintains 100% markdown compatibility while enabling real-time data integration, conditional logic, and modular composition through invisible HTML comments.

### Mission Statement
To empower developers, DevOps engineers, and technical writers worldwide with a free, open source markdown processor that bridges the gap between static documentation and dynamic content generation, making powerful documentation tools accessible to everyone.

### Key Value Propositions

1. **Universal Compatibility**: Works with any markdown renderer, no special tooling required
2. **Zero Learning Curve**: Extends markdown with familiar programming concepts
3. **Language Agnostic**: Standalone C binary works anywhere, no runtime dependencies
4. **Security First**: Sandboxed execution with granular permission controls
5. **Performance Focused**: Sub-millisecond processing for most documents
6. **Completely Free**: Open source with no restrictions, subscriptions, or enterprise tiers

### Community Impact Goals

- **Global Accessibility**: Make advanced documentation tools available to everyone regardless of budget
- **Developer Empowerment**: Reduce documentation burden by 70% through automation
- **Knowledge Sharing**: Enable dynamic, self-updating documentation across all industries
- **Open Innovation**: Build a thriving ecosystem of community-contributed plugins and templates
- **Educational Impact**: Provide free tools for students, educators, and open source projects

## Problem Statement

### Current Pain Points

1. **Static Documentation Decay**
   - Documentation becomes outdated within weeks of creation
   - Manual updates are error-prone and time-consuming
   - No connection between docs and live system state

2. **Tool Accessibility Barriers**
   - Many solutions require expensive licenses or subscriptions
   - Complex setup procedures exclude casual users
   - Vendor lock-in prevents widespread adoption

3. **Fragmented Ecosystem**
   - MDX requires React ecosystem (excludes 70% of developers)
   - Static site generators require complex build pipelines
   - Template engines break markdown compatibility

4. **Documentation Inequality**
   - Small teams and individual developers lack access to enterprise documentation tools
   - Open source projects struggle with outdated documentation
   - Educational institutions can't afford commercial solutions

### Why Existing Solutions Fall Short

| Solution | Limitation | Impact |
|----------|------------|---------|
| MDX | React-only, requires bundler | Excludes non-React developers |
| Jekyll/Hugo | Build-time only, no runtime logic | Can't show live data |
| Commercial Tools | Expensive licenses, vendor lock-in | Inaccessible to many users |
| Jupyter Notebooks | Python-centric, heavyweight | Limited to data science use cases |

### User Frustrations

- "I spend 30% of my time updating documentation that could be automated"
- "Our open source project can't afford enterprise documentation tools"
- "I need something simple that just works without complex setup"
- "Why should basic documentation features cost hundreds per month?"

## Solution Overview

### How XMD Solves These Problems

XMD introduces programmability through HTML comments with the `<!-- xmd: -->` namespace, enabling:

```markdown
<!-- xmd:set env="production" -->
<!-- xmd:import servers from "config/servers.json" -->

# {{env}} Server Status Report

Generated: <!-- xmd:exec date -->

<!-- xmd:for server in servers[env] -->
## {{server.name}} ({{server.ip}})

Status: <!-- xmd:exec nc -zv {{server.ip}} {{server.port}} && echo "✅ Online" || echo "❌ Offline" -->

<!-- xmd:if server.metrics -->
### Performance Metrics
- CPU: <!-- xmd:exec ssh {{server.ip}} "top -bn1 | grep 'Cpu(s)' | awk '{print $2}'" -->%
- Memory: <!-- xmd:exec ssh {{server.ip}} "free -m | awk 'NR==2{printf \"%.2f%%\", $3*100/$2}'" -->
- Disk: <!-- xmd:exec ssh {{server.ip}} "df -h / | awk 'NR==2{print $5}'" -->
<!-- xmd:endif -->
<!-- xmd:endfor -->
```

### Core Capabilities

1. **Variable Management**: Set, reference, and compute with variables
2. **Control Flow**: Conditionals, loops, and error handling
3. **System Integration**: Execute commands with sandboxed permissions
4. **Modular Composition**: Import/export reusable components
5. **Data Processing**: JSON/YAML parsing, filtering, and transformation

### Technical Differentiators

- **Single Binary**: 2MB standalone executable, no dependencies
- **Streaming Parser**: Processes gigabyte files with constant memory
- **Parallel Execution**: Multi-threaded command execution
- **Caching Layer**: Intelligent result caching for repeated operations
- **Plugin Architecture**: Extend with custom functions via shared libraries

## User Personas & Journey

### Primary Personas

#### 1. DevOps Engineer - "Sarah"
- **Role**: Senior DevOps Engineer at a startup
- **Goals**: Automate infrastructure documentation, create self-updating runbooks
- **Pain Points**: Documentation drift, manual status reports, can't afford expensive tools
- **XMD Value**: Free, powerful tool for live infrastructure queries in markdown

**Journey Map**:
1. Discovers XMD through Hacker News post
2. Downloads single binary and tests with simple server status page (10 min)
3. Replaces weekly status report automation (2 hours)
4. Implements full runbook automation (2 days)
5. Advocates for team-wide adoption, contributes plugin back to community

#### 2. Open Source Maintainer - "Marcus"
- **Role**: Maintainer of popular open source ML library
- **Goals**: Keep documentation current, manage community contributions
- **Pain Points**: Documentation always outdated, manual example updates, no budget for tools
- **XMD Value**: Free automation that keeps docs synchronized with code

**Journey Map**:
1. Finds XMD while searching for free documentation tools
2. Converts project README to XMD format (30 min)
3. Automates API documentation generation (1 day)
4. Sets up automated examples from test suite (3 days)
5. Shares template with other open source projects

#### 3. Student/Educator - "Alex"
- **Role**: Computer Science student working on thesis
- **Goals**: Create dynamic documentation for research project
- **Pain Points**: University has no budget for commercial tools, need professional-quality output
- **XMD Value**: Professional-grade documentation tools available for free

### Secondary Personas

#### Small Business Owner - "Jordan"
- Uses XMD for automated system monitoring reports
- Values simplicity and zero cost over advanced features

#### Freelance Developer - "Riley"
- Uses XMD for client project documentation
- Needs professional results without subscription costs

## Features & Requirements

### Core Features

#### F1: Variable System
**User Story**: As a developer, I want to define and use variables so I can parameterize my documentation.

**Acceptance Criteria**:
- Set variables with `<!-- xmd:set key="value" -->`
- Reference with `{{variable}}` syntax
- Support nested objects and arrays
- Type inference and validation

#### F2: Control Flow
**User Story**: As a DevOps engineer, I want conditional content so I can show environment-specific information.

**Acceptance Criteria**:
- `if/else/elif` conditionals
- `for/while` loops with break/continue
- `try/catch` error handling
- Switch/case statements

#### F3: Command Execution
**User Story**: As a system admin, I want to embed command outputs so my docs show real system state.

**Acceptance Criteria**:
- Execute shell commands with `<!-- xmd:exec -->`
- Configurable timeout and retry logic
- Output formatting options (raw, JSON, table)
- Permission-based command whitelist

#### F4: Module System
**User Story**: As a technical writer, I want to reuse content components across documents.

**Acceptance Criteria**:
- Import with `<!-- xmd:import -->`
- Export with `<!-- xmd:export -->`
- Relative and absolute path resolution
- Circular dependency detection

### Security Requirements

#### S1: Sandboxed Execution
- All commands run in restricted environment
- No network access by default
- Limited filesystem access
- Resource limits (CPU, memory, time)

#### S2: Permission Model
```yaml
xmd:
  permissions:
    exec:
      whitelist:
        - "date"
        - "echo"
        - "curl https://api.internal/*"
      blacklist:
        - "rm"
        - "sudo"
    filesystem:
      read: ["./data", "/etc/config"]
      write: ["./output"]
    network:
      allow: ["internal.company.com"]
```

#### S3: Audit Trail
- Log all executed commands
- Track file access patterns
- User attribution for changes
- Security reporting for compliance

### Performance Requirements

| Metric | Target | Rationale |
|--------|--------|-----------|
| Parse time | <10ms per MB | Enable real-time processing |
| Command timeout | 30s default | Prevent hanging operations |
| Memory usage | <50MB for 1GB file | Support resource-constrained environments |
| Concurrent operations | 100+ threads | Scale for large projects |

### Platform Compatibility

- **Operating Systems**: Linux, macOS, Windows, BSD variants
- **Architectures**: x86_64, ARM64, RISC-V
- **Package Managers**: apt, yum, brew, chocolatey, cargo
- **Container Support**: Docker, Kubernetes, Lambda layers

## Technical Specifications

### Architecture Overview

```
┌─────────────────────┐
│   CLI Interface     │
├─────────────────────┤
│   Parser Engine     │
├─────────┬───────────┤
│  XMD    │  Plugin   │
│  Core   │  System   │
├─────────┴───────────┤
│  Security Sandbox   │
├─────────────────────┤
│   OS Interface      │
└─────────────────────┘
```

### CLI Interface

```bash
# Basic usage
xmd process input.md -o output.md

# With variables
xmd process template.md -v env=prod -v region=us-east

# Watch mode
xmd watch src/ -o dist/

# Security config
xmd process secure.md --config security.yaml

# Debug mode
xmd process debug.md --trace --explain
```

### API Specifications

```c
// Core API
typedef struct {
    char* (*process)(const char* markdown, xmd_config* config);
    void (*set_variable)(const char* key, xmd_value* value);
    xmd_value* (*get_variable)(const char* key);
    int (*execute_command)(const char* cmd, xmd_exec_opts* opts);
} xmd_api;

// Plugin API
typedef struct {
    const char* name;
    const char* version;
    xmd_function* functions;
    int function_count;
} xmd_plugin;
```

### Integration Capabilities

1. **Language Bindings**
   - Python: `pip install pyxmd`
   - Node.js: `npm install xmd`
   - Go: `go get github.com/akaoio/xmd-go`
   - Rust: `cargo add xmd`

2. **CI/CD Integration**
   - GitHub Actions: `xmd/process-action@v1`
   - GitLab CI: Native runner support
   - Jenkins: XMD plugin
   - CircleCI: Orb available

3. **Editor Support**
   - VSCode: Syntax highlighting, preview, debugging
   - Vim/Neovim: LSP integration
   - IntelliJ: Plugin with refactoring support
   - Sublime/Atom: Basic highlighting

## Success Metrics & KPIs

### Community Growth Metrics

| Metric | 6 Months | 1 Year | 3 Years |
|--------|----------|---------|----------|
| GitHub Stars | 5,000 | 15,000 | 50,000 |
| Monthly Active Users | 10,000 | 50,000 | 500,000 |
| Community Contributors | 50 | 200 | 1,000 |
| Plugin Ecosystem | 25 | 100 | 500 |
| Educational Adoptions | 100 | 1,000 | 10,000 |

### Impact Metrics

- Documentation update time reduction: 70%
- Open source project adoption: 1,000+ projects
- Community forum engagement: 80% response rate within 24 hours
- Tutorial completion rate: >90%

### Quality Metrics

- 95th percentile processing time: <100ms
- Zero critical security vulnerabilities
- <24 hour fix time for reported bugs
- 99% test coverage maintenance

### User Satisfaction

- Net Promoter Score (NPS): >70
- Documentation satisfaction: >4.8/5
- Community support rating: >4.5/5
- GitHub issue resolution time: <48 hours

## Community Strategy

### Launch Phases

#### Phase 1: Developer Preview (Months 1-3)
- Open source release on GitHub with comprehensive documentation
- Hacker News, Reddit r/programming, and Dev.to launches
- 100 beta community testers
- Core feature set complete with extensive examples

#### Phase 2: Community Building (Months 4-6)
- Package manager distribution (brew, apt, chocolatey)
- Documentation site with 200+ examples and tutorials
- VSCode extension launch
- First conference talks and community presentations

#### Phase 3: Ecosystem Growth (Months 7-12)
- Plugin marketplace launch
- Community governance model
- Mentorship program for new contributors
- Integration with popular open source projects

### Distribution Channels

1. **Open Source First**
   - GitHub (primary repository and releases)
   - Package managers (apt, brew, npm, cargo)
   - Docker Hub official images
   - Homebrew core formula

2. **Community Platforms**
   - Discord server for real-time support
   - GitHub Discussions for feature requests
   - YouTube channel with tutorials
   - Community blog on Dev.to

3. **Educational Outreach**
   - University computer science departments
   - Coding bootcamps and online courses
   - Open source conference sponsorships
   - Student hackathon presence

### Competitive Analysis

### Direct Competitors

#### MDX
- **Strengths**: React integration, large ecosystem
- **Weaknesses**: React-only, complex toolchain, requires build process
- **XMD Advantage**: Universal compatibility, no dependencies, works everywhere

#### Jekyll/Hugo
- **Strengths**: Mature, extensive themes
- **Weaknesses**: Build-time only, language-specific requirements
- **XMD Advantage**: Runtime execution, single binary, no setup

#### Jupyter Notebooks
- **Strengths**: Interactive, data science standard
- **Weaknesses**: Python-centric, not markdown-first, heavyweight
- **XMD Advantage**: Language agnostic, pure markdown, lightweight

### Positioning Matrix

```
         Dynamic ←────────────→ Static
Complex ┌──────────────────────────┐
   ↑    │ Jupyter       MDX        │
   │    │                          │
   │    │      XMD                 │
   │    │                          │
   ↓    │              Jekyll/Hugo │
Simple  └──────────────────────────┘
```

### Competitive Advantages

1. **Accessibility**
   - Completely free with no restrictions
   - Single binary with zero setup
   - Works with existing markdown workflows

2. **Community First**
   - Open source development model
   - Transparent roadmap and governance
   - Community-driven feature development

3. **Universal Compatibility**
   - Works with any markdown renderer
   - No vendor lock-in or proprietary formats
   - Integrates with all major platforms

## Risk Assessment & Mitigation

### Technical Risks

| Risk | Impact | Probability | Mitigation |
|------|--------|-------------|------------|
| Security vulnerability | High | Medium | Sandboxing, security audits, responsible disclosure |
| Performance regression | Medium | Medium | Comprehensive benchmarks, CI performance tests |
| Platform incompatibility | Low | Low | Multi-platform CI, community testing |

### Community Risks

| Risk | Impact | Probability | Mitigation |
|------|--------|-------------|------------|
| Low adoption | High | Medium | Strong developer outreach, excellent documentation |
| Contributor burnout | Medium | Medium | Governance model, recognition program |
| Feature creep | Medium | High | Clear roadmap, community voting on features |

### Sustainability Risks

| Risk | Impact | Probability | Mitigation |
|------|--------|-------------|------------|
| Maintainer sustainability | High | Medium | Multiple maintainers, sponsorship program |
| Community fragmentation | Medium | Low | Clear governance, inclusive decision making |
| Competition response | Low | High | Open source moat, community loyalty |

### Mitigation Strategies

1. **Security First**
   - Monthly security reviews by community experts
   - Automated vulnerability scanning in CI
   - Clear security reporting process
   - Security-focused documentation

2. **Community Sustainability**
   - Open governance model with elected maintainers
   - GitHub Sponsors and OpenCollective funding
   - Recognition program for contributors
   - Clear contributor onboarding process

3. **Technical Excellence**
   - Extensive test suite with >99% coverage
   - Performance benchmarks in CI
   - Multiple platform testing
   - Community code review process

## Conclusion

XMD represents a fundamental shift toward democratizing powerful documentation tools. By making advanced markdown processing completely free and accessible, we can empower developers, students, and organizations worldwide to create dynamic, self-updating documentation without barriers.

The focus on community, open source principles, and universal accessibility positions XMD to become the standard tool for programmable documentation. Success will be measured not in revenue, but in community growth, user empowerment, and the positive impact on documentation practices across the software industry.

### Next Steps

1. Finalize v1.0 feature set based on community feedback
2. Establish community governance structure
3. Launch contributor onboarding program
4. Create comprehensive tutorial series
5. Plan community launch events and presentations

---

*Document Version: 2.0 - Open Source Edition*  
*Last Updated: <!-- xmd:exec date '+%Y-%m-%d' -->*  
*Status: Community Review*