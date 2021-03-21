#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRUCT_SIZE 50
#define MAX_FIRST_NAME_SIZE 20
#define MAX_LAST_NAME_SIZE 20
#define MAX_START_DATE_SIZE 20
#define MAX_END_DATE_SIZE 20
#define MAX_FILE_LINE_SIZE 256
#define MAX_FILE_NAME_SIZE 50
#define MAX_TEMP_FILE_NAME_SIZE 50

FILE *file;
FILE *tempFile;
char fileName[MAX_FILE_NAME_SIZE] = "gymRecords.txt";
char tempFileName[MAX_TEMP_FILE_NAME_SIZE] = "tempGymRecords.txt";

struct GymPass {
    int id;
    char firstName[MAX_FIRST_NAME_SIZE];
    char lastName[MAX_LAST_NAME_SIZE];
    char startDate[MAX_START_DATE_SIZE];
    char endDate[MAX_END_DATE_SIZE];
};

void createGymRecord();
void readAllGymRecords();
void updateGymRecord();
void deleteGymRecord();
void applicationMenu();

int main() {

    applicationMenu();
    return 0;
}

void createGymRecord() {

    struct GymPass gymPass;

    file = fopen(fileName, "a");

    printf("Enter id:");
    scanf("%d", &gymPass.id);

    printf("Enter first name:");
    scanf("%s", gymPass.firstName);

    printf("Enter last name:");
    scanf("%s", gymPass.lastName);

    printf("Enter starting date:");
    scanf("%s", gymPass.startDate);

    printf("Enter end date:");
    scanf("%s", gymPass.endDate);

    fprintf(file, "\n%d,%s,%s,%s,%s",
            gymPass.id,
            gymPass.firstName,
            gymPass.lastName,
            gymPass.startDate,
            gymPass.endDate);

    fclose(file);
    printf("\nRecord %d added successfully!\n", gymPass.id);
}

void readAllGymRecords() {

    char fileLine[MAX_FILE_LINE_SIZE];
    file = fopen(fileName, "r");

    if (!file) {
        printf("File %s not found!", fileName);
    }

    while (fgets(fileLine, MAX_STRUCT_SIZE, file)) {
        printf("%s", fileLine);
    }
    printf("\n");

    fclose(file);
    printf("\n");
}

void updateGymRecord() {

    struct GymPass gymPass[MAX_STRUCT_SIZE];
    char fileLine[MAX_FILE_LINE_SIZE];
    char firstName[MAX_FIRST_NAME_SIZE];
    char lastName[MAX_LAST_NAME_SIZE];
    char startDate[MAX_START_DATE_SIZE];
    char endDate[MAX_END_DATE_SIZE];
    char *token;
    int recordIndex;
    int countRecord = 0;
    int countLinesInFile = 0;

    file = fopen(fileName, "r");
    tempFile = fopen(tempFileName, "w");

    if (!file) {
        printf("File %s not found!", fileName);
    }

    while (fgets(fileLine, MAX_STRUCT_SIZE, file)) {
        countLinesInFile++;

        token = strtok(fileLine, ",");
        gymPass[countRecord].id = atoi(token);

        token = strtok(NULL, ",");
        strcpy(gymPass[countRecord].firstName, token);

        token = strtok(NULL, ",");
        strcpy(gymPass[countRecord].lastName, token);

        token = strtok(NULL, ",");
        strcpy(gymPass[countRecord].startDate, token);

        token = strtok(NULL, ",");
        strcpy(gymPass[countRecord].endDate, token);

        countRecord++;
    }

    printf("Enter the id of the gym record you wish to modify:");
    scanf("%d", &recordIndex);
    printf("\n");

    printf("Enter the first name:");
    scanf("%s", firstName);
    strcpy(gymPass[recordIndex - 1].firstName, firstName);

    printf("Enter the last name:");
    scanf("%s", lastName);
    strcpy(gymPass[recordIndex - 1].lastName, lastName);

    printf("Enter the start date (dd-mm-yyyy):");
    scanf("%s", startDate);
    strcpy(gymPass[recordIndex - 1].startDate, startDate);

    printf("Enter the end date (dd-mm-yyyy):");
    scanf("%s", endDate);
    strcpy(gymPass[recordIndex - 1].endDate, endDate);

    for (recordIndex = 0; recordIndex < countLinesInFile; recordIndex++) {
        fprintf(tempFile, "%d,%s,%s,%s,%s",
                gymPass[recordIndex].id,
                gymPass[recordIndex].firstName,
                gymPass[recordIndex].lastName,
                gymPass[recordIndex].startDate,
                gymPass[recordIndex].endDate);
    }

    fclose(file);
    fclose(tempFile);
    remove(fileName);
    rename(tempFileName, fileName);
    printf("\nRecord %d modified successfully!\n", gymPass[recordIndex - 1].id);
}

void deleteGymRecord() {
    file = fopen(fileName, "r");
    tempFile = fopen(tempFileName, "w");

    if (!file) {
        printf("File %s not found!", fileName);
    }

    struct GymPass gymPass[MAX_STRUCT_SIZE];
    char fileLine[MAX_FILE_LINE_SIZE];
    char *token;
    int indexToDelete;
    int countRecord = 0;
    int countLinesInFile = 0;

    while (fgets(fileLine, MAX_STRUCT_SIZE, file)) {
        countLinesInFile++;

        token = strtok(fileLine, ",");
        gymPass[countRecord].id = atoi(token);

        token = strtok(NULL, ",");
        strcpy(gymPass[countRecord].firstName, token);

        token = strtok(NULL, ",");
        strcpy(gymPass[countRecord].lastName, token);

        token = strtok(NULL, ",");
        strcpy(gymPass[countRecord].startDate, token);

        token = strtok(NULL, ",");
        strcpy(gymPass[countRecord].endDate, token);

        countRecord++;
    }

    printf("Enter the id of the gym record you wish to delete:");
    scanf("%d", &indexToDelete);
    printf("\n");

    for (int recordIndex = 0; recordIndex < countLinesInFile; recordIndex++) {
        if (recordIndex != indexToDelete - 1) {
            fprintf(tempFile, "%d,%s,%s,%s,%s",
                    gymPass[recordIndex].id,
                    gymPass[recordIndex].firstName,
                    gymPass[recordIndex].lastName,
                    gymPass[recordIndex].startDate,
                    gymPass[recordIndex].endDate);
        }
    }

    fclose(file);
    fclose(tempFile);
    remove(fileName);
    rename(tempFileName, fileName);
    printf("\nRecord %d deleted successfully!\n", gymPass[indexToDelete - 1].id);
}

void menu() {
    printf("**** WELCOME TO GYM RECORDS APP ****\n"
           "1-Add new gym record.\n"
           "2-Show all gym records.\n"
           "3-Modify gym record.\n"
           "4-Delete gym record.\n"
           "0-EXIT.\n");
}

void applicationMenu() {

    int flag = 1;
    int choice;

    menu();
    while (flag) {
        printf("Choose option:");
        scanf("%d", &choice);
        printf("\n");
        switch (choice) {
            case 1:
                printf("*** Add new gym record ***\n");
                createGymRecord();
                printf("\n");
                menu();
                break;
            case 2:
                printf("*** All gym records ***\n");
                readAllGymRecords();
                menu();
                break;
            case 3:
                printf("*** Modify gym record ***\n");
                updateGymRecord();
                printf("\n");
                menu();
                break;
            case 4:
                printf("*** Delete gym record ***\n");
                deleteGymRecord();
                printf("\n");
                menu();
                break;
            case 0:
                flag = 0;
                printf("*** APP CLOSED SUCCESSFULLY ***");
                break;
        }
    }
}
