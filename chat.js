#!/usr/bin/env node

const fs = require('fs');
const path = require('path');

const CHAT_DIR = './chat';
const PINNED_DIR = path.join(CHAT_DIR, 'pinned');

// Ensure directories exist
if (!fs.existsSync(CHAT_DIR)) {
    fs.mkdirSync(CHAT_DIR, { recursive: true });
}
if (!fs.existsSync(PINNED_DIR)) {
    fs.mkdirSync(PINNED_DIR, { recursive: true });
}

// Color codes
const colors = {
    reset: '\x1b[0m',
    red: '\x1b[31m',
    green: '\x1b[32m',
    yellow: '\x1b[33m',
    blue: '\x1b[34m',
    magenta: '\x1b[35m',
    cyan: '\x1b[36m',
    white: '\x1b[37m',
    bold: '\x1b[1m',
    dim: '\x1b[2m'
};

// Get role emoji and display with color
function getRoleDisplay(role, isColored = false) {
    const display = `👤 ${role.toUpperCase()}`;
    if (!isColored) return display;
    
    // Color based on role name
    const roleColors = {
        'leader': colors.green,
        'developer': colors.blue,
        'systems': colors.cyan,
        'tester': colors.magenta,
        'debthunter': colors.yellow,
        'designer': colors.red
    };
    
    const color = roleColors[role.toLowerCase()] || colors.white;
    return color + display + colors.reset;
}

// Get target display with color
function getTargetDisplay(target, isColored = false) {
    const clean = target.replace('@', '').toLowerCase();
    if (clean === 'all') {
        const display = '👥 ALL';
        return isColored ? colors.bold + colors.yellow + display + colors.reset : display;
    }
    const display = `👤 ${target.replace('@', '').toUpperCase()}`;
    if (!isColored) return display;
    
    // Same coloring for targets
    const targetColors = {
        'leader': colors.green,
        'developer': colors.blue,
        'systems': colors.cyan,
        'tester': colors.magenta,
        'debthunter': colors.yellow,
        'designer': colors.red
    };
    
    const color = targetColors[clean] || colors.white;
    return color + display + colors.reset;
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

// Format timestamp to be shorter
function formatTimestamp(date) {
    const d = new Date(date);
    const month = String(d.getMonth() + 1).padStart(2, '0');
    const day = String(d.getDate()).padStart(2, '0');
    const hour = String(d.getHours()).padStart(2, '0');
    const min = String(d.getMinutes()).padStart(2, '0');
    return `${month}/${day} ${hour}:${min}`;
}

// Send message
function sendMessage(args) {
    const { sender, target, content } = parseMessage(args);
    const timestamp = new Date().toISOString();
    const senderDisplay = getRoleDisplay(sender);
    const targetDisplay = getTargetDisplay(target);
    
    // Create unique filename for each message
    const messageId = Date.now() + '_' + Math.random().toString(36).substr(2, 9);
    const messageFile = path.join(CHAT_DIR, `msg_${messageId}.txt`);
    
    // Format message with full content preserved - store full timestamp for sorting
    const fullMessage = `${timestamp}|${senderDisplay}|${targetDisplay}|${content}`;
    
    // Save each message to its own file
    fs.writeFileSync(messageFile, fullMessage);
    
    console.log('');
    console.log(`✅ ${getRoleDisplay(sender, true)} → ${getTargetDisplay(target, true)}`);
    console.log(`💬 ${content}`);
    console.log('');
}

// Show header
function showHeader() {
    const role = process.env.XMD_ROLE || 'User';
    const timestamp = formatTimestamp(new Date());
    
    console.log("\n" + colors.dim + "═══════════════════════" + colors.reset);
    console.log('🚀 XMD TEAM CHAT');
    console.log(`Role: ${colors.bold}${role}${colors.reset} | ${formatTimestamp(new Date())}`);
    console.log(colors.dim + "═══════════════════════" + colors.reset + "\n");
}

// Show pinned messages
function showPinnedMessages() {
    const pinnedFiles = fs.readdirSync(PINNED_DIR)
        .filter(file => file.startsWith('pinned_') && file.endsWith('.txt'))
        .map(file => path.join(PINNED_DIR, file))
        .sort((a, b) => fs.statSync(b).mtime - fs.statSync(a).mtime); // Newest first
    
    if (pinnedFiles.length > 0) {
        console.log(colors.bold + colors.yellow + '📌 PINNED MESSAGES' + colors.reset);
        console.log(colors.dim + '───────────────────────' + colors.reset);
        
        pinnedFiles.slice(0, 3).forEach(file => {
            const content = fs.readFileSync(file, 'utf8').trim();
            const [timestamp, sender, target, message] = content.split('|');
            const shortTime = formatTimestamp(timestamp);
            
            console.log(colors.bold + colors.yellow + '📌 ' + colors.reset + 
                       colors.dim + `[${shortTime}]` + colors.reset + ' ' +
                       getRoleDisplay(sender.replace(/👤\s*/, ''), true) + ' → ' + 
                       getTargetDisplay(target.replace(/👤\s*|👥\s*/, '@'), true) + 
                       ': ' + message);
            console.log(colors.dim + '···' + colors.reset);
        });
        console.log('');
    }
}

// Show messages (newest first)
function showMessages() {
    // Get all message files
    const messageFiles = fs.readdirSync(CHAT_DIR)
        .filter(file => file.startsWith('msg_') && file.endsWith('.txt'))
        .map(file => path.join(CHAT_DIR, file))
        .sort((a, b) => fs.statSync(b).mtime - fs.statSync(a).mtime); // Sort newest first
    
    if (messageFiles.length === 0) {
        console.log('💬 No messages yet. Be the first to send one!');
        console.log('Usage: node chat.js @sender: @target "message"');
        return;
    }
    
    console.log(colors.bold + '📨 RECENT MESSAGES' + colors.reset + ' (newest first)');
    console.log(colors.dim + '───────────────────────' + colors.reset);
    
    // Show last 10 messages
    const recent = messageFiles.slice(0, 10);
    
    recent.forEach((messageFile, index) => {
        const content = fs.readFileSync(messageFile, 'utf8').trim();
        if (content) {
            // Handle both old and new message formats
            let timestamp, sender, target, message;
            
            if (content.includes('|')) {
                // New format with pipe separators
                [timestamp, sender, target, message] = content.split('|');
            } else {
                // Old format - try to parse it
                const match = content.match(/\[([^\]]+)\]\s*([^→]+)→\s*([^:]+):\s*(.*)/s);
                if (match) {
                    timestamp = match[1];
                    sender = match[2].trim();
                    target = match[3].trim();
                    message = match[4];
                } else {
                    // Can't parse, skip this message
                    return;
                }
            }
            
            if (!sender || !target) return; // Skip invalid messages
            
            const shortTime = formatTimestamp(timestamp);
            const isToAll = target && target.includes('ALL');
            
            // Clean up sender and target for display
            const cleanSender = sender.replace(/👤\s*|👥\s*/, '').trim();
            const cleanTarget = target.replace(/👤\s*|👥\s*/, '').replace(/^@*/, '@').trim();
            
            // Format with colors
            let displayLine = colors.dim + `[${shortTime}]` + colors.reset + ' ';
            displayLine += getRoleDisplay(cleanSender, true) + ' → ';
            displayLine += getTargetDisplay(cleanTarget, true);
            
            // Add star for broadcasts
            if (isToAll) {
                displayLine = '⭐ ' + displayLine;
            }
            
            console.log(displayLine);
            
            // Message content with slight indentation
            const messageLines = message.split('\n');
            messageLines.forEach(line => {
                console.log('   ' + line);
            });
            
            // Separator (except for last message)
            if (index < recent.length - 1) {
                console.log(colors.dim + '···' + colors.reset);
            }
        }
    });
}

// Pin a message
function pinMessage(messageNumber) {
    const messageFiles = fs.readdirSync(CHAT_DIR)
        .filter(file => file.startsWith('msg_') && file.endsWith('.txt'))
        .map(file => path.join(CHAT_DIR, file))
        .sort((a, b) => fs.statSync(b).mtime - fs.statSync(a).mtime);
    
    if (messageNumber < 1 || messageNumber > messageFiles.length) {
        console.error('❌ Invalid message number');
        return;
    }
    
    const sourceFile = messageFiles[messageNumber - 1];
    const content = fs.readFileSync(sourceFile, 'utf8');
    const pinnedFile = path.join(PINNED_DIR, `pinned_${Date.now()}.txt`);
    
    fs.writeFileSync(pinnedFile, content);
    console.log('📌 Message pinned successfully!');
}

// Unpin a message
function unpinMessage(pinnedNumber) {
    const pinnedFiles = fs.readdirSync(PINNED_DIR)
        .filter(file => file.startsWith('pinned_') && file.endsWith('.txt'))
        .map(file => path.join(PINNED_DIR, file))
        .sort((a, b) => fs.statSync(b).mtime - fs.statSync(a).mtime);
    
    if (pinnedNumber < 1 || pinnedNumber > pinnedFiles.length) {
        console.error('❌ Invalid pinned message number');
        return;
    }
    
    fs.unlinkSync(pinnedFiles[pinnedNumber - 1]);
    console.log('✅ Message unpinned successfully!');
}

// List messages for pinning
function listMessagesForPinning() {
    const messageFiles = fs.readdirSync(CHAT_DIR)
        .filter(file => file.startsWith('msg_') && file.endsWith('.txt'))
        .map(file => path.join(CHAT_DIR, file))
        .sort((a, b) => fs.statSync(b).mtime - fs.statSync(a).mtime);
    
    console.log(colors.bold + '📋 SELECT MESSAGE TO PIN' + colors.reset);
    console.log(colors.dim + '───────────────────────' + colors.reset);
    
    messageFiles.slice(0, 10).forEach((file, index) => {
        const content = fs.readFileSync(file, 'utf8').trim();
        let timestamp, sender, target, message;
        
        if (content.includes('|')) {
            [timestamp, sender, target, message] = content.split('|');
        } else {
            // Old format - try to parse it
            const match = content.match(/\[([^\]]+)\]\s*([^→]+)→\s*([^:]+):\s*(.*)/s);
            if (match) {
                timestamp = match[1];
                sender = match[2].trim();
                target = match[3].trim();
                message = match[4];
            } else {
                return; // Skip unparseable messages
            }
        }
        
        if (!message) message = '';
        const shortTime = formatTimestamp(timestamp);
        const preview = message.split('\n')[0].substring(0, 50) + (message.length > 50 ? '...' : '');
        
        console.log(`[${index + 1}] ${colors.dim}${shortTime}${colors.reset} ${sender} → ${target}: ${preview}`);
    });
    
    console.log('\nUsage: node chat.js pin <number>');
}

// List pinned messages for unpinning
function listPinnedForUnpinning() {
    const pinnedFiles = fs.readdirSync(PINNED_DIR)
        .filter(file => file.startsWith('pinned_') && file.endsWith('.txt'))
        .map(file => path.join(PINNED_DIR, file))
        .sort((a, b) => fs.statSync(b).mtime - fs.statSync(a).mtime);
    
    if (pinnedFiles.length === 0) {
        console.log('📌 No pinned messages');
        return;
    }
    
    console.log(colors.bold + '📌 PINNED MESSAGES' + colors.reset);
    console.log(colors.dim + '───────────────────────' + colors.reset);
    
    pinnedFiles.forEach((file, index) => {
        const content = fs.readFileSync(file, 'utf8').trim();
        const [timestamp, sender, target, message] = content.split('|');
        const shortTime = formatTimestamp(timestamp);
        const preview = message.split('\n')[0].substring(0, 50) + (message.length > 50 ? '...' : '');
        
        console.log(`[${index + 1}] ${colors.dim}${shortTime}${colors.reset} ${sender} → ${target}: ${preview}`);
    });
    
    console.log('\nUsage: node chat.js unpin <number>');
}

// Show help
function showHelp() {
    console.log(colors.bold + '🚀 XMD TEAM CHAT - Complete Guide' + colors.reset);
    console.log(colors.dim + '═══════════════════════════════════' + colors.reset);
    console.log('');
    console.log(colors.bold + '📨 BASIC COMMANDS:' + colors.reset);
    console.log('  node chat.js                              - View recent messages & pinned');
    console.log('  node chat.js @<from>: @<to> <message>    - Send a message');
    console.log('  node chat.js help                        - Show this complete guide');
    console.log('');
    console.log(colors.bold + '📌 PINNING COMMANDS:' + colors.reset);
    console.log('  node chat.js pin                         - List messages to pin');
    console.log('  node chat.js pin <number>                - Pin specific message');
    console.log('  node chat.js unpin                       - List pinned messages');
    console.log('  node chat.js unpin <number>              - Unpin specific message');
    console.log('  node chat.js pinned                      - Show only pinned messages');
    console.log('');
    console.log(colors.bold + '📋 MESSAGE EXAMPLES:' + colors.reset);
    console.log('  node chat.js @systems: @all "Hello team"');
    console.log('  node chat.js @leader: @developer "Do task"');
    console.log('  node chat.js @alice: @bob "Hello!"');
    console.log('');
    console.log(colors.bold + '🎯 SPECIAL TARGETS:' + colors.reset);
    console.log('  @all - Broadcast to everyone (shows with ⭐)');
    console.log('  @<username> - Direct message to specific person');
    console.log('');
    console.log(colors.bold + '💡 FEATURES:' + colors.reset);
    console.log('  • Newest messages appear first');
    console.log('  • Color-coded senders and receivers');
    console.log('  • Shortened timestamps (MM/DD HH:MM)');
    console.log('  • Pin important messages for visibility');
    console.log('  • Multi-line message support');
    console.log('  • Individual file storage per message');
    console.log('  • Broadcast messages highlighted with ⭐');
    console.log('');
    console.log(colors.bold + '🎨 COLOR CODING:' + colors.reset);
    console.log('  ' + colors.green + '👤 LEADER' + colors.reset + '     - Green');
    console.log('  ' + colors.blue + '👤 DEVELOPER' + colors.reset + '  - Blue');
    console.log('  ' + colors.cyan + '👤 SYSTEMS' + colors.reset + '    - Cyan');
    console.log('  ' + colors.magenta + '👤 TESTER' + colors.reset + '     - Magenta');
    console.log('  ' + colors.yellow + '👤 DEBTHUNTER' + colors.reset + ' - Yellow');
    console.log('  ' + colors.red + '👤 DESIGNER' + colors.reset + '   - Red');
    console.log('  ' + colors.white + '👤 OTHERS' + colors.reset + '     - White');
    console.log('');
    console.log(colors.bold + '📝 MULTI-LINE MESSAGES:' + colors.reset);
    console.log('  Use quotes to include line breaks:');
    console.log('  node chat.js @dev: @all "Line 1');
    console.log('  Line 2');
    console.log('  Line 3"');
    console.log('');
    console.log(colors.bold + '💾 STORAGE:' + colors.reset);
    console.log('  • Messages: ./chat/msg_*.txt');
    console.log('  • Pinned: ./chat/pinned/pinned_*.txt');
    console.log('');
}

// Main function
function main() {
    const args = process.argv.slice(2);
    
    if (args.length === 0) {
        // No arguments - show header, pinned, and messages
        showHeader();
        showPinnedMessages();
        showMessages();
    } else if (args[0] === 'help' || args[0] === '-h' || args[0] === '--help') {
        showHelp();
    } else if (args[0] === 'pin') {
        if (args[1]) {
            pinMessage(parseInt(args[1]));
        } else {
            listMessagesForPinning();
        }
    } else if (args[0] === 'unpin') {
        if (args[1]) {
            unpinMessage(parseInt(args[1]));
        } else {
            listPinnedForUnpinning();
        }
    } else if (args[0] === 'pinned') {
        showHeader();
        showPinnedMessages();
    } else {
        // Send message
        showHeader();
        sendMessage(args);
        showPinnedMessages();
        showMessages();
    }
}

// Run
main();