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
```

### Why this structure?

A 2D character array gives direct access to each line, keeps the implementation simple for a small editor, and makes insertion/deletion straightforward by shifting complete strings.

---

## How to Compile

Using GCC:

```bash
gcc lineeditor.c -o lineeditor
```

For stricter warnings:

```bash
gcc -std=c11 -Wall -Wextra -pedantic lineeditor.c -o lineeditor
```

## How to Run

Linux/macOS:

```bash
./lineeditor
```

Windows:

```text
lineeditor.exe
```

If a file named `document.txt` exists in the same folder, the editor automatically loads it when the program starts.

---

## Menu Commands

| Option | Command | Purpose |
|---|---|---|
| 1 | Insert line | Insert text at a line number |
| 2 | Delete line | Delete a selected line |
| 3 | Display document | Show all current lines |
| 4 | Save file | Save the document to a .txt file |
| 5 | Load file | Load a .txt file |
| 6 | Search text | Find line number(s) containing a word/phrase |
| 7 | Find and replace | Replace text on a selected line |
| 8 | Undo | Undo the latest insert/delete |
| 9 | Help | Show command help |
| 0 | Exit | Close the editor |

---

## Edge Cases and Error Handling

The program handles:

- Inserting into an empty document.
- Inserting at the beginning, middle, or end.
- Deleting the only line.
- Deleting from an empty document.
- Invalid line numbers.
- Invalid menu input.
- Missing files during load.
- Empty search/find text.
- Replacement text that would exceed the maximum line length.
- A full document with 100 lines.

---

## Project Files

- `lineeditor.c` — complete C implementation.
- `HELP.md` — command-by-command usage guide.
- `TESTING.md` — test checklist for core and bonus features.
- `paper-design.jpg` — cropped photo/scan of the hand-written paper design and core logic.

---

## Paper Design

The paper-design image is included in the repository as `paper-design.jpg` and contains the hand-written data structure, command list, flowcharts/core logic, program/function design, example, and team roles.

---

## Team Collaboration

The project was designed as a team activity with shared planning, implementation, testing, and documentation. The Git history records the project development steps.

---

## Activity 7

**Portfolio Building — Studio Course | 3rd Semester | Coding Competition**

**Activity:** Build a Simple Line Editor in C
