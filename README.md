# Simple Line Editor in C

## About the Project

This project is a simple command-line Line Editor developed using the C programming language.

The editor allows users to create and modify a text document one line at a time. All operations are performed through a menu in the terminal.

This project was developed for the Line Editor Coding Competition.

---

## Team Members

1. Vighnesh P Kanhirakandi
2. Ujjwal G D
3. Rohan R

---

## Features Implemented

### Core Features

- Insert a line at a specified line number.
- Delete a line from the document.
- Display all lines with their line numbers.
- Save the document to a text file.
- Load a text file into the editor.

### Bonus Features

- Search for a word or phrase.
- Find and replace text on a selected line.
- Undo the most recent Insert or Delete operation.

---

## Data Structure

The document is stored using a two-dimensional character array.

```c
#define MAX_LINES 100
#define MAX_LENGTH 256

char document[MAX_LINES][MAX_LENGTH];
int lineCount = 0;