#!/bin/bash

# tmux.sh - Create or attach to a tmux session with 4 claude instances
# Usage: ./tmux.sh [help]

SESSION_NAME="xmd-swarm"

# Show help if requested
if [ "$1" = "help" ] || [ "$1" = "--help" ] || [ "$1" = "-h" ]; then
    cat << 'EOF'
╔══════════════════════════════════════════════════════════════════════╗
║                        TMUX SWARM LAUNCHER                          ║
╚══════════════════════════════════════════════════════════════════════╝

Usage: ./tmux.sh [help]

This script creates or attaches to a tmux session with 4 Claude instances
running in horizontal panes for XMD swarm development.

ESSENTIAL TMUX SHORTCUTS:
══════════════════════════
Navigation:
  Ctrl+b → ←     Move between panes left/right
  Ctrl+b ↑ ↓     Move between panes up/down  
  Ctrl+b o       Cycle through panes
  Ctrl+b q       Show pane numbers (press number to jump)
  
Pane Management:
  Ctrl+b z       Zoom/unzoom current pane (fullscreen toggle)
  Ctrl+b x       Kill current pane (with confirmation)
  Ctrl+b !       Break pane into new window
  Ctrl+b space   Cycle through layouts
  
Session Control:
  Ctrl+b d       Detach from session (keeps running in background)
  Ctrl+b s       List/switch sessions
  Ctrl+b $       Rename current session
  
Scrolling/Copy Mode:
  Ctrl+b [       Enter scroll/copy mode (vim keys to navigate)
    ↑/↓ or j/k   Scroll up/down
    PgUp/PgDn    Page up/down
    g/G          Go to top/bottom
    /            Search forward
    ?            Search backward
    q            Exit scroll mode
    
Pane Resizing:
  Ctrl+b Alt+←   Resize pane left
  Ctrl+b Alt+→   Resize pane right
  Ctrl+b Ctrl+←  Resize pane left (fine)
  Ctrl+b Ctrl+→  Resize pane right (fine)

Window Management:
  Ctrl+b c       Create new window
  Ctrl+b n       Next window
  Ctrl+b p       Previous window
  Ctrl+b 0-9     Switch to window number
  Ctrl+b w       List windows

SWARM AGENT TIPS:
═════════════════
• Each pane runs an independent Claude instance
• Use @agent-swarm-agent in each pane to activate swarm mode
• Agents coordinate through @swarm/*.yaml log files
• Check memory/ folders for agent-specific context

To kill entire session: tmux kill-session -t xmd-swarm
To list sessions: tmux ls
To reattach later: ./tmux.sh or tmux attach -t xmd-swarm

EOF
    exit 0
fi

# Check if tmux session already exists
tmux has-session -t "$SESSION_NAME" 2>/dev/null

if [ $? != 0 ]; then
    echo "Creating new tmux session: $SESSION_NAME"
    
    # Create new session with first pane
    tmux new-session -d -s "$SESSION_NAME" -n "claude-swarm"
    
    # Split horizontally to create second pane
    tmux split-window -h -t "$SESSION_NAME:0"
    
    # Split the first pane horizontally to create third pane (top-left becomes two)
    tmux split-window -h -t "$SESSION_NAME:0.0"
    
    # Split the right pane horizontally to create fourth pane (top-right becomes two)
    tmux split-window -h -t "$SESSION_NAME:0.2"
    
    # Select layout to make all panes equal size horizontally
    tmux select-layout -t "$SESSION_NAME:0" even-horizontal
    
    # Send claude.sh command to each pane
    tmux send-keys -t "$SESSION_NAME:0.0" './claude.sh' C-m
    tmux send-keys -t "$SESSION_NAME:0.1" './claude.sh' C-m
    tmux send-keys -t "$SESSION_NAME:0.2" './claude.sh' C-m
    tmux send-keys -t "$SESSION_NAME:0.3" './claude.sh' C-m
    
    echo "Session created with 4 claude instances"
else
    echo "Session $SESSION_NAME already exists"
fi

# Attach to the session
echo "Attaching to session $SESSION_NAME..."
tmux attach-session -t "$SESSION_NAME"