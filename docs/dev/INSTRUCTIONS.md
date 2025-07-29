RULES:
1. IMPORTANT: One file per folder
2. IMPORTANT: One function per file
3. IMPORTANT: File / folder naming: grand_parent/parent/<snake_case>/<snake_case>.c (folder name = file name = function name)
4. Test driven: write the full test for the whole desired system first -> write logic code for system later
5. Maximum line of code per file: 200 lines
6. Reusable logic: no duplicated code
7. Real implementation: no mock, no "simplified", no "TODO", no tech debts
8. Write note before working: docs/notes/<YYYYMMDD-HHMM-topic>.md -> no more than 100 lines
9. No external dependencies
10. Always comment code in Doxygen compatible style with metas @brief, @struct, @param, @return etc...
11. Always update docs, and update tests, before implementation -> first steps of any plan.
12. Planning before any implementation: docs/plans/<YYYYMMDD-HHMM-plan>/<phase>/phase-instructions.md -> each plan has phases separated into each folder with short comprehensive doc.
13. Error handling: all functions must return meaningful error codes and handle edge cases
14. Memory management: always free allocated memory, check for null pointers
15. Use Cmake -> auto generate Makefile -> do not manually edit Makefile
16. All build artifacts in build/
17. All official tests must be in test/ (not sandbox, not trash test, not temporary test)
18. All temporary tests must be in sandbox/ (not official test, will be deleted without announcements)