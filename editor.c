#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINES 100
#define MAX_LENGTH 256

char document[MAX_LINES][MAX_LENGTH];
int lineCount = 0;

/* Undo variables */
int lastAction = 0;      /* 1 = insert, 2 = delete */
int lastPosition = -1;
char lastDeletedLine[MAX_LENGTH];

/* Function declarations */
void clearInputBuffer();
void insertLine();
void deleteLine();
void displayDocument();
void saveFile();
void loadFile();
void searchText();
void replaceText();
void undoLastAction();
void showHelp();


void clearInputBuffer()
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}


/* INSERT LINE */
void insertLine()
{
    int lineNumber;
    int i;
    char text[MAX_LENGTH];

    if (lineCount >= MAX_LINES)
    {
        printf("\nDocument is full!\n");
        return;
    }

    printf("\nEnter line number (1 to %d): ", lineCount + 1);

    if (scanf("%d", &lineNumber) != 1)
    {
        printf("Invalid input!\n");
        clearInputBuffer();
        return;
    }

    clearInputBuffer();

    if (lineNumber < 1 || lineNumber > lineCount + 1)
    {
        printf("Invalid line number!\n");
        return;
    }

    printf("Enter text: ");
    fgets(text, MAX_LENGTH, stdin);

    text[strcspn(text, "\n")] = '\0';

    /* Shift lines down */
    for (i = lineCount; i >= lineNumber; i--)
    {
        strcpy(document[i], document[i - 1]);
    }

    strcpy(document[lineNumber - 1], text);

    lineCount++;

    /* Save for undo */
    lastAction = 1;
    lastPosition = lineNumber - 1;

    printf("Line inserted successfully!\n");
}


/* DELETE LINE */
void deleteLine()
{
    int lineNumber;
    int i;

    if (lineCount == 0)
    {
        printf("\nDocument is empty. Nothing to delete!\n");
        return;
    }

    printf("\nEnter line number to delete (1 to %d): ", lineCount);

    if (scanf("%d", &lineNumber) != 1)
    {
        printf("Invalid input!\n");
        clearInputBuffer();
        return;
    }

    clearInputBuffer();

    if (lineNumber < 1 || lineNumber > lineCount)
    {
        printf("Invalid line number!\n");
        return;
    }

    /* Save deleted line for undo */
    strcpy(lastDeletedLine, document[lineNumber - 1]);
    lastAction = 2;
    lastPosition = lineNumber - 1;

    /* Shift lines up */
    for (i = lineNumber - 1; i < lineCount - 1; i++)
    {
        strcpy(document[i], document[i + 1]);
    }

    lineCount--;

    printf("Line deleted successfully!\n");
}


/* DISPLAY DOCUMENT */
void displayDocument()
{
    int i;

    if (lineCount == 0)
    {
        printf("\nDocument is empty.\n");
        return;
    }

    printf("\n========== DOCUMENT ==========\n");

    for (i = 0; i < lineCount; i++)
    {
        printf("%d. %s\n", i + 1, document[i]);
    }

    printf("==============================\n");
}


/* SAVE FILE */
void saveFile()
{
    FILE *file;
    char filename[100];
    int i;

    printf("\nEnter filename to save: ");
    scanf("%99s", filename);
    clearInputBuffer();

    file = fopen(filename, "w");

    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    for (i = 0; i < lineCount; i++)
    {
        fprintf(file, "%s\n", document[i]);
    }

    fclose(file);

    printf("Document saved successfully to %s!\n", filename);
}


/* LOAD FILE */
void loadFile()
{
    FILE *file;
    char filename[100];

    printf("\nEnter filename to load: ");
    scanf("%99s", filename);
    clearInputBuffer();

    file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("File not found or could not be opened!\n");
        return;
    }

    lineCount = 0;

    while (lineCount < MAX_LINES &&
           fgets(document[lineCount], MAX_LENGTH, file) != NULL)
    {
        document[lineCount][strcspn(document[lineCount], "\n")] = '\0';
        lineCount++;
    }

    fclose(file);

    lastAction = 0;

    printf("File loaded successfully!\n");
}


/* SEARCH TEXT */
void searchText()
{
    char search[MAX_LENGTH];
    int i;
    int found = 0;

    if (lineCount == 0)
    {
        printf("\nDocument is empty!\n");
        return;
    }

    printf("\nEnter word or phrase to search: ");
    fgets(search, MAX_LENGTH, stdin);

    search[strcspn(search, "\n")] = '\0';

    if (strlen(search) == 0)
    {
        printf("Search text cannot be empty!\n");
        return;
    }

    printf("\nFound in line(s): ");

    for (i = 0; i < lineCount; i++)
    {
        if (strstr(document[i], search) != NULL)
        {
            printf("%d ", i + 1);
            found = 1;
        }
    }

    if (!found)
    {
        printf("No matches found.");
    }

    printf("\n");
}


/* FIND AND REPLACE */
void replaceText()
{
    int lineNumber;
    char oldText[MAX_LENGTH];
    char newText[MAX_LENGTH];
    char temp[MAX_LENGTH * 2];
    char *position;
    int beforeLength;

    if (lineCount == 0)
    {
        printf("\nDocument is empty!\n");
        return;
    }

    printf("\nEnter line number: ");

    if (scanf("%d", &lineNumber) != 1)
    {
        printf("Invalid input!\n");
        clearInputBuffer();
        return;
    }

    clearInputBuffer();

    if (lineNumber < 1 || lineNumber > lineCount)
    {
        printf("Invalid line number!\n");
        return;
    }

    printf("Enter text to find: ");
    fgets(oldText, MAX_LENGTH, stdin);
    oldText[strcspn(oldText, "\n")] = '\0';

    printf("Enter replacement text: ");
    fgets(newText, MAX_LENGTH, stdin);
    newText[strcspn(newText, "\n")] = '\0';

    if (strlen(oldText) == 0)
    {
        printf("Find text cannot be empty!\n");
        return;
    }

    position = strstr(document[lineNumber - 1], oldText);

    if (position == NULL)
    {
        printf("Text not found in that line!\n");
        return;
    }

    beforeLength = position - document[lineNumber - 1];

    strncpy(temp, document[lineNumber - 1], beforeLength);
    temp[beforeLength] = '\0';

    strcat(temp, newText);
    strcat(temp, position + strlen(oldText));

    if (strlen(temp) >= MAX_LENGTH)
    {
        printf("Replacement makes line too long!\n");
        return;
    }

    strcpy(document[lineNumber - 1], temp);

    printf("Text replaced successfully!\n");
}


/* UNDO LAST ACTION */
void undoLastAction()
{
    int i;

    if (lastAction == 0)
    {
        printf("\nNothing to undo!\n");
        return;
    }

    /* Undo insert */
    if (lastAction == 1)
    {
        for (i = lastPosition; i < lineCount - 1; i++)
        {
            strcpy(document[i], document[i + 1]);
        }

        lineCount--;

        printf("Last insert undone successfully!\n");
    }

    /* Undo delete */
    else if (lastAction == 2)
    {
        if (lineCount >= MAX_LINES)
        {
            printf("Cannot undo. Document is full!\n");
            return;
        }

        for (i = lineCount; i > lastPosition; i--)
        {
            strcpy(document[i], document[i - 1]);
        }

        strcpy(document[lastPosition], lastDeletedLine);

        lineCount++;

        printf("Last delete undone successfully!\n");
    }

    lastAction = 0;
}


/* HELP */
void showHelp()
{
    printf("\n========== HELP ==========\n");

    printf("1. Insert Line\n");
    printf("   Insert text at a specific line number.\n\n");

    printf("2. Delete Line\n");
    printf("   Delete a line using its line number.\n\n");

    printf("3. Display Document\n");
    printf("   Display all lines with line numbers.\n\n");

    printf("4. Save File\n");
    printf("   Save the document to a text file.\n\n");

    printf("5. Load File\n");
    printf("   Load a text file into the editor.\n\n");

    printf("6. Search Text\n");
    printf("   Search for a word or phrase.\n\n");

    printf("7. Find and Replace\n");
    printf("   Replace text on a selected line.\n\n");

    printf("8. Undo Last Action\n");
    printf("   Undo the most recent insert or delete.\n\n");

    printf("9. Help\n");
    printf("   Display this help menu.\n\n");

    printf("0. Exit\n");

    printf("==========================\n");
}


/* MAIN FUNCTION */
int main()
{
    int choice;

    printf("=====================================\n");
    printf("       SIMPLE LINE EDITOR IN C\n");
    printf("=====================================\n");

    do
    {
        printf("\n----------- MENU -----------\n");
        printf("1. Insert Line\n");
        printf("2. Delete Line\n");
        printf("3. Display Document\n");
        printf("4. Save File\n");
        printf("5. Load File\n");
        printf("6. Search Text\n");
        printf("7. Find and Replace\n");
        printf("8. Undo Last Action\n");
        printf("9. Help\n");
        printf("0. Exit\n");

        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        switch (choice)
        {
            case 1:
                insertLine();
                break;

            case 2:
                deleteLine();
                break;

            case 3:
                displayDocument();
                break;

            case 4:
                saveFile();
                break;

            case 5:
                loadFile();
                break;

            case 6:
                searchText();
                break;

            case 7:
                replaceText();
                break;

            case 8:
                undoLastAction();
                break;

            case 9:
                showHelp();
                break;

            case 0:
                printf("\nThank you for using Simple Line Editor!\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 0);

    return 0;
}