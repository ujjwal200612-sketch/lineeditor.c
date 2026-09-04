# HELP - Simple Line Editor

This file explains how to use each command in the Simple Line Editor.

---

## 1. Insert Line

### What it does
Adds a new line of text at a selected line number.

### How to use
1. Select option `1`.
2. Enter the line number.
3. Enter the text.

### Example

Enter line number:

1

Enter text:

Hello World

The new line will be inserted into the document.

---

## 2. Delete Line

### What it does
Removes a line from the document.

### How to use
1. Select option `2`.
2. Enter the line number you want to delete.

### Example

Document:

1. Hello
2. World

Delete line:

2

Result:

1. Hello

---

## 3. Display Document

### What it does
Shows all lines currently stored in the document along with their line numbers.

### How to use

Select option:

3

### Example Output

========== DOCUMENT ==========

1. Hello
2. Welcome
3. World

==============================

---

## 4. Save File

### What it does
Saves the current document into a text file.

### How to use
1. Select option `4`.
2. Enter a filename.

### Example

Enter filename to save:

notes.txt

The document will be saved in `notes.txt`.

---

## 5. Load File

### What it does
Loads a text file into the editor.

### How to use
1. Select option `5`.
2. Enter the name of the file.

### Example

Enter filename to load:

notes.txt

The contents of the file will be loaded into the editor.

---

## 6. Search Text

### What it does
Searches for a word or phrase in the document.

The program displays the line number(s) where the text is found.

### How to use
1. Select option `6`.
2. Enter the word or phrase to search.

### Example

Search text:

Hello

Output:

Found in line(s): 1 4

---

## 7. Find and Replace

### What it does
Finds text in a selected line and replaces it with new text.

### How to use
1. Select option `7`.
2. Enter the line number.
3. Enter the text to find.
4. Enter the replacement text.

### Example

Original line:

I like Java

Find:

Java

Replace with:

C

Result:

I like C

---

## 8. Undo Last Action

### What it does
Undoes the most recent Insert or Delete operation.

### How to use

Select option:

8

### Example

After deleting a line, select option `8` to restore the deleted line.

---

## 9. Help

### What it does
Displays the list of available commands.

### How to use

Select option:

9

---

## 0. Exit

### What it does
Closes the Simple Line Editor.

### How to use

Select option:

0

---

## Important Notes

- Maximum number of lines: 100
- Maximum characters per line: 256
- Undo works only for the latest Insert or Delete operation.
- Enter valid line numbers when inserting, deleting, or replacing text.