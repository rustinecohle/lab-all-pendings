/*
 * Institute of Information Technology, University of Dhaka
 * BSSE - CSE 1101L : Structured Programming Lab
 * Final Exam Solution - "Pahartoli" Land Record Digitization System
 *
 * Compile:  gcc -Wall -o land_registry land_registry.c
 * Run:      ./land_registry
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------- Constants ---------- */
#define MAX_RECORDS      200
#define MAX_NAME_LEN     100
#define MAX_PLOT_LEN     20
#define MAX_TYPE_LEN     20
#define DELIM            "|"   /* delimiter used for the save file (avoids clashing with commas in names) */

/* ---------- Struct Definition ---------- */
typedef struct {
    int    khatianNumber;                  /* unique positive integer */
    char   ownerName[MAX_NAME_LEN + 1];    /* max 100 chars */
    char   plotNumber[MAX_PLOT_LEN + 1];   /* e.g. "101/Ka", max 20 chars */
    float  landArea;                       /* in Shotok */
    char   landType[MAX_TYPE_LEN + 1];     /* Krishi / Bashot / Dokan / Pukur */
    int    lastTaxPaymentYear;             /* e.g. 2023 */
} LandRecord;

/* ---------- Function Prototypes ---------- */
void   promptRecordDetails(LandRecord *recordPtr);
void   displayRecord(const LandRecord *recordPtr);
void   addNewRecord(LandRecord registry[], int *currentSize);
int    findRecordsByKhatian(LandRecord registry[], int currentSize, int searchKhatian,
                             LandRecord *results[], int maxResults);
void   getDefaulterList(LandRecord registry[], int currentSize, int currentYear);
void   saveRegistryToFile(LandRecord registry[], int currentSize, const char *filename);
int    loadRegistryFromFile(LandRecord registry[], int maxSize, const char *filename);

void   clearInputBuffer(void);
void   readLine(char *buffer, int size);
void   displayAllRecords(LandRecord registry[], int currentSize);

/* ---------- main ---------- */
int main(void) {
    LandRecord registry[MAX_RECORDS];
    int currentSize = 0;
    int choice;

    printf("=====================================================\n");
    printf("   Pahartoli Land Record Digitization System (Demo)\n");
    printf("=====================================================\n");

    do {
        printf("\n---------------- MAIN MENU ----------------\n");
        printf("1. Add New Land Record\n");
        printf("2. Search Records by Khatian Number\n");
        printf("3. Display All Records\n");
        printf("4. Generate Tax Defaulter List\n");
        printf("5. Save Registry to File\n");
        printf("6. Load Registry from File\n");
        printf("0. Exit\n");
        printf("---------------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                addNewRecord(registry, &currentSize);
                break;

            case 2: {
                int searchKhatian;
                LandRecord *results[MAX_RECORDS];
                int found;

                printf("Enter Khatian Number to search: ");
                if (scanf("%d", &searchKhatian) != 1) {
                    printf("Invalid Khatian Number.\n");
                    clearInputBuffer();
                    break;
                }
                clearInputBuffer();

                found = findRecordsByKhatian(registry, currentSize, searchKhatian,
                                              results, MAX_RECORDS);
                if (found == 0) {
                    printf("No record found with Khatian Number %d.\n", searchKhatian);
                } else {
                    printf("\nFound %d record(s) for Khatian Number %d:\n",
                           found, searchKhatian);
                    for (int i = 0; i < found; i++) {
                        displayRecord(results[i]);
                    }
                }
                break;
            }

            case 3:
                displayAllRecords(registry, currentSize);
                break;

            case 4: {
                int currentYear;
                printf("Enter current year: ");
                if (scanf("%d", &currentYear) != 1) {
                    printf("Invalid year.\n");
                    clearInputBuffer();
                    break;
                }
                clearInputBuffer();
                getDefaulterList(registry, currentSize, currentYear);
                break;
            }

            case 5: {
                char filename[256];
                printf("Enter filename to save to (e.g. registry.txt): ");
                readLine(filename, sizeof(filename));
                saveRegistryToFile(registry, currentSize, filename);
                break;
            }

            case 6: {
                char filename[256];
                int loaded;
                printf("Enter filename to load from (e.g. registry.txt): ");
                readLine(filename, sizeof(filename));
                loaded = loadRegistryFromFile(registry, MAX_RECORDS, filename);
                if (loaded >= 0) {
                    currentSize = loaded;
                    printf("Loaded %d record(s) from '%s'.\n", currentSize, filename);
                }
                break;
            }

            case 0:
                printf("Exiting program. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 0);

    return 0;
}

/* ---------- Utility: consume leftover newline after scanf("%d", ...) ---------- */
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* discard */
    }
}

/* ---------- Utility: safely read a full line into buffer (strips trailing \n) ---------- */
void readLine(char *buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
    } else {
        buffer[0] = '\0';
    }
}

/* ----------------------------------------------------------------------
 * promptRecordDetails
 * Prompts the user to enter details for one LandRecord and stores them
 * at the location pointed to by recordPtr.
 * ---------------------------------------------------------------------- */
void promptRecordDetails(LandRecord *recordPtr) {
    char temp[256];

    printf("Enter Khatian Number: ");
    while (scanf("%d", &recordPtr->khatianNumber) != 1 || recordPtr->khatianNumber <= 0) {
        printf("Invalid input. Khatian Number must be a positive integer. Try again: ");
        clearInputBuffer();
    }
    clearInputBuffer();

    printf("Enter Owner Name (max %d chars): ", MAX_NAME_LEN);
    readLine(temp, sizeof(temp));
    strncpy(recordPtr->ownerName, temp, MAX_NAME_LEN);
    recordPtr->ownerName[MAX_NAME_LEN] = '\0';

    printf("Enter Plot Number / Dag No. (e.g. 101/Ka, max %d chars): ", MAX_PLOT_LEN);
    readLine(temp, sizeof(temp));
    strncpy(recordPtr->plotNumber, temp, MAX_PLOT_LEN);
    recordPtr->plotNumber[MAX_PLOT_LEN] = '\0';

    printf("Enter Land Area (in Shotok): ");
    while (scanf("%f", &recordPtr->landArea) != 1 || recordPtr->landArea < 0) {
        printf("Invalid input. Enter a non-negative number: ");
        clearInputBuffer();
    }
    clearInputBuffer();

    printf("Enter Land Type (Krishi/Bashot/Dokan/Pukur, max %d chars): ", MAX_TYPE_LEN);
    readLine(temp, sizeof(temp));
    strncpy(recordPtr->landType, temp, MAX_TYPE_LEN);
    recordPtr->landType[MAX_TYPE_LEN] = '\0';

    printf("Enter Last Tax Payment Year (e.g. 2023): ");
    while (scanf("%d", &recordPtr->lastTaxPaymentYear) != 1) {
        printf("Invalid input. Enter a valid year: ");
        clearInputBuffer();
    }
    clearInputBuffer();
}

/* ----------------------------------------------------------------------
 * displayRecord
 * Neatly prints one land record's information.
 * ---------------------------------------------------------------------- */
void displayRecord(const LandRecord *recordPtr) {
    printf("-----------------------------------------------\n");
    printf("Khatian Number      : %d\n", recordPtr->khatianNumber);
    printf("Owner Name          : %s\n", recordPtr->ownerName);
    printf("Plot Number (Dag)   : %s\n", recordPtr->plotNumber);
    printf("Land Area (Shotok)  : %.2f\n", recordPtr->landArea);
    printf("Land Type           : %s\n", recordPtr->landType);
    printf("Last Tax Paid Year  : %d\n", recordPtr->lastTaxPaymentYear);
    printf("-----------------------------------------------\n");
}

/* ----------------------------------------------------------------------
 * displayAllRecords
 * Convenience helper for menu option 3.
 * ---------------------------------------------------------------------- */
void displayAllRecords(LandRecord registry[], int currentSize) {
    if (currentSize == 0) {
        printf("Registry is empty. No records to display.\n");
        return;
    }
    printf("\n============ ALL LAND RECORDS (%d) ============\n", currentSize);
    for (int i = 0; i < currentSize; i++) {
        displayRecord(&registry[i]);
    }
}

/* ----------------------------------------------------------------------
 * addNewRecord
 * Handles menu option 1: prompts for a record, checks the uniqueness
 * constraint (same Khatian Number + same Plot Number is a duplicate),
 * checks array bounds, then appends the record and updates currentSize.
 * ---------------------------------------------------------------------- */
void addNewRecord(LandRecord registry[], int *currentSize) {
    if (*currentSize >= MAX_RECORDS) {
        printf("Error: Registry is full (max %d records). Cannot add more records.\n",
               MAX_RECORDS);
        return;
    }

    LandRecord newRecord;
    promptRecordDetails(&newRecord);

    /* Uniqueness check: same Khatian Number AND same Plot Number = duplicate */
    for (int i = 0; i < *currentSize; i++) {
        if (registry[i].khatianNumber == newRecord.khatianNumber &&
            strcmp(registry[i].plotNumber, newRecord.plotNumber) == 0) {
            printf("Error: A record with Khatian Number %d and Plot Number '%s' "
                   "already exists. Record not added.\n",
                   newRecord.khatianNumber, newRecord.plotNumber);
            return;
        }
    }

    registry[*currentSize] = newRecord;
    (*currentSize)++;
    printf("Record added successfully. Total records: %d\n", *currentSize);
}

/* ----------------------------------------------------------------------
 * findRecordsByKhatian
 * Searches the registry array for all records matching searchKhatian.
 * Stores pointers to the matching records in results[] (up to maxResults),
 * displays them, and returns the number of matches found.
 * (A single Khatian can have multiple plots/entries.)
 * ---------------------------------------------------------------------- */
int findRecordsByKhatian(LandRecord registry[], int currentSize, int searchKhatian,
                          LandRecord *results[], int maxResults) {
    int count = 0;

    for (int i = 0; i < currentSize && count < maxResults; i++) {
        if (registry[i].khatianNumber == searchKhatian) {
            results[count] = &registry[i];
            count++;
        }
    }

    return count;
}

/* ----------------------------------------------------------------------
 * getDefaulterList
 * Iterates through the registry to find and display defaulters.
 * A record is a 'defaulter' if lastTaxPaymentYear < currentYear - 1
 * (i.e., tax wasn't paid last year or more recently).
 * ---------------------------------------------------------------------- */
void getDefaulterList(LandRecord registry[], int currentSize, int currentYear) {
    int defaulterCount = 0;

    printf("\n========= TAX DEFAULTER LIST (as of %d) =========\n", currentYear);
    for (int i = 0; i < currentSize; i++) {
        if (registry[i].lastTaxPaymentYear < currentYear - 1) {
            displayRecord(&registry[i]);
            defaulterCount++;
        }
    }

    if (defaulterCount == 0) {
        printf("No defaulters found. All land tax payments are up to date.\n");
    } else {
        printf("Total Defaulters: %d\n", defaulterCount);
    }
}

/* ----------------------------------------------------------------------
 * saveRegistryToFile
 * Writes all records from the registry array to the given file, one
 * record per line, fields separated by '|' (pipe) to avoid clashing
 * with commas or spaces that may appear inside names/types.
 * ---------------------------------------------------------------------- */
void saveRegistryToFile(LandRecord registry[], int currentSize, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: Could not open file '%s' for writing.\n", filename);
        return;
    }

    for (int i = 0; i < currentSize; i++) {
        fprintf(fp, "%d" DELIM "%s" DELIM "%s" DELIM "%.2f" DELIM "%s" DELIM "%d\n",
                registry[i].khatianNumber,
                registry[i].ownerName,
                registry[i].plotNumber,
                registry[i].landArea,
                registry[i].landType,
                registry[i].lastTaxPaymentYear);
    }

    fclose(fp);
    printf("Successfully saved %d record(s) to '%s'.\n", currentSize, filename);
}

/* ----------------------------------------------------------------------
 * loadRegistryFromFile
 * Reads records from the given file (in the format produced by
 * saveRegistryToFile) and populates the registry array starting from
 * index 0. Returns the number of records loaded, or -1 on error.
 * ---------------------------------------------------------------------- */
int loadRegistryFromFile(LandRecord registry[], int maxSize, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: Could not open file '%s' for reading.\n", filename);
        return -1;
    }

    char line[512];
    int count = 0;

    while (count < maxSize && fgets(line, sizeof(line), fp) != NULL) {
        /* strip trailing newline */
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        if (strlen(line) == 0) {
            continue; /* skip blank lines */
        }

        LandRecord rec;
        memset(&rec, 0, sizeof(rec));

        char *token;
        char *saveptr;

        token = strtok_r(line, DELIM, &saveptr);
        if (token == NULL) continue;
        rec.khatianNumber = atoi(token);

        token = strtok_r(NULL, DELIM, &saveptr);
        if (token == NULL) continue;
        strncpy(rec.ownerName, token, MAX_NAME_LEN);

        token = strtok_r(NULL, DELIM, &saveptr);
        if (token == NULL) continue;
        strncpy(rec.plotNumber, token, MAX_PLOT_LEN);

        token = strtok_r(NULL, DELIM, &saveptr);
        if (token == NULL) continue;
        rec.landArea = (float)atof(token);

        token = strtok_r(NULL, DELIM, &saveptr);
        if (token == NULL) continue;
        strncpy(rec.landType, token, MAX_TYPE_LEN);

        token = strtok_r(NULL, DELIM, &saveptr);
        if (token == NULL) continue;
        rec.lastTaxPaymentYear = atoi(token);

        registry[count] = rec;
        count++;
    }

    fclose(fp);
    return count;
}
