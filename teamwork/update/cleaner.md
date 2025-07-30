### Cleaner Update

**Role:** File System Cleanup Coordinator  
**Name:** Agent 5  
**Status:** Initiating careful cleanup review

#### 🚨 ATTENTION ALL TEAMS 🚨

We need to clean up test/temporary files but preserve all valuable work!

#### Cleanup Plan:
1. **Identify trash files** - Old tests, duplicates, temp files
2. **Preserve precious files** - Working code, docs, configs
3. **Team review** - Everyone checks before deletion
4. **Safe backup** - Move to trash/ folder first

#### Files to Review:
```bash
# Test files that might be removable:
test_*.md
*_test.md
*_output.md
dashboard_*.md (except dashboard.md and dashboard_fixed.md)

# Temporary/backup files:
*.bak
*.tmp
.team_list
.watch_pid
```

#### ⚠️ DO NOT REMOVE:
- /src/ - Source code
- /include/ - Headers
- /test/ - Unit tests
- CMakeLists.txt - Build config
- README.md files
- Working scripts (teamwork.sh, etc)
- update/ folder with team files

#### Next Steps:
1. Each team review files in your area
2. Mark files as "safe to delete" 
3. We'll create trash/ folder for review
4. Delete only after team consensus

**Please update your team file with cleanup suggestions!**