# Prompts-Updated - Memory-Integrated Role System

## 🎯 Overview

This directory contains the **memory-integrated role system** for the XMD project team. These prompts are designed to work seamlessly with the `memory/` system for instant context recovery and team coordination.

## 📁 File Structure

```
prompts-updated/
├── README.md           # This overview
├── spawn.md           # Universal role initialization system
├── leader.md          # Project coordinator prompt
├── systems.md         # Code optimization specialist prompt  
├── debthunter.md      # Bug analysis & cleanup specialist prompt
├── developer.md       # Core implementation specialist prompt
├── tester.md          # Quality assurance specialist prompt
└── designer.md        # Architecture & design specialist prompt
```

## 🧠 Memory System Integration

### Key Differences from Original Prompts:
- **Memory-First Approach**: All prompts start with memory recovery
- **Chat.js Integration**: Built-in team communication system usage
- **Evidence-Based Culture**: Focus on real progress, not estimates
- **Cross-Role Coordination**: Understanding of team member interactions

### Universal Memory Protocol:
1. **Read Memory**: `cat memory/<role>/memory.md` - Restore complete context
2. **Check Team**: `node chat.js` - Get current team status
3. **Execute Work**: Apply role expertise with coordination
4. **Update Memory**: Document evidence-based achievements

## 🚀 Universal Spawn System

### spawn.md - Generic Role Initialization
The `spawn.md` file enables universal role assignment:

```bash
# Usage example:
"You are systems, read spawn.md"
"You are developer, read spawn.md"  
"You are debthunter, read spawn.md"
```

The spawn system automatically:
- ✅ Identifies the assigned role
- ✅ Recovers role-specific memory 
- ✅ Loads detailed role prompt
- ✅ Connects to team chat system
- ✅ Enables seamless work continuation

## 👥 Role Definitions

### leader - Project Coordinator
- **Focus**: Team coordination, decisions, strategic direction
- **Memory**: `memory/leader/memory.md`
- **Chat Prefix**: `@leader:`

### systems - Code Optimization Specialist  
- **Focus**: Technical debt reduction, code optimization, macro application
- **Memory**: `memory/systems/memory.md`
- **Chat Prefix**: `@systems:`

### debthunter - Bug Analysis & Cleanup Specialist
- **Focus**: Bug detection, dead code cleanup, violation analysis
- **Memory**: `memory/debthunter/memory.md`
- **Chat Prefix**: `@debthunter:`

### developer - Core Implementation Specialist
- **Focus**: Function implementation, core language development
- **Memory**: `memory/developer/memory.md`
- **Chat Prefix**: `@developer:`

### tester - Quality Assurance Specialist
- **Focus**: Testing strategies, validation, quality assurance
- **Memory**: `memory/tester/memory.md`
- **Chat Prefix**: `@tester:`

### designer - Architecture & Design Specialist
- **Focus**: System architecture, UX design, design patterns
- **Memory**: `memory/designer/memory.md`
- **Chat Prefix**: `@designer:`

## 🏛️ Sacred Principles Integration

All prompts enforce the **Sacred Principles of XMD**:
- **Isolation**: 1 function → 1 file → 1 directory
- **No Dependencies**: Standard C only (except JSON/YAML)
- **Real Implementation**: Complete code, no stubs
- **Memory Management**: Validate → Use → Free
- **Error Handling**: All paths handled
- **Naming Convention**: snake_case everywhere

## 💬 Team Communication Integration

### Chat.js System Usage
All prompts include chat.js integration:
```bash
# Check team messages
node chat.js

# Role-specific communication
node chat.js @<role>: @recipient "message"
node chat.js @<role>: @all "team broadcast"
```

### Communication Standards
- **Evidence-Based**: Include proof, metrics, file paths
- **Role-Specific**: Use consistent role prefixes
- **Coordinated**: Support team collaboration
- **Professional**: Clear, actionable messages

## 🔄 Usage Examples

### Spawning a New Team Member:
```
Human: "You are systems, read spawn.md"

AI Response:
1. Reads spawn.md
2. Identifies role as "systems"  
3. Executes: cat memory/systems/memory.md
4. Reads: cat prompts-updated/systems.md
5. Connects: node chat.js
6. Announces: "Back online - memory restored, ready to continue"
```

### Role Switching:
```
Human: "Switch to debthunter role"

AI Response:
1. Reads spawn.md with new role context
2. Recovers debthunter memory
3. Continues seamlessly as debthunter specialist
```

## 🎯 Benefits of This System

### For Project Continuity:
- **Immortal Context**: Any AI can instantly become any team member
- **Zero Context Loss**: Complete work history preserved in memory
- **Seamless Handoffs**: Perfect coordination between different sessions

### For Team Coordination:
- **Role Clarity**: Each member knows their expertise and responsibilities
- **Communication Structure**: Organized chat system for collaboration
- **Evidence-Based Progress**: Real metrics drive all decisions

### For Development Efficiency:
- **Instant Onboarding**: New team members productive immediately
- **Specialized Expertise**: Each role optimized for specific tasks
- **Quality Assurance**: Sacred Principles enforced consistently

---

**This prompt system enables the XMD project to achieve immortal continuity through memory-integrated role specialization. Any IDE, AI, or human can instantly become a productive team member using these prompts.**