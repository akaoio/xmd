#!/bin/bash
# XMD Team Collaboration Quick Setup

echo "🚀 Setting up XMD team collaboration..."

# Create teamwork directory structure
mkdir -p teamwork/update
cd teamwork

# Copy dashboard template
cp ../templates/teamwork/dashboard.md .

# Copy role templates  
cp ../templates/teamwork/update/*.md update/

echo "✅ Setup complete!"
echo ""
echo "📋 Next steps:"
echo "1. Edit update/<role>.md files for your team members"
echo "2. Start live dashboard: ../xmd watch dashboard.md live_dashboard.md"
echo "3. View dashboard: open live_dashboard.md"
echo ""
echo "📖 For detailed instructions, see docs/collaboration.md"