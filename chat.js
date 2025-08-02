#!/usr/bin/env node

const fs = require('fs');
const path = require('path');

const CHAT_DIR = './chat';

// Ensure directories exist
if (!fs.existsSync(CHAT_DIR)) {
    fs.mkdirSync(CHAT_DIR, { recursive: true });
}

// Get role emoji and display
function getRoleDisplay(role) {
    return `👤 ${role.toUpperCase()}`;
}

// Get target display
function getTargetDisplay(target) {
    const clean = target.replace('@', '').toLowerCase();
    if (clean === 'all') {
        return '👥 ALL';
    }
    return `👤 ${target.replace('@', '').toUpperCase()}`;
}

// Parse message format: @from: @to message
function parseMessage(args) {
    const fullInput = args.join(' ');
    
    // Regex to match @from: @to message (with proper multi-line support)
    const match = fullInput.match(/^@([^:]+):\s*@([^\s]+)\s+(.+)$/s);
    
    if (!match) {
        console.error('❌ ERROR: Invalid syntax!');
        console.error('REQUIRED FORMAT: node chat.js @<from>: @<to> <message>');
        console.error('Examples:');
        console.error('  node chat.js @developer: @leader "Build complete!"');
        console.error('  node chat.js @alice: @bob "Hello!"');
        console.error('  node chat.js @systems: @all "System update"');
        process.exit(1);
    }
    
    return {
        sender: match[1].trim(),
        target: '@' + match[2].trim(), 
        content: match[3].trim()
    };
}

// Send message
function sendMessage(args) {
    const { sender, target, content } = parseMessage(args);
    const timestamp = new Date().toISOString().slice(0, 19).replace('T', ' ');
    const senderDisplay = getRoleDisplay(sender);
    const targetDisplay = getTargetDisplay(target);
    
    // Create unique filename for each message
    const messageId = Date.now() + '_' + Math.random().toString(36).substr(2, 9);
    const messageFile = path.join(CHAT_DIR, `msg_${messageId}.txt`);
    
    // Format message with full content preserved
    const fullMessage = `[${timestamp}] ${senderDisplay} → ${targetDisplay}: ${content}`;
    
    // Save each message to its own file
    fs.writeFileSync(messageFile, fullMessage);
    
    console.log('');
    console.log(`✅ ${senderDisplay} → ${targetDisplay}`);
    console.log(`💬 ${content}`);
    console.log('');
}

// Show header
function showHeader() {
    const role = process.env.XMD_ROLE || 'User';
    const timestamp = new Date().toISOString().slice(0, 19).replace('T', ' ');
    
    console.log('---');
    console.log('🚀 XMD TEAM CHAT');
    console.log(`Role: ${role} | Time: ${timestamp}`);
    console.log('---');
}

// Show messages
function showMessages() {
    console.log('');
    console.log('📨 TEAM CHAT HISTORY (Latest 10 messages):');
    console.log('---')
    
    // Get all message files
    const messageFiles = fs.readdirSync(CHAT_DIR)
        .filter(file => file.startsWith('msg_') && file.endsWith('.txt'))
        .map(file => path.join(CHAT_DIR, file))
        .sort((a, b) => fs.statSync(a).mtime - fs.statSync(b).mtime); // Sort by creation time
    
    if (messageFiles.length === 0) {
        console.log('💬 No messages yet. Be the first to send one!');
        console.log('Usage: node chat.js @sender: @target "message"');
        return;
    }
    
    // Show last 10 messages
    const recent = messageFiles.slice(-10);
    
    recent.forEach(messageFile => {
        const message = fs.readFileSync(messageFile, 'utf8').trim();
        if (message) {
            const highlight = message.includes('→ 👥 ALL:') ? '⭐ ' : '';
            
            // Show message with highlight for @all only
            console.log(`${highlight}${message}`);
            console.log('---');
        }
    });
}

// Show help
function showHelp() {
    console.log('🚀 XMD TEAM CHAT - Node.js Version');
    console.log('');
    console.log('📨 BASIC COMMANDS:');
    console.log('  node chat.js                              - View recent messages');
    console.log('  node chat.js @<from>: @<to> <message>    - Send message');
    console.log('  node chat.js help                        - Show this help');
    console.log('');
    console.log('📋 MESSAGE EXAMPLES:');
    console.log('  node chat.js @systems: @all "Hello team"');
    console.log('  node chat.js @leader: @developer "Do task"');
    console.log('  node chat.js @alice: @bob "Hello!"');
    console.log('');
    console.log('🎯 ROLES:');
    console.log('  @all, @leader, @developer, @systems, @tester, @designer');
    console.log('  Or use any custom name like @alice, @bob, etc.');
    console.log('');
    console.log('💡 MULTI-LINE SUPPORT:');
    console.log('  Use quotes for multi-line messages:');
    console.log('  node chat.js @dev: @all "Line 1');
    console.log('  Line 2');
    console.log('  Line 3"');
    console.log('');
}

// Main function
function main() {
    const args = process.argv.slice(2);
    
    showHeader();
    
    if (args.length === 0) {
        // No arguments - show messages
        showMessages();
    } else if (args[0] === 'help' || args[0] === '-h' || args[0] === '--help') {
        showHelp();
    } else {
        // Send message
        sendMessage(args);
        showMessages();
    }
}

// Run
main();