# XMD Team Chat System - Enhanced

Real-time text-based team coordination tool with @mention system for the XMD development team.

## Features

- 🚀 **Real-time messaging** - Instant team communication
- 🎯 **@Mention system** - Target messages to specific team members
- 👥 **Role detection** - Automatically detects team member roles
- 🎨 **Color-coded messages** - Different colors for different roles
- ⭐ **Message highlighting** - Messages targeted to you are highlighted
- 📁 **Persistent storage** - Messages saved with timestamps
- 🔄 **Auto-sync** - View latest messages when called without parameters
- 📊 **Team status** - Shows current status of all team members
- 🏗️ **Build integration** - Displays current build status

## Usage

### From root directory:
```bash
# Sync and view all messages
./chat.sh

# Send message to everyone (default)
./chat.sh "Your message here"

# Send targeted messages with @mentions
./chat.sh "@all Hello everyone!"
./chat.sh "@leader Status update needed"
./chat.sh "@developer Need code review"
./chat.sh "@systems Build system question"

# Show team status
./chat.sh status

# Show help
./chat.sh help

# Clear chat history
./chat.sh clear

# Show only messages for me
./chat.sh mine
```

### From chat/ directory:
```bash
# Same commands work here
./chat.sh "Message from chat directory"
```

## Message Format

Messages are stored as individual files with enhanced format:
```
[YYYY-MM-DD HH:MM:SS] FROM → TO: Message content
```

### @Mention Targets
- `@all` - Message visible to everyone (default)
- `@systems` - Message targeted to Systems Engineer
- `@leader` - Message targeted to Genesis Leader
- `@developer` - Message targeted to Developer

## File Structure

```
chat/
├── README.md                    # This documentation
├── chat.sh                     # Lightweight chat tool
└── msg_YYYYMMDD_HHMMSS_Role.txt # Individual message files
```

## Role Colors

- 🔧 **Systems Engineer** - Blue text
- 👑 **Genesis Leader** - Green text  
- 💻 **Developer** - Yellow text

## Integration

The chat system integrates with the teamwork coordination system:
- Reads status from `teamwork/*.md` files
- Detects user roles automatically
- Shows build progress when available

## Examples

```bash
# Send status update to everyone
./chat.sh "@all AST parser implementation completed - 100% success!"

# Direct message to leader
./chat.sh "@leader Ready for code review and next phase planning"

# Ask developer for help
./chat.sh "@developer Need assistance with memory allocation in parser module"

# Report to systems engineer
./chat.sh "@systems Build pipeline showing warnings in security module"

# Check what everyone is working on
./chat.sh status

# View recent team discussions
./chat.sh

# See only messages directed to me
./chat.sh mine
```

### Message Examples in Chat:
```
[2025-08-02 04:08:58] Systems → 👑 LEADER: Build system is 100% operational, all modules restored. Ready for your next directives on project roadmap!

[2025-08-02 04:09:05] Systems → 💻 DEVELOPER: All 100% real implementations complete. No stubs or TODOs remain. Ready to collaborate on new features!

[2025-08-02 04:08:52] Systems → 👥 ALL: Enhanced chat system deployed! Now supports @mentions for targeted messaging.
```

This tool enables seamless coordination for the XMD development team's real-time collaboration needs.