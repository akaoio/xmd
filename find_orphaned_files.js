#!/usr/bin/env node

/**
 * Accurate orphaned files scanner for XMD project
 * Finds files that are truly not used in the build system
 */

const fs = require('fs');
const path = require('path');

const PROJECT_ROOT = '/home/x/Projects/xmd';
const SRC_DIR = path.join(PROJECT_ROOT, 'src');

// Track all referenced files
const referencedFiles = new Set();
const cmakeTargets = new Map(); // target -> files
const allSourceFiles = new Set();

function getAllFiles(dir, pattern = /\.(c|h)$/) {
    const files = [];
    if (!fs.existsSync(dir)) return files;
    
    const items = fs.readdirSync(dir);
    for (const item of items) {
        const fullPath = path.join(dir, item);
        const stat = fs.statSync(fullPath);
        if (stat.isDirectory()) {
            files.push(...getAllFiles(fullPath, pattern));
        } else if (pattern.test(item)) {
            files.push(fullPath);
        }
    }
    return files;
}

function extractCMakeVariables(content) {
    const variables = new Map();
    
    // Match set() commands
    const setRegex = /set\s*\(\s*(\w+)\s+((?:[^\)\\]|\\.|\\\n)+)\)/gms;
    let match;
    
    while ((match = setRegex.exec(content)) !== null) {
        const varName = match[1];
        const value = match[2].trim();
        
        // Split value into list items (CMake uses whitespace or semicolons)
        const items = value.split(/[\s;]+/)
            .map(item => item.trim())
            .filter(item => item && !item.startsWith('#'));
        
        variables.set(varName, items);
    }
    
    return variables;
}

function expandVariables(content, variables) {
    // Replace ${VAR} references
    let expanded = content;
    const varRegex = /\$\{(\w+)\}/g;
    
    let iterations = 0;
    while (varRegex.test(expanded) && iterations < 10) {
        expanded = expanded.replace(varRegex, (match, varName) => {
            if (variables.has(varName)) {
                return variables.get(varName).join(' ');
            }
            return match;
        });
        iterations++;
    }
    
    return expanded;
}

function analyzeCMakeFile(cmakePath) {
    console.log(`Analyzing: ${path.relative(PROJECT_ROOT, cmakePath)}`);
    
    const content = fs.readFileSync(cmakePath, 'utf-8');
    const dir = path.dirname(cmakePath);
    
    // Extract variables
    const variables = extractCMakeVariables(content);
    
    // Process file(GLOB ...) commands first to populate variables
    const globRegex = /file\s*\(\s*(GLOB|GLOB_RECURSE)\s+(\w+)\s+((?:[^\)\\]|\\.|\\\n)+)\)/gms;
    let match;
    
    while ((match = globRegex.exec(content)) !== null) {
        const globType = match[1];
        const varName = match[2];
        const patterns = match[3];
        
        // Extract patterns
        const patternList = patterns.split(/[\s;]+/)
            .map(p => p.trim())
            .filter(p => p && !p.startsWith('#'));
        
        const files = [];
        patternList.forEach(pattern => {
            // Remove quotes if present
            pattern = pattern.replace(/^["']|["']$/g, '');
            
            // Resolve pattern relative to CMake file directory
            const resolvedPattern = path.resolve(dir, pattern);
            
            if (globType === 'GLOB_RECURSE') {
                // For GLOB_RECURSE, find all matching files recursively
                const baseDir = resolvedPattern.substring(0, resolvedPattern.lastIndexOf('*'));
                const filePattern = resolvedPattern.substring(resolvedPattern.lastIndexOf('/') + 1);
                
                if (fs.existsSync(baseDir)) {
                    const regex = new RegExp('^' + filePattern.replace(/\*/g, '.*') + '$');
                    const matchedFiles = getAllFiles(baseDir)
                        .filter(f => regex.test(path.basename(f)));
                    files.push(...matchedFiles);
                }
            } else {
                // For regular GLOB, only match in the specific directory
                const patternDir = path.dirname(resolvedPattern);
                const patternFile = path.basename(resolvedPattern);
                
                if (patternFile.includes('*') && fs.existsSync(patternDir)) {
                    const regex = new RegExp('^' + patternFile.replace(/\*/g, '.*') + '$');
                    const dirFiles = fs.readdirSync(patternDir)
                        .filter(f => regex.test(f))
                        .map(f => path.join(patternDir, f))
                        .filter(f => fs.statSync(f).isFile());
                    files.push(...dirFiles);
                }
            }
        });
        
        variables.set(varName, files);
    }
    
    // Expand variables in content
    const expandedContent = expandVariables(content, variables);
    
    // Find add_library() calls
    const libRegex = /add_library\s*\(\s*(\w+)(?:\s+STATIC|\s+SHARED)?\s+((?:[^\)\\]|\\.|\\\n)+)\)/gms;
    
    while ((match = libRegex.exec(expandedContent)) !== null) {
        const target = match[1];
        const sources = match[2];
        
        // Extract source files and variables
        const sourceItems = sources.split(/[\s;]+/)
            .map(item => item.trim())
            .filter(item => item && !item.startsWith('#'));
        
        if (!cmakeTargets.has(target)) {
            cmakeTargets.set(target, []);
        }
        
        sourceItems.forEach(item => {
            // Check if it's a variable reference
            if (item.match(/^\$\{(\w+)\}$/)) {
                const varName = item.match(/^\$\{(\w+)\}$/)[1];
                if (variables.has(varName)) {
                    // Add all files from the variable
                    variables.get(varName).forEach(file => {
                        referencedFiles.add(file);
                        cmakeTargets.get(target).push(file);
                    });
                }
            } else if (/\.(c|cpp|cc|cxx)$/i.test(item)) {
                // It's a direct file reference
                const fullPath = path.resolve(dir, item);
                referencedFiles.add(fullPath);
                cmakeTargets.get(target).push(fullPath);
            }
        });
    }
    
    // Find add_executable() calls
    const exeRegex = /add_executable\s*\(\s*(\w+)\s+((?:[^\)\\]|\\.|\\\n)+)\)/gms;
    
    while ((match = exeRegex.exec(expandedContent)) !== null) {
        const target = match[1];
        const sources = match[2];
        
        const sourceItems = sources.split(/[\s;]+/)
            .map(item => item.trim())
            .filter(item => item && !item.startsWith('#'));
        
        if (!cmakeTargets.has(target)) {
            cmakeTargets.set(target, []);
        }
        
        sourceItems.forEach(item => {
            // Check if it's a variable reference
            if (item.match(/^\$\{(\w+)\}$/)) {
                const varName = item.match(/^\$\{(\w+)\}$/)[1];
                if (variables.has(varName)) {
                    // Add all files from the variable
                    variables.get(varName).forEach(file => {
                        referencedFiles.add(file);
                        cmakeTargets.get(target).push(file);
                    });
                }
            } else if (/\.(c|cpp|cc|cxx)$/i.test(item)) {
                // It's a direct file reference
                const fullPath = path.resolve(dir, item);
                referencedFiles.add(fullPath);
                cmakeTargets.get(target).push(fullPath);
            }
        });
    }
    
    
    // Check for subdirectory includes
    const subdirRegex = /add_subdirectory\s*\(\s*([^\s\)]+)\s*\)/g;
    
    while ((match = subdirRegex.exec(content)) !== null) {
        const subdir = match[1];
        const subdirPath = path.join(dir, subdir, 'CMakeLists.txt');
        if (fs.existsSync(subdirPath)) {
            analyzeCMakeFile(subdirPath);
        }
    }
}

// Main analysis
console.log('XMD Orphaned Files Scanner');
console.log('==========================\n');

// Find all source files
console.log('Collecting all source files...');
const sourceFiles = getAllFiles(SRC_DIR);
sourceFiles.forEach(file => allSourceFiles.add(file));

console.log(`Found ${allSourceFiles.size} source files\n`);

// Analyze CMake files
console.log('Analyzing CMake build system...\n');
const rootCMake = path.join(PROJECT_ROOT, 'CMakeLists.txt');
if (fs.existsSync(rootCMake)) {
    analyzeCMakeFile(rootCMake);
}

// Also check test directory CMake files
const testCMake = path.join(PROJECT_ROOT, 'test', 'CMakeLists.txt');
if (fs.existsSync(testCMake)) {
    analyzeCMakeFile(testCMake);
}

// Find orphaned files
const orphanedFiles = [];
const usedFiles = [];

allSourceFiles.forEach(file => {
    if (!referencedFiles.has(file)) {
        orphanedFiles.push(file);
    } else {
        usedFiles.push(file);
    }
});

// Group orphaned files by directory
const orphanedByDir = new Map();
orphanedFiles.forEach(file => {
    const dir = path.dirname(file);
    const relDir = path.relative(SRC_DIR, dir);
    if (!orphanedByDir.has(relDir)) {
        orphanedByDir.set(relDir, []);
    }
    orphanedByDir.get(relDir).push(path.basename(file));
});

// Report findings
console.log('\n=== BUILD SYSTEM ANALYSIS ===\n');
console.log(`Total CMake targets found: ${cmakeTargets.size}`);
console.log(`Total files referenced in CMake: ${referencedFiles.size}`);
console.log(`Total source files in src/: ${allSourceFiles.size}`);
console.log(`Orphaned files: ${orphanedFiles.length}`);

if (orphanedFiles.length > 0) {
    console.log('\n=== ORPHANED FILES BY DIRECTORY ===\n');
    
    // Sort directories by number of orphaned files
    const sortedDirs = Array.from(orphanedByDir.entries())
        .sort((a, b) => b[1].length - a[1].length);
    
    sortedDirs.forEach(([dir, files]) => {
        console.log(`${dir}/ (${files.length} files)`);
        files.forEach(file => console.log(`  - ${file}`));
    });
    
    // Find patterns
    console.log('\n=== ANALYSIS ===\n');
    
    // Check if entire directories are orphaned
    const orphanedDirs = new Set();
    orphanedByDir.forEach((files, dir) => {
        const dirPath = path.join(SRC_DIR, dir);
        const allFilesInDir = fs.readdirSync(dirPath).filter(f => f.endsWith('.c'));
        if (files.length === allFilesInDir.length) {
            orphanedDirs.add(dir);
        }
    });
    
    if (orphanedDirs.size > 0) {
        console.log(`Entire directories orphaned: ${orphanedDirs.size}`);
        orphanedDirs.forEach(dir => console.log(`  - ${dir}/`));
    }
}

// Show sample of used files to verify
console.log('\n=== SAMPLE OF REFERENCED FILES ===\n');
usedFiles.slice(0, 10).forEach(file => {
    console.log(`  ${path.relative(PROJECT_ROOT, file)}`);
});

if (usedFiles.length > 10) {
    console.log(`  ... and ${usedFiles.length - 10} more files`);
}