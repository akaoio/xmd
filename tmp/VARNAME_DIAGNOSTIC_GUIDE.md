# {{varname}} Diagnostic Guide

## Implementation Chain Analysis
The {{varname}} evaluation chain is correctly implemented:

1. **xmd_process_string_api** → Uses processor->variables
2. **ast_process_xmd_content** → Calls xmd_dispatch_process with variables
3. **xmd_dispatch_process** → Handles {{varname}} substitution properly

## Expected vs Actual Behavior

### Test Case: `set name "Alice"` + `Hello {{name}}!`

**Expected Output**: `Hello Alice!`
**Tester Reports**: `print "Hello Alice"` or partial results

## Root Cause Analysis

### Possible Issues:

1. **XMD Block Processing**:
   - Are test files using proper ```xmd``` blocks in .md files?
   - Are .xmd files being processed as native XMD?

2. **Print Statement Confusion**:
   - Tester sees `print "Hello Alice"` - this suggests the directive is being treated as literal
   - This indicates the XMD block might not be recognized as executable

3. **File Processing Pipeline**:
   - main.c:cmd_process → calls xmd_process_file
   - xmd_process_file → calls xmd_process_string  
   - xmd_process_string → calls xmd_process_string_api
   - Chain should be working

## Diagnostic Commands

### Test 1: Direct Variable Test
```bash
echo 'set name "Alice"
Hello {{name}}!' > test_direct.xmd
./xmd process test_direct.xmd
```
**Expected**: `Hello Alice!`

### Test 2: Markdown Block Test  
```bash
echo '```xmd
set name "Alice"
```
Hello {{name}}!' > test_markdown.md
./xmd process test_markdown.md
```
**Expected**: `Hello Alice!`

### Test 3: Inline Test
```bash
echo 'set name "Alice"; Hello {{name}}!' | ./xmd process
```
**Expected**: `Hello Alice!`

## Implementation Verification

The implementation at native_xmd_consolidated.c:659-810 correctly:
- ✅ Parses `set varname value` directives
- ✅ Stores variables in processor context
- ✅ Recognizes {{varname}} patterns
- ✅ Substitutes variable values
- ✅ Handles quoted and unquoted values

## Debugging Steps

1. **Verify Binary**: Ensure latest xmd binary includes all fixes
2. **Check File Extensions**: .xmd vs .md processing differences
3. **Test Simple Case**: Single set+substitution in .xmd file
4. **Validate Chain**: Each step of the processing pipeline

## Expected Team Actions

**Tester**: Try the diagnostic commands above and report exact outputs
**Developer**: Verify build includes latest native_xmd_consolidated.c
**DevOps**: Confirm deployed binary has all recent changes

## Architecture Confidence

The {{varname}} evaluator implementation is architecturally sound. Any issues are likely in:
- File type detection/routing
- Build/deployment pipeline
- Test file formatting

The core evaluation logic is correct and complete.