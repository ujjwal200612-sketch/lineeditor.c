#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LENGTH 256

char document[MAX_LINES][MAX_LENGTH];
int lineCount = 0;

char undoDocument[MAX_LINES][MAX_LENGTH];
int undoLineCount = 0;
int undoAvailable = 0;

void saveState(void) {
    int i;
    undoLineCount = lineCount;
    for (i = 0; i < lineCount; i++) strcpy(undoDocument[i], document[i]);
    undoAvailable = 1;
}

void undoLastAction(void) {
    int i;
    if (!undoAvailable) {
        printf("Nothing to undo.\n");
        return;
    }
    lineCount = undoLineCount;
    for (i = 0; i < lineCount; i++) strcpy(document[i], undoDocument[i]);
    undoAvailable = 0;
    printf("Last insert/delete action undone.\n");
}

void insertLine(void) {
    int lineNumber, i;
    char text[MAX_LENGTH];

    if (lineCount >= MAX_LINES) {
        printf("Document is full.\n");
        return;
    }

    printf("Enter line number (1-%d): ", lineCount + 1);
    if (scanf("%d", &lineNumber) != 1) {
        printf("Invalid line number.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    if (lineNumber < 1 || lineNumber > lineCount + 1) {
        printf("Invalid line number.\n");
        return;
    }

    printf("Enter text: ");
    if (fgets(text, sizeof(text), stdin) == NULL) return;
    text[strcspn(text, "\n")] = '\0';

    saveState();
    for (i = lineCount; i >= lineNumber; i--) strcpy(document[i], document[i - 1]);
    strcpy(document[lineNumber - 1], text);
    lineCount++;
    printf("Line inserted successfully.\n");
}

void deleteLine(void) {
    int lineNumber, i;

    if (lineCount == 0) {
        printf("Document is empty.\n");
        return;
    }

    printf("Enter line number to delete (1-%d): ", lineCount);
    if (scanf("%d", &lineNumber) != 1) {
        printf("Invalid line number.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    if (lineNumber < 1 || lineNumber > lineCount) {
        printf("Invalid line number.\n");
        return;
    }

    saveState();
    for (i = lineNumber - 1; i < lineCount - 1; i++) strcpy(document[i], document[i + 1]);
    document[lineCount - 1][0] = '\0';
    lineCount--;
    printf("Line deleted successfully.\n");
}

void displayDocument(void) {
    int i;
    printf("\n========== DOCUMENT ==========\n");
    if (lineCount == 0) {
        printf("(empty)\n");
    } else {
        for (i = 0; i < lineCount; i++) printf("%d. %s\n", i + 1, document[i]);
    }
    printf("==============================\n");
}

void saveFile(void) {
    char filename[100];
    FILE *file;
    int i;

    printf("Enter filename to save: ");
    if (scanf("%99s", filename) != 1) return;
    while (getchar() != '\n');

    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Could not open file for writing.\n");
        return;
    }
    for (i = 0; i < lineCount; i++) fprintf(file, "%s\n", document[i]);
    fclose(file);
    printf("Document saved to %s.\n", filename);
}

void loadFile(void) {
    char filename[100];
    FILE *file;
    char buffer[MAX_LENGTH];

    printf("Enter filename to load: ");
    if (scanf("%99s", filename) != 1) return;
    while (getchar() != '\n');

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file for reading.\n");
        return;
    }

    lineCount = 0;
    while (lineCount < MAX_LINES && fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        strcpy(document[lineCount], buffer);
        lineCount++;
    }
    fclose(file);
    undoAvailable = 0;
    printf("Loaded %d line(s) from %s.\n", lineCount, filename);
}

void searchText(void) {
    char query[MAX_LENGTH];
    int i, found = 0;

    printf("Enter word or phrase to search: ");
    if (fgets(query, sizeof(query), stdin) == NULL) return;
    query[strcspn(query, "\n")] = '\0';

    if (query[0] == '\0') {
        printf("Search text cannot be empty.\n");
        return;
    }

    printf("Found in line(s):");
    for (i = 0; i < lineCount; i++) {
        if (strstr(document[i], query) != NULL) {
            printf(" %d", i + 1);
            found = 1;
        }
    }
    if (!found) printf(" none");
    printf("\n");
}

void findReplace(void) {
    int lineNumber;
    char find[MAX_LENGTH], replace[MAX_LENGTH];
    char *position;
    char result[MAX_LENGTH];
    size_t prefixLength, suffixLength, replacementLength;

    if (lineCount == 0) {
        printf("Document is empty.\n");
        return;
    }

    printf("Enter line number (1-%d): ", lineCount);
    if (scanf("%d", &lineNumber) != 1) {
        printf("Invalid line number.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    if (lineNumber < 1 || lineNumber > lineCount) {
        printf("Invalid line number.\n");
        return;
    }

    printf("Enter text to find: ");
    if (fgets(find, sizeof(find), stdin) == NULL) return;
    find[strcspn(find, "\n")] = '\0';
    if (find[0] == '\0') {
        printf("Text to find cannot be empty.\n");
        return;
    }

    printf("Enter replacement text: ");
    if (fgets(replace, sizeof(replace), stdin) == NULL) return;
    replace[strcspn(replace, "\n")] = '\0';

    position = strstr(document[lineNumber - 1], find);
    if (position == NULL) {
        printf("Text not found on line %d.\n", lineNumber);
        return;
    }

    prefixLength = (size_t)(position - document[lineNumber - 1]);
    suffixLength = strlen(position + strlen(find));
    replacementLength = strlen(replace);

    if (prefixLength + replacementLength + suffixLength >= MAX_LENGTH) {
        printf("Replacement would make the line too long.\n");
        return;
    }

    memcpy(result, document[lineNumber - 1], prefixLength);
    memcpy(result + prefixLength, replace, replacementLength);
    memcpy(result + prefixLength + replacementLength,
           position + strlen(find), suffixLength + 1);
    strcpy(document[lineNumber - 1], result);
    printf("Text replaced successfully.\n");
}

void showHelp(void) {
    printf("\n========== HELP ==========\n");
    printf("1 - Insert a line\n");
    printf("2 - Delete a line\n");
    printf("3 - Display document\n");
    printf("4 - Save document to a text file\n");
    printf("5 - Load a text file\n");
    printf("6 - Search for text\n");
    printf("7 - Find and replace text on a line\n");
    printf("8 - Undo last insert/delete\n");
    printf("9 - Show help\n");
    printf("0 - Exit\n");
    printf("==========================\n");
}

int main(void) {
    int choice;
    FILE *startupFile;
    char buffer[MAX_LENGTH];

    /* Automatically load document.txt when it exists. */
    startupFile = fopen("document.txt", "r");
    if (startupFile != NULL) {
        while (lineCount < MAX_LINES && fgets(buffer, sizeof(buffer), startupFile) != NULL) {
            buffer[strcspn(buffer, "\n")] = '\0';
            strcpy(document[lineCount], buffer);
            lineCount++;
        }
        fclose(startupFile);
        printf("Loaded document.txt on startup (%d line(s)).\n", lineCount);
    }

    do {
        printf("\n===== SIMPLE LINE EDITOR =====\n");
        printf("1. Insert line\n2. Delete line\n3. Display document\n");
        printf("4. Save file\n5. Load file\n6. Search text\n");
        printf("7. Find and replace\n8. Undo last action\n9. Help\n0. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid choice. Please enter a number from 0 to 9.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
            case 1: insertLine(); break;
            case 2: deleteLine(); break;
            case 3: displayDocument(); break;
            case 4: saveFile(); break;
            case 5: loadFile(); break;
            case 6: searchText(); break;
            case 7: findReplace(); break;
            case 8: undoLastAction(); break;
            case 9: showHelp(); break;
            case 0: printf("Exiting Line Editor.\n"); break;
            default: printf("Invalid choice. Please select 0-9.\n");
        }
    } while (choice != 0);

    return 0;
}
