#!/usr/bin/env node

/**
 * Codebase analyzer for XMD project
 * Checks compliance with INSTRUCTIONS.md rules
 */

const fs = require('fs');
const path = require('path');

// Configuration
const PROJECT_ROOT = '/home/x/Projects/xmd';
const SRC_DIR = path.join(PROJECT_ROOT, 'src');
const TEST_DIR = path.join(PROJECT_ROOT, 'test');
const MAX_LINES_PER_FILE = 200;

// Results storage
const results = {
    ruleViolations: [],
    orphanedFiles: [],
    emptyFiles: [],
    oversizedFiles: [],
    duplicatedFunctions: new Map(),
    mismatchedFunctions: [],
    multipleFunctionsInFile: [],
    todosAndFixmes: [],
    fakeImplementations: [],
    missingNullChecks: [],
    memoryLeaks: [],
    zombieCode: []
};

// Helper functions
function getAllFiles(dir, fileList = []) {
    if (!fs.existsSync(dir)) return fileList;
    
    const files = fs.readdirSync(dir);
    files.forEach(file => {
        const filePath = path.join(dir, file);
        const stat = fs.statSync(filePath);
        if (stat.isDirectory()) {
            getAllFiles(filePath, fileList);
        } else if (file.endsWith('.c') || file.endsWith('.h')) {
            fileList.push(filePath);
        }
    });
    return fileList;
}

function getFileLineCount(filePath) {
    try {
        const content = fs.readFileSync(filePath, 'utf-8');
        return content.split('\n').length;
    } catch (e) {
        return 0;
    }
}

function extractFunctionNames(content) {
    const functions = [];
    // Match function definitions (return_type function_name(...) {)
    const funcRegex = /^(?!\/\/|\/\*|\s*\*)[a-zA-Z_][a-zA-Z0-9_*\s]*\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*\([^)]*\)\s*\{/gm;
    let match;
    while ((match = funcRegex.exec(content)) !== null) {
        functions.push(match[1]);
    }
    return functions;
}

function checkRule1(filePath) {
    // Rule 1: One file per folder
    const dir = path.dirname(filePath);
    const filesInDir = fs.readdirSync(dir).filter(f => f.endsWith('.c'));
    if (filesInDir.length > 1) {
        results.ruleViolations.push({
            rule: 1,
            file: filePath,
            message: `Multiple .c files in directory: ${dir} (found ${filesInDir.length} files)`
        });
    }
}

function checkRule2(filePath, content) {
    // Rule 2: One function per file
    const functions = extractFunctionNames(content);
    if (functions.length > 1) {
        results.multipleFunctionsInFile.push({
            file: filePath,
            functions: functions,
            count: functions.length
        });
        results.ruleViolations.push({
            rule: 2,
            file: filePath,
            message: `Multiple functions in file: ${functions.join(', ')}`
        });
    }
}

function checkRule3(filePath, content) {
    // Rule 3: File and folder naming convention
    const dir = path.basename(path.dirname(filePath));
    const filename = path.basename(filePath, '.c');
    
    if (dir !== filename) {
        // Check if the file contains the expected function
        const functions = extractFunctionNames(content);
        const expectedFunction = filename;
        
        if (functions.length > 0 && !functions.includes(expectedFunction)) {
            results.mismatchedFunctions.push({
                file: filePath,
                expected: expectedFunction,
                actual: functions
            });
            results.ruleViolations.push({
                rule: 3,
                file: filePath,
                message: `Function name mismatch: expected '${expectedFunction}', found '${functions.join(', ')}'`
            });
        }
    }
}

function checkRule5(filePath) {
    // Rule 5: Maximum 200 lines per file
    const lineCount = getFileLineCount(filePath);
    if (lineCount > MAX_LINES_PER_FILE) {
        results.oversizedFiles.push({
            file: filePath,
            lines: lineCount,
            excess: lineCount - MAX_LINES_PER_FILE
        });
        results.ruleViolations.push({
            rule: 5,
            file: filePath,
            message: `File exceeds 200 lines (${lineCount} lines)`
        });
    }
}

function checkRule6(filePath, content) {
    // Rule 6: No duplicated code
    const functions = extractFunctionNames(content);
    functions.forEach(func => {
        if (!results.duplicatedFunctions.has(func)) {
            results.duplicatedFunctions.set(func, []);
        }
        results.duplicatedFunctions.get(func).push(filePath);
    });
}

function checkRule7(filePath, content) {
    // Rule 7: Real implementation (no mocks, TODOs, fake implementations)
    const lowerContent = content.toLowerCase();
    
    // Check for TODO/FIXME comments
    const todoRegex = /\/\/\s*(TODO|FIXME|HACK|XXX|BUG|STUB)[\s:]/gi;
    const todos = content.match(todoRegex);
    if (todos) {
        todos.forEach(todo => {
            results.todosAndFixmes.push({
                file: filePath,
                type: todo.trim()
            });
        });
    }
    
    // Check for fake implementations
    const fakePatterns = [
        /return\s+NULL\s*;\s*\/\/\s*TODO/,
        /return\s+0\s*;\s*\/\/\s*TODO/,
        /return\s+-1\s*;\s*\/\/\s*TODO/,
        /\/\/\s*stub/i,
        /\/\/\s*placeholder/i,
        /\/\/\s*not\s+implemented/i,
        /fprintf\s*\(\s*stderr\s*,\s*"not\s+implemented/i
    ];
    
    for (const pattern of fakePatterns) {
        if (pattern.test(content)) {
            results.fakeImplementations.push({
                file: filePath,
                pattern: pattern.toString()
            });
            results.ruleViolations.push({
                rule: 7,
                file: filePath,
                message: 'Contains fake/stub implementation'
            });
            break;
        }
    }
}

function checkRule13(filePath, content) {
    // Rule 13: Error handling
    const mallocRegex = /(\w+)\s*=\s*malloc\s*\(/g;
    const callocRegex = /(\w+)\s*=\s*calloc\s*\(/g;
    const reallocRegex = /(\w+)\s*=\s*realloc\s*\(/g;
    
    let match;
    const allocations = [];
    
    while ((match = mallocRegex.exec(content)) !== null) {
        allocations.push({ var: match[1], type: 'malloc', index: match.index });
    }
    while ((match = callocRegex.exec(content)) !== null) {
        allocations.push({ var: match[1], type: 'calloc', index: match.index });
    }
    while ((match = reallocRegex.exec(content)) !== null) {
        allocations.push({ var: match[1], type: 'realloc', index: match.index });
    }
    
    // Check if each allocation is followed by a NULL check
    allocations.forEach(alloc => {
        const checkPattern = new RegExp(`if\\s*\\(\\s*!?\\s*${alloc.var}\\s*[!=)=]`, 'g');
        checkPattern.lastIndex = alloc.index;
        
        const remainingContent = content.substring(alloc.index, alloc.index + 200);
        if (!checkPattern.test(remainingContent)) {
            results.missingNullChecks.push({
                file: filePath,
                variable: alloc.var,
                type: alloc.type
            });
            results.ruleViolations.push({
                rule: 13,
                file: filePath,
                message: `Missing NULL check for ${alloc.type} allocation: ${alloc.var}`
            });
        }
    });
}

function checkEmptyFiles(filePath, content) {
    // Check for empty or nearly empty files
    const trimmed = content.trim();
    const lines = trimmed.split('\n').filter(line => {
        const stripped = line.trim();
        return stripped && !stripped.startsWith('//') && !stripped.startsWith('/*') && !stripped.startsWith('*');
    });
    
    if (lines.length < 5) {
        results.emptyFiles.push({
            file: filePath,
            contentLines: lines.length
        });
    }
}

function findOrphanedFiles() {
    // Find files that are not referenced in CMakeLists.txt
    const cmakeFiles = getAllFiles(PROJECT_ROOT).filter(f => f.includes('CMakeLists.txt'));
    const allSourceFiles = getAllFiles(SRC_DIR);
    const referencedFiles = new Set();
    
    cmakeFiles.forEach(cmakeFile => {
        try {
            const content = fs.readFileSync(cmakeFile, 'utf-8');
            allSourceFiles.forEach(srcFile => {
                const basename = path.basename(srcFile);
                if (content.includes(basename)) {
                    referencedFiles.add(srcFile);
                }
            });
        } catch (e) {
            // Skip
        }
    });
    
    allSourceFiles.forEach(file => {
        if (!referencedFiles.has(file)) {
            results.orphanedFiles.push(file);
        }
    });
}

// Main analysis
console.log('XMD Codebase Analyzer');
console.log('====================\n');

console.log('Analyzing source files...');
const sourceFiles = getAllFiles(SRC_DIR);
const testFiles = getAllFiles(TEST_DIR);

sourceFiles.forEach(file => {
    try {
        const content = fs.readFileSync(file, 'utf-8');
        
        checkRule1(file);
        checkRule2(file, content);
        checkRule3(file, content);
        checkRule5(file);
        checkRule6(file, content);
        checkRule7(file, content);
        checkRule13(file, content);
        checkEmptyFiles(file, content);
    } catch (e) {
        console.error(`Error analyzing ${file}: ${e.message}`);
    }
});

// Process duplicated functions
const duplicates = [];
results.duplicatedFunctions.forEach((files, func) => {
    if (files.length > 1) {
        duplicates.push({
            function: func,
            files: files,
            count: files.length
        });
    }
});

// Find orphaned files
findOrphanedFiles();

// Generate report
console.log('\n=== ANALYSIS RESULTS ===\n');

console.log(`Total source files analyzed: ${sourceFiles.length}`);
console.log(`Total test files found: ${testFiles.length}`);

console.log(`\nRule Violations: ${results.ruleViolations.length}`);
results.ruleViolations.forEach(v => {
    console.log(`  Rule ${v.rule}: ${v.file}`);
    console.log(`    ${v.message}`);
});

console.log(`\nOversized Files (>200 lines): ${results.oversizedFiles.length}`);
results.oversizedFiles.forEach(f => {
    console.log(`  ${f.file}: ${f.lines} lines (+${f.excess})`);
});

console.log(`\nFiles with Multiple Functions: ${results.multipleFunctionsInFile.length}`);
results.multipleFunctionsInFile.forEach(f => {
    console.log(`  ${f.file}: ${f.count} functions`);
    console.log(`    Functions: ${f.functions.join(', ')}`);
});

console.log(`\nMismatched Function Names: ${results.mismatchedFunctions.length}`);
results.mismatchedFunctions.forEach(f => {
    console.log(`  ${f.file}`);
    console.log(`    Expected: ${f.expected}`);
    console.log(`    Found: ${f.actual.join(', ')}`);
});

console.log(`\nDuplicated Functions: ${duplicates.length}`);
duplicates.forEach(d => {
    console.log(`  Function '${d.function}' appears in ${d.count} files:`);
    d.files.forEach(f => console.log(`    - ${f}`));
});

console.log(`\nTODOs and FIXMEs: ${results.todosAndFixmes.length}`);
results.todosAndFixmes.forEach(t => {
    console.log(`  ${t.file}: ${t.type}`);
});

console.log(`\nFake/Stub Implementations: ${results.fakeImplementations.length}`);
results.fakeImplementations.forEach(f => {
    console.log(`  ${f.file}`);
});

console.log(`\nMissing NULL Checks: ${results.missingNullChecks.length}`);
results.missingNullChecks.forEach(m => {
    console.log(`  ${m.file}: ${m.type}(${m.variable})`);
});

console.log(`\nEmpty/Nearly Empty Files: ${results.emptyFiles.length}`);
results.emptyFiles.forEach(e => {
    console.log(`  ${e.file}: ${e.contentLines} content lines`);
});

console.log(`\nOrphaned Files (not in CMake): ${results.orphanedFiles.length}`);
results.orphanedFiles.forEach(f => {
    console.log(`  ${f}`);
});

// Summary
console.log('\n=== SUMMARY ===');
console.log(`Total issues found: ${
    results.ruleViolations.length +
    results.orphanedFiles.length +
    results.emptyFiles.length +
    results.todosAndFixmes.length +
    results.missingNullChecks.length
}`);

console.log('\nPriority fixes:');
console.log('1. Fix files with multiple functions (Rule 2)');
console.log('2. Fix oversized files (Rule 5)');
console.log('3. Fix mismatched function names (Rule 3)');
console.log('4. Add missing NULL checks (Rule 13)');
console.log('5. Replace stub implementations (Rule 7)');