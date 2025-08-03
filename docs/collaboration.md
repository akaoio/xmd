# Team Collaboration Guide

XMD enables seamless team collaboration through real-time dashboard updates. This guide shows you how to set up and use XMD for team coordination.

## Quick Setup

### 1. Project Setup
```bash
# In your project root
git submodule add https://github.com/akaoio/xmd.git tools/xmd
cd tools/xmd && ./build.sh && cd ../..

# Create collaboration workspace
mkdir teamwork && cd teamwork
mkdir update
```

### 2. Dashboard Template
Create `dashboard.md`:

```markdown
# Team Dashboard
**Last Updated:** <!-- xmd exec date '+%Y-%m-%d %H:%M:%S' -->

## Team Members

<!-- xmd import update/backend.md -->
---
<!-- xmd import update/frontend.md -->
---
<!-- xmd import update/tester.md -->
---
<!-- xmd import update/coordinator.md -->

## Quick Stats
<!-- xmd exec ls update/*.md | wc -l | tr -d ' ' --> active members
```

### 3. Start Live Dashboard
```bash
# Auto-update dashboard when any team file changes
../tools/xmd/xmd watch dashboard.md live_dashboard.md

# Dashboard updates automatically when anyone edits their file!
```

## Team Member Templates

### Backend Developer Template
`update/backend.md`:
```markdown
### Backend Developer Update

**Role:** Backend Developer  
**Name:** John Doe / Agent-Backend  
**Status:** 🔄 API Development in Progress

#### Current Tasks:
- ✅ Database schema design completed
- 🔄 REST API endpoints implementation
- ⏳ Authentication middleware pending

#### Today's Progress:
- Implemented user registration endpoint
- Fixed database connection pooling issue
- Added input validation for all POST requests

#### Next Steps:
- Complete authentication system
- Add rate limiting
- Write API tests

#### Blockers:
None currently

#### Code Files Changed:
- `src/api/users.js` - New user endpoints
- `config/database.js` - Connection pool fix
```

### Frontend Developer Template  
`update/frontend.md`:
```markdown
### Frontend Developer Update

**Role:** Frontend Developer  
**Name:** Jane Smith / Agent-Frontend  
**Status:** 🎨 UI Components Development

#### Current Tasks:
- ✅ Login/Register forms completed
- 🔄 Dashboard layout in progress
- ⏳ API integration pending

#### Today's Progress:
- Implemented responsive login form
- Added form validation with error messages
- Set up routing for main app sections

#### Next Steps:
- Connect forms to backend API
- Build user dashboard
- Add loading states

#### Blockers:
Waiting for backend API endpoints

#### Code Files Changed:
- `src/components/Auth/` - Login/register forms
- `src/styles/forms.css` - Form styling
```

### QA Tester Template
`update/tester.md`:
```markdown
### QA Tester Update

**Role:** Quality Assurance Tester  
**Name:** Mike Johnson / Agent-QA  
**Status:** 🧪 Testing Backend APIs

#### Current Tasks:
- ✅ Manual testing of user registration
- 🔄 API endpoint validation in progress
- ⏳ Frontend testing pending

#### Today's Progress:
- Found 3 bugs in user registration flow
- Verified database constraints working correctly
- Created test data sets for edge cases

#### Bugs Found:
1. **Registration Bug**: Email validation allows invalid formats
2. **API Bug**: 500 error when password is empty
3. **UI Bug**: Success message not showing after registration

#### Next Steps:
- Test password reset functionality
- Validate error handling
- Cross-browser testing

#### Test Cases Completed: 15/23
```

### Project Coordinator Template
`update/coordinator.md`:
```markdown
### Project Coordinator Update

**Role:** Project Coordinator  
**Name:** Sarah Wilson / Agent-Coordinator  
**Status:** 📊 Sprint Planning & Team Coordination

#### Current Sprint: Sprint 3 - Authentication System
**Duration:** Feb 1-14, 2025  
**Progress:** 60% Complete

#### Team Status Overview:
- **Backend**: API development 80% done
- **Frontend**: Forms completed, integration 40% done  
- **QA**: Found 3 critical bugs, testing ongoing

#### Today's Coordination:
- Facilitated backend-frontend API integration discussion
- Prioritized bug fixes found by QA team
- Updated project timeline based on current progress

#### Blockers Resolved:
- Backend API documentation shared with frontend
- Test environment setup completed

#### Next Sprint Goals:
- Complete authentication system
- Begin dashboard functionality
- Implement user profile management

#### Meeting Schedule:
- Daily standup: 9:00 AM
- Sprint review: Feb 14, 3:00 PM
```

## Agent Integration Prompts

### For AI Agents Joining Team

**Copy this prompt for AI agents:**
```
You are joining an XMD-powered collaborative team workspace.

SETUP:
- Your workspace file: `/teamwork/update/<your-role>.md`
- Dashboard updates automatically when you save your file
- Use the role template from docs/collaboration.md

WORKFLOW:
1. Edit ONLY your assigned role file
2. Update your progress regularly (at least daily)
3. Use the template format consistently
4. Never edit dashboard.md directly (auto-generated)

ROLE FILE TEMPLATE:
```markdown
### <Your Role> Update

**Role:** <Your Specialization>
**Name:** <Agent Name/ID>
**Status:** <Current Task with emoji>

#### Current Tasks:
- ✅ Completed task
- 🔄 In progress task  
- ⏳ Pending task

#### Today's Progress:
- Specific accomplishments today

#### Next Steps:
- Planned tasks for tomorrow

#### Blockers:
- Issues preventing progress

#### Files Changed:
- List of modified files
```

COLLABORATION RULES:
- Communicate through your status file
- Check dashboard regularly for team updates
- Mark blockers clearly so others can help
- Use consistent emoji status indicators

The dashboard at `/teamwork/live_dashboard.md` shows everyone's updates in real-time!
```

### For Project Owners

**Setup instructions for project owners:**
```
INTEGRATING XMD TEAM COLLABORATION:

1. Add XMD to your project:
   git submodule add https://github.com/akaoio/xmd.git tools/xmd
   cd tools/xmd && ./build.sh

2. Create team workspace:
   mkdir teamwork && cd teamwork
   mkdir update

3. Copy dashboard template from docs/collaboration.md to dashboard.md

4. Start live dashboard:
   ../tools/xmd/xmd watch dashboard.md live_dashboard.md &

5. Share role templates with your team/agents

6. Each team member creates update/<role>.md using templates

BENEFITS:
✅ Real-time team visibility
✅ No merge conflicts (individual files)
✅ Automatic dashboard updates
✅ Works with AI agents and humans
✅ Markdown-based (version controllable)
```

## Advanced Features

### Custom Role Templates
Create your own role templates by copying and modifying the examples above.

### Multi-Project Dashboards
```markdown
# Multi-Project Dashboard
<!-- xmd import project1/teamwork/dashboard.md -->
---
<!-- xmd import project2/teamwork/dashboard.md -->
```

### Team Metrics
```markdown
## Team Metrics
**Total Members:** <!-- xmd exec ls update/*.md | wc -l -->
**Files Changed Today:** <!-- xmd exec find . -name "*.md" -newer .yesterday -type f | wc -l -->
**Active Projects:** <!-- xmd exec grep -l "🔄" update/*.md | wc -l -->
```

### Integration with Git
```bash
# Add pre-commit hook to update timestamp
echo '#!/bin/bash\ndate "+%Y-%m-%d %H:%M:%S" > .last_update' > .git/hooks/pre-commit
chmod +x .git/hooks/pre-commit
```

## Troubleshooting

**Dashboard not updating?**
- Check that watch process is running: `ps aux | grep xmd`
- Restart watch: `pkill xmd && ../tools/xmd/xmd watch dashboard.md live_dashboard.md &`

**Import not working?**
- Use single quotes or no quotes: `<!-- xmd import 'file.md' -->`
- Avoid double quotes: `<!-- xmd import "file.md" -->` ❌

**Multiple agents causing conflicts?**
- Each agent should only edit their own update/<role>.md file
- Never edit dashboard.md or live_dashboard.md directly

## Best Practices

1. **Update frequently** - Keep your status current
2. **Be specific** - Detail what you accomplished
3. **Mark blockers clearly** - Help teammates understand dependencies  
4. **Use consistent formatting** - Follow the templates
5. **Include file references** - List what you changed
6. **Use emoji indicators** - Visual status at a glance

---

*For more examples and advanced usage, see the [examples](examples/) directory.*