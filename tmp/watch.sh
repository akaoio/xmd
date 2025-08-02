#!/bin/bash

# XMD Watch Script for Teamwork Dashboard
# Watches teamwork/dashboard.md and outputs to teamwork.md in real-time

echo "Starting XMD watch for teamwork dashboard..."
echo "Watching: teamwork/dashboard.md"
echo "Output: teamwork.md"
echo ""
echo "Press Ctrl+C to stop watching"
echo ""

# Run xmd watch command
xmd watch teamwork/dashboard.md teamwork.md

# If xmd watch exits, show message
echo ""
echo "Watch stopped."