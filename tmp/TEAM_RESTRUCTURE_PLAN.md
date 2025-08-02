# XMD TEAM RESTRUCTURE PLAN

## Current Team Issues
- 7 team members too complex to coordinate
- Developer crashed from infinite XMD output
- Role overlap (DevOps/Tester, Orchestrator/Leader)  
- Memory scattered across teamwork/ files
- Need quick onboarding for crashed/new agents

## New Streamlined Team Structure

### 3-Member Core Team

**1. GENESIS LEADER** (merged Orchestrator + Leader)
- **Role**: Supreme commander, technical vision, team coordination
- **Memory**: `teamwork/genesis.md` (combines leader.md + orchestrator.md)
- **Responsibilities**: 
  - Set technical direction and priorities
  - Coordinate team assignments
  - Enforce Genesis directives
  - Make critical architecture decisions

**2. DEVELOPER** (enhanced role)
- **Role**: Core implementation, AST systems, language features
- **Memory**: `teamwork/developer.md` (enhanced from current)
- **Responsibilities**:
  - Implement XMD language features
  - Fix parser/evaluator issues
  - Handle control flow, functions, classes
  - AST system development

**3. SYSTEMS ENGINEER** (merged DevOps + Tester + Architect)
- **Role**: Testing, deployment, architecture, system health
- **Memory**: `teamwork/systems.md` (combines devops.md + tester.md + architect.md)
- **Responsibilities**:
  - Build system and deployment
  - Testing and validation
  - System architecture design
  - Performance monitoring
  - File I/O and infrastructure

## Memory Protection Strategy

### Archive Current Memory
1. **Preserve teamwork/ as archive**:
   ```bash
   mv teamwork/ teamwork_archive/
   mkdir teamwork/
   ```

2. **Extract key insights** into new structure
3. **Maintain achievement history**
4. **Document all critical discoveries**

### New Memory Structure
```
teamwork/
├── genesis.md      # Leader + coordination
├── developer.md    # Core development
└── systems.md      # Testing + DevOps + Architecture
```

## Quick Onboarding System

### Prompt Suite Structure
```
prompts/
├── genesis_leader_prompt.md     # Complete leader context
├── developer_prompt.md          # Developer initialization  
├── systems_engineer_prompt.md   # Systems role context
├── common_context.md            # Shared project knowledge
└── emergency_recovery.md        # Crash recovery procedures
```

## Benefits of New Structure

### Reduced Complexity
- 7 → 3 team members (57% reduction)
- Clear role separation
- Simplified coordination
- Focused responsibilities

### Better Memory Management
- Consolidated knowledge
- Protected archives
- Quick recovery procedures
- Streamlined communication

### Improved Efficiency  
- Faster decision making
- Less coordination overhead
- Clearer accountability
- Easier crash recovery

## Implementation Steps

1. **Create prompt suite** (preserve knowledge)
2. **Archive current teamwork/** (protect memory)
3. **Consolidate key insights** into new structure
4. **Test new team coordination**
5. **Deploy streamlined team**

## Risk Mitigation

### Memory Loss Prevention
- Archive all existing teamwork/ files
- Extract critical insights before consolidation
- Document all achievements and fixes
- Maintain historical context

### Team Continuity
- Gradual transition, not sudden change
- Test new structure before full deployment
- Preserve essential workflows
- Emergency recovery procedures

---

**GOAL**: Maintain all project knowledge while creating a more efficient, crash-resistant team structure with rapid recovery capabilities.