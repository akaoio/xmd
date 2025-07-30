# XMD Teamwork Platform

A real-time collaborative dashboard system built on XMD (eXtended MarkDown) that enables teams to share updates and track progress seamlessly.

## 🚀 Quick Start

```bash
# Start the platform
./teamwork.sh start

# Add yourself to a team
./teamwork.sh add developer

# Check status
./teamwork.sh status
```

## 📋 Features

- **Auto-Discovery**: Automatically detects and includes all team files
- **Real-Time Updates**: Changes to team files instantly reflect in dashboard
- **Zero Configuration**: Works out of the box with sensible defaults
- **Tech Debt Free**: Clean, maintainable code with no hardcoded values
- **Error Handling**: Robust error checking and user-friendly messages

## 🛠️ Commands

| Command | Description | Example |
|---------|-------------|---------|
| `start` | Start platform and watch mode | `./teamwork.sh start` |
| `stop` | Stop watch mode | `./teamwork.sh stop` |
| `restart` | Restart the platform | `./teamwork.sh restart` |
| `add <team>` | Add a new team | `./teamwork.sh add backend` |
| `list` | List all teams | `./teamwork.sh list` |
| `status` | Show system status | `./teamwork.sh status` |
| `update` | Manually update dashboard | `./teamwork.sh update` |

## 📁 Directory Structure

```
teamwork/
├── teamwork.sh          # Main control script
├── dashboard.md         # Generated dashboard (DO NOT EDIT)
├── dashboard_template.md # Auto-generated template
├── update/              # Team update files
│   ├── developer.md
│   ├── designer.md
│   └── ...
└── README.md           # This file
```

## ✏️ How to Use

### 1. Start the Platform
```bash
./teamwork.sh start
```
This will:
- Create necessary directories
- Generate dashboard template
- Start watch mode
- Show system status

### 2. Add/Edit Your Team Update
```bash
# Add a new team
./teamwork.sh add myteam

# Edit your update
nano update/myteam.md
```

### 3. View the Dashboard
The dashboard is automatically generated at `dashboard.md` and updates in real-time.

## 📝 Team File Format

Each team file should follow this format:

```markdown
### Team Name Update

**Role:** Your Role
**Name:** Your Name
**Status:** Current project status

#### Progress:
- Completed task 1
- Working on task 2

#### Next Steps:
- Plan for task 3
```

## 🔧 Technical Details

### How It Works
1. **Auto-Discovery**: Scans `update/` directory for team files
2. **Dynamic Template**: Generates dashboard template based on found teams
3. **XMD Processing**: Uses XMD to process imports and variables
4. **Watch Mode**: Monitors changes and regenerates dashboard

### Requirements
- XMD binary (xmd-release)
- Bash shell
- Basic Unix utilities (sed, awk, grep)

## 🐛 Troubleshooting

### Dashboard not updating?
```bash
# Check status
./teamwork.sh status

# Restart if needed
./teamwork.sh restart
```

### Watch mode issues?
```bash
# Stop any hanging processes
./teamwork.sh stop

# Start fresh
./teamwork.sh start
```

### Permission errors?
```bash
# Make script executable
chmod +x teamwork.sh
```

## 🚫 Known Limitations

Due to XMD bugs, the following features use workarounds:
- No dynamic loops (uses auto-generated imports)
- No array functions (counts teams during generation)
- No object properties (uses flat variables)

## 🤝 Contributing

To improve the platform:
1. Check current tech debt in TEAMWORK.md
2. Test your changes thoroughly
3. Update documentation if needed
4. Share with the team!

## 📊 Version History

- **v2.0** - Tech debt removal, auto-discovery, improved UX
- **v1.0** - Initial version with hardcoded teams

---
*Built with ❤️ by the XMD Team*