# Testing Notes

The editor was compiled with GCC using:
gcc -std=c11 -Wall -Wextra -pedantic lineeditor.c -o lineeditor

## Core feature tests
1. Insert: test an empty document and insertion at beginning, middle, and end.
2. Delete: test deleting the only line and deleting first, middle, and last lines; also test an invalid line number.
3. Display: test an empty document and a multi-line document; verify line numbers.
4. Save / Load: save multiple lines, load the saved file, try a missing file, and verify automatic startup loading from document.txt.

## Bonus feature tests
5. Search: search for text on multiple lines, text that does not exist, and empty search text.
6. Find and Replace: replace existing text, try missing text, and try an invalid line number.
7. Undo: insert then undo, delete then undo, and undo when no undo state exists.
8. Invalid menu input: enter a non-numeric choice and a number outside 0-9.