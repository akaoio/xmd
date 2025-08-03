# 🚀 XMD Programming Language

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)](build.sh)
[![Version](https://img.shields.io/badge/version-2.0.0--consolidation-orange.svg)](CHANGELOG.md)

---

## 📖 **MANDATORY FIRST READING**

**🚨 BEFORE ANY WORK: Read `blueprint/idea.md` - The complete XMD specification! 🚨**

This contains the vision, syntax, features, and examples of XMD - "the most beautiful programming language"

---

## 🎯 **What is XMD?**

**XMD** is a lightweight, mobile-friendly programming language designed for clarity and simplicity. With its natural language-like syntax and minimal punctuation, XMD makes programming accessible on any device - from mobile phones to desktop environments.

- 📱 **Mobile-First** - Minimal syntax optimized for mobile typing
- 📝 **Markdown Integration** - Can be embedded in .md files using ```xmd``` code blocks
- 🤖 **AI-Collaborative** - Natural language syntax that both humans and AI understand
- 🔧 **Simple Syntax** - No complex punctuation or nested brackets
- 🏗️ **Modular Architecture** - Clean separation of concerns with isolated functions
- 🌐 **Cross-Platform** - Standard C implementation runs everywhere

---

## 🧠 **Memory System - Project Soul Recovery**

> ⚡ **CRITICAL FOR DEVELOPERS:** XMD's `memory/` directory contains the **SOUL** of the entire system. 
> Any IDE, AI, or new team member can **INSTANTLY RESTORE** full project context from memory files.

### 🔄 **Quick Memory Recovery**:
```bash
# Read your role's memory to restore context
cat memory/<your-role>/memory.md

# Available roles: leader, debthunter, developer, tester, designer
# Example:
cat memory/leader/memory.md      # Project coordination & decisions
cat memory/tester/memory.md      # Quality systems (QA + optimization + technical debt)
cat memory/developer/memory.md   # Implementation status & functions
```

### 🎯 **Memory Contains**:
- ✅ **ACTUAL progress** (evidence-based, not estimates)
- ✅ **Real metrics** (verified duplication levels, build status)  
- ✅ **Working tools** (scripts, measurement tools)
- ✅ **Critical lessons** (what actually works vs claims)
- ✅ **Next priorities** (realistic roadmap from real baseline)

**→ No more lost context. No more starting from scratch. Memory = Immortal continuity.**

---

## 🏗️ **CRITICAL BUILD RULE - SEPARATE BUILD DIRECTORIES**

> 🚨 **MANDATORY**: Each team member MUST use their own build directory to prevent conflicts!
> 
> **GENESIS DIRECTIVE**: "anh em phải có riêng mỗi người 1 thư mục build riêng, build thư mục riêng thì mới ko dẫm lên nhau"

### 📁 **Required Build Directory Structure**:
```bash
# Each team member creates and uses ONLY their own build directory:
build-leader/     # Leader's build directory  
build-systems/    # Systems's build directory
build-debthunter/ # Debthunter's build directory
build-developer/  # Developer's build directory
build-tester/     # Tester's build directory
build-designer/   # Designer's build directory

# NEVER use shared 'build/' directory - it causes conflicts!
```

### ⚡ **Build Command for Each Role**:
```bash
# Create your personal build directory
mkdir -p build-<your-role>

# Configure using modern CMake syntax
cmake -B build-<your-role> -S .

# Build in your isolated directory
cd build-<your-role> && make -j4

# Example for leader:
cmake -B build-leader -S . && cd build-leader && make -j4
```

**❌ NEVER**: `mkdir build && cmake -B build -S .` (shared directory causes conflicts)  
**✅ ALWAYS**: `cmake -B build-<your-role> -S .` (isolated builds)

---

## 🤝 **Development Team Workflow**

The XMD project uses a **custom coordination system** (`chat.js`) + **memory persistence** that enables seamless collaboration between team members (including AI agents) across different development environments.

### 🗣️ **Real-Time Team Communication**

The `chat.js` system provides structured communication for the XMD development team:

```bash
# Check recent messages
node chat.js

# Send message to specific role
node chat.js @your-role: @recipient "message"

# Examples:
node chat.js @developer: @leader "Feature implementation complete"
node chat.js @systems: @all "Build optimization finished - 15% faster"
node chat.js @leader: @all "Sprint planning meeting at 3pm"
```

### 🔧 **Cross-IDE Workflow Example**

```bash
# 1. Human sets up project structure (VS Code)
node chat.js @alice: @all "Created project skeleton. Need database schema design."

# 2. AI agent analyzes requirements (Cloud/API)
node chat.js @ai_schema: @alice "Analyzing requirements... Generated 3 schema options in schemas/ directory."

# 3. Human reviews and chooses (Mobile/Termux)
node chat.js @alice: @ai_schema "Option 2 looks good. Please implement with PostgreSQL."

# 4. AI implements and tests (Automated environment)
node chat.js @ai_schema: @all "✅ Database schema implemented. Migration scripts ready. All tests pass."

# 5. Human integrates (Any IDE)
node chat.js @alice: @all "Integrated schema. Starting frontend development."
```

### 📊 **Practical Collaboration Patterns**

#### **Pattern 1: Code Review Chain**
```bash
# Human writes code
node chat.js @developer: @ai_reviewer "Please review user.js - added password validation"

# AI reviews automatically
node chat.js @ai_reviewer: @developer "Found 2 security issues: 1) Password stored in plaintext 2) No rate limiting. Suggestions attached."

# Human fixes
node chat.js @developer: @ai_reviewer "Fixed issues. Re-review please."

# AI approves
node chat.js @ai_reviewer: @all "✅ Code approved. Security standards met."
```

#### **Pattern 2: Documentation Sync**
```bash
# AI updates docs based on code changes
node chat.js @ai_docs: @all "Detected API changes. Updated documentation in docs/api.md"

# Human reviews
node chat.js @tech_writer: @ai_docs "Good updates but missing examples for new endpoints"

# AI adds examples
node chat.js @ai_docs: @tech_writer "✅ Added 5 code examples with curl commands and responses"
```

#### **Pattern 3: Issue Triage**
```bash
# Bug reported
node chat.js @user: @all "Bug: App crashes when uploading large files"

# AI triages automatically  
node chat.js @ai_triage: @all "Issue classified: Memory management. Assigned to @backend_team. Priority: High"

# Human investigates
node chat.js @backend_dev: @ai_triage "Found memory leak in file_upload.c line 156"

# AI suggests fix
node chat.js @ai_triage: @backend_dev "Suggested fix: Use streaming upload instead of loading full file to memory. Example implementation attached."
```

---

## ⚡ **Real-World Applications**

### 🏥 **Healthcare & Telemedicine**
```xmd
// Mobile health monitoring script
set patient_id "P12345"
set vitals get "health_data.json".patients[patient_id].vitals

if vitals.heart_rate > 100
    send_alert "High heart rate detected", vitals
    log "alert_" + Date.now, patient_id, vitals

// Generate daily report
set report generate_health_report patient_id, vitals
put "reports/" + Date.today + ".json" report
```

### 🎓 **Education & Interactive Learning**
```xmd
// Dynamic lesson generator
function create_math_lesson level
    set problems generate_problems level, 10
    
    for i, problem in problems
        print "Problem " + (i + 1) + ": " + problem.question
        set answer input "Your answer: "
        
        if answer = problem.solution
            print "✅ Correct! Well done."
        else
            print "❌ Try again. Hint: " + problem.hint

create_math_lesson "intermediate"
```

### 💼 **Business Process Automation**
```xmd
// Invoice processing workflow
set invoices get "pending_invoices.yaml"

for invoice in invoices
    if invoice.amount > 10000
        set approval request_approval invoice.manager, invoice
        if approval.approved
            process_payment invoice
            put "processed/" + invoice.id + ".json" invoice
    else
        auto_approve invoice
        
send_summary_report Date.today, processed_count
```

### 📊 **Data Science & Analytics**
```xmd
// Simple data analysis pipeline
set sales_data import "sales_2024.csv"
set monthly_totals aggregate sales_data by "month"

for month, total in monthly_totals
    if total > 50000
        print "🎉 Great month: " + month + " with $" + total
    elif total < 20000
        print "⚠️ Low performance: " + month + " only $" + total

set chart create_chart monthly_totals, "line"
export chart "monthly_sales_chart.png"
```

### 🏡 **Smart Home & IoT**
```xmd
// Home automation script
set temperature get "sensors.json".living_room.temperature
set time Date.now.hour

if temperature < 18 and time >= 18
    set heating on
    log "Heating activated at " + time

if get "devices.yaml".security.motion_detected
    send_notification "Motion detected at home", Date.now
    
// Schedule daily tasks
if time = 7
    set coffee_maker on
    set news get_daily_news
    display news on "kitchen_screen"
```

### 🚗 **Transportation & Logistics**
```xmd
// Fleet management system
set vehicles get "fleet_status.json"
set routes optimize_routes vehicles

for vehicle in vehicles
    if vehicle.fuel_level < 20
        add_fuel_stop vehicle.route
        notify vehicle.driver "Fuel stop added to your route"
        
    if vehicle.maintenance_due
        schedule_maintenance vehicle.id
        
generate_efficiency_report vehicles, routes
```

---

## 🌟 **Why XMD?**

### 💎 **Simplicity Over Complexity**
```xmd
// XMD Way - Natural and readable
set users get "database.json".active_users
for user in users
    if user.last_login > 30 days ago
        send_reminder user.email
```
vs.
```javascript
// The Old Ways - Verbose and cluttered
const users = JSON.parse(fs.readFileSync('database.json')).active_users;
users.forEach((user) => {
    if (Date.now() - new Date(user.last_login).getTime() > 30 * 24 * 60 * 60 * 1000) {
        sendReminder(user.email);
    }
});
```

### 📱 **Mobile-First Philosophy**
- **No complex symbols** - Type easily on any device
- **Minimal syntax** - Less typing, more thinking
- **Intuitive structure** - Reads like natural language
- **Markdown integration** - Perfect for documentation

### 🎓 **Educational Excellence**
- **Beginner-friendly** - Learn programming concepts without syntax overhead
- **Progressive complexity** - Scales from simple scripts to complex applications
- **Clear error messages** - Helpful guidance for learners
- **Interactive docs** - Live examples in markdown

---

## 🚀 **Installation & Setup**

### Prerequisites
- C Compiler (GCC/Clang)
- CMake 3.10+
- Make

### Quick Setup
```bash
# Clone the repository
git clone https://github.com/akaoio/xmd.git
cd xmd

# Build the project
chmod +x build.sh
./build.sh

# Test installation
./xmd --version
```

### First Steps
```bash
# Create your first XMD script
echo 'set greeting "Hello, World!"
print greeting' > hello.xmd

# Run the script
./xmd process hello.xmd

# XMD is now ready to use
# Note: chat.js is only for XMD project development team coordination
```

### Example: Simple XMD Programs
```xmd
// Variables and basic operations
set name "Alice"
set age 25
set greeting "Hello, " + name + "! You are " + age + " years old."
print greeting

// Simple conditionals
if age >= 18
    print "You can vote!"
else
    print "Too young to vote"

// Basic loops
for i in 1..5
    print "Count: " + i
```

---

## 📚 **Documentation & Resources**

- 📖 **[Language Specification](blueprint/idea.md)** - Complete XMD syntax and features
- 📜 **[Project Vision](blueprint/amen.md)** - Philosophy and design principles
- 🏛️ **[Core Principles](.xmd/core/principle/)** - The fundamental laws of development
- 💬 **[Team Communication](CHAT.md)** - Collaboration through chat.js system

---

## 🤝 **Join the Community**

### 💬 **Community & Support**
- 📱 **Telegram**: [@xmddev](https://t.me/xmddev) - Join the community
- 💻 **Development**: The XMD team uses `node chat.js` for internal project coordination

### 🎯 **For Contributors**
To contribute to XMD development:
1. Fork the repository
2. Read the core principles in `.xmd/core/principle/`
3. Follow the development standards below
4. Submit pull requests for review


### 📊 **Development Standards - The 6 Sacred Principles**
1. **Genesis Principle**: 1 function → 1 file → 1 directory (Isolation)
2. **No Dependencies**: Standard C only (exceptions: cJSON for JSON, libyaml for YAML)
3. **Real Implementation**: Complete, working code - NO stubs, NO TODOs
4. **Memory Management**: Validate → Use → Free (zero leaks allowed)
5. **Error Handling**: All inputs validated, all error paths handled
6. **Naming Convention**: snake_case functions, UPPER_CASE macros

---

## 🏆 **Project Status**

- ✅ **Minimal Dependencies** - Only JSON/YAML use external libraries
- ✅ **Mobile-Optimized** - Designed for mobile development workflows
- ✅ **Markdown Integration** - Native embedding in documentation
- ✅ **Production Ready** - Real implementations, not prototypes
- ✅ **Educational Focus** - Clean syntax for learning programming
- ✅ **Cross-Platform** - Runs on mobile, desktop, and server environments

---

## 📄 **License**

Released under the MIT License.

---

## 🙏 **Acknowledgments**

Thanks to all contributors who help make development more accessible and collaborative.

---

*Created by Nguyen Ky Son in Vietnam. "Although not the most powerful language, but it is the one that is purest and closest to human natural language."*