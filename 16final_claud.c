#include <stdio.h>
#include <string.h>

#define MAX 200

typedef struct {
    int   khatianNo;
    char  ownerName[101];
    char  plotNo[21];
    float landArea;
    char  landType[21];
    int   lastTaxYear;
} LandRecord;

/* Ask the user for one record's details */
void promptRecordDetails(LandRecord *recordPtr) {
    printf("Khatian Number: ");
    scanf("%d", &recordPtr->khatianNo);

    printf("Owner Name: ");
    scanf(" %100[^\n]", recordPtr->ownerName);   /* reads spaces too */

    printf("Plot Number (Dag No.): ");
    scanf(" %20[^\n]", recordPtr->plotNo);

    printf("Land Area (Shotok): ");
    scanf("%f", &recordPtr->landArea);

    printf("Land Type: ");
    scanf(" %20[^\n]", recordPtr->landType);

    printf("Last Tax Payment Year: ");
    scanf("%d", &recordPtr->lastTaxYear);
}

/* Print one record */
void displayRecord(const LandRecord *recordPtr) {
    printf("-----------------------------\n");
    printf("Khatian No : %d\n", recordPtr->khatianNo);
    printf("Owner      : %s\n", recordPtr->ownerName);
    printf("Plot No    : %s\n", recordPtr->plotNo);
    printf("Area       : %.2f Shotok\n", recordPtr->landArea);
    printf("Land Type  : %s\n", recordPtr->landType);
    printf("Last Tax   : %d\n", recordPtr->lastTaxYear);
}

/* Find all records with the given Khatian number.
   Stores their addresses in results[] and returns how many were found. */
int findRecordsByKhatian(LandRecord registry[], int currentSize, int searchKhatian,
                         LandRecord *results[], int maxResults) {
    int count = 0;
    for (int i = 0; i < currentSize && count < maxResults; i++) {
        if (registry[i].khatianNo == searchKhatian) {
            results[count] = &registry[i];
            count++;
        }
    }
    if (count == 0) {
        printf("No record found.\n");
    } else {
        for (int i = 0; i < count; i++) {
            displayRecord(results[i]);
        }
    }
    return count;
}

/* Show records whose last tax year is before currentYear - 1 */
int getDefaulterList(LandRecord registry[], int currentSize, int currentYear) {
    int count = 0;
    for (int i = 0; i < currentSize; i++) {
        if (registry[i].lastTaxYear < currentYear - 1) {
            displayRecord(&registry[i]);
            count++;
        }
    }
    if (count == 0) {
        printf("No defaulters.\n");
    }
    return count;
}

/* Save to file, one record per line, fields separated by '|' */
void saveRegistryToFile(LandRecord registry[], int currentSize, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Cannot open file for writing.\n");
        return;
    }
    for (int i = 0; i < currentSize; i++) {
        fprintf(fp, "%d|%s|%s|%.2f|%s|%d\n",
                registry[i].khatianNo, registry[i].ownerName, registry[i].plotNo,
                registry[i].landArea, registry[i].landType, registry[i].lastTaxYear);
    }
    fclose(fp);
    printf("Saved %d record(s).\n", currentSize);
}

/* Load from file into registry[] starting at index 0. Returns records loaded. */
int loadRegistryFromFile(LandRecord registry[], int maxSize, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Cannot open file for reading.\n");
        return 0;
    }
    char line[400];
    int count = 0;
    while (count < maxSize && fgets(line, sizeof(line), fp) != NULL) {
        int n = sscanf(line, "%d|%100[^|]|%20[^|]|%f|%20[^|]|%d",
                       &registry[count].khatianNo, registry[count].ownerName,
                       registry[count].plotNo, &registry[count].landArea,
                       registry[count].landType, &registry[count].lastTaxYear);
        if (n == 6) {
            count++;          /* count only good lines */
        }
    }
    fclose(fp);
    printf("Loaded %d record(s).\n", count);
    return count;
}

// int main(void) {
//     LandRecord registry[MAX];
//     int currentSize = 0;
//     int choice;

//     do {
//         printf("\n1. Add New Land Record\n");
//         printf("2. Search Records by Khatian Number\n");
//         printf("3. Display All Records\n");
//         printf("4. Generate Tax Defaulter List\n");
//         printf("5. Save Registry to File\n");
//         printf("6. Load Registry from File\n");
//         printf("0. Exit\n");
//         printf("Choice: ");
//         scanf("%d", &choice);

//         if (choice == 1) {
//             if (currentSize >= MAX) {
//                 printf("Registry is full.\n");
//             } else {
//                 LandRecord temp;
//                 promptRecordDetails(&temp);

//                 /* uniqueness: same Khatian AND same Plot */
//                 int duplicate = 0;
//                 for (int i = 0; i < currentSize; i++) {
//                     if (registry[i].khatianNo == temp.khatianNo &&
//                         strcmp(registry[i].plotNo, temp.plotNo) == 0) {
//                         duplicate = 1;
//                     }
//                 }
//                 if (duplicate) {
//                     printf("Error: this Khatian and Plot already exist.\n");
//                 } else {
//                     registry[currentSize] = temp;
//                     currentSize++;
//                     printf("Record added.\n");
//                 }
//             }
//         }
//         else if (choice == 2) {
//             int key;
//             LandRecord *results[MAX];
//             printf("Khatian Number to search: ");
//             scanf("%d", &key);
//             findRecordsByKhatian(registry, currentSize, key, results, MAX);
//         }
//         else if (choice == 3) {
//             if (currentSize == 0) printf("Registry is empty.\n");
//             for (int i = 0; i < currentSize; i++) {
//                 displayRecord(&registry[i]);
//             }
//         }
//         else if (choice == 4) {
//             int year;
//             printf("Enter current year: ");
//             scanf("%d", &year);
//             getDefaulterList(registry, currentSize, year);
//         }
//         else if (choice == 5) {
//             saveRegistryToFile(registry, currentSize, "registry.txt");
//         }
//         else if (choice == 6) {
//             currentSize = loadRegistryFromFile(registry, MAX, "registry.txt");
//         }
//     } while (choice != 0);

//     return 0;
// }

int main(void) {
    LandRecord registry[MAX];
    int currentSize = 0;
    int choice;

    do {
        printf("\n1. Add New Land Record\n");
        printf("2. Search Records by Khatian Number\n");
        printf("3. Display All Records\n");
        printf("4. Generate Tax Defaulter List\n");
        printf("5. Save Registry to File\n");
        printf("6. Load Registry from File\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1: {   /* braces needed because we declare variables inside */
                if (currentSize >= MAX) {
                    printf("Registry is full.\n");
                    break;
                }

                LandRecord temp;
                promptRecordDetails(&temp);

                /* uniqueness: same Khatian AND same Plot */
                int duplicate = 0;
                for (int i = 0; i < currentSize; i++) {
                    if (registry[i].khatianNo == temp.khatianNo &&
                        strcmp(registry[i].plotNo, temp.plotNo) == 0) {
                        duplicate = 1;
                    }
                }

                if (duplicate) {
                    printf("Error: this Khatian and Plot already exist.\n");
                } else {
                    registry[currentSize] = temp;
                    currentSize++;
                    printf("Record added.\n");
                }
                break;
            }

            case 2: {
                int key;
                LandRecord *results[MAX];
                printf("Khatian Number to search: ");
                scanf("%d", &key);
                findRecordsByKhatian(registry, currentSize, key, results, MAX);
                break;
            }

            case 3:
                if (currentSize == 0) {
                    printf("Registry is empty.\n");
                }
                for (int i = 0; i < currentSize; i++) {
                    displayRecord(&registry[i]);
                }
                break;

            case 4: {
                int year;
                printf("Enter current year: ");
                scanf("%d", &year);
                getDefaulterList(registry, currentSize, year);
                break;
            }

            case 5:
                saveRegistryToFile(registry, currentSize, "registry.txt");
                break;

            case 6:
                currentSize = loadRegistryFromFile(registry, MAX, "registry.txt");
                break;

            case 0:
                printf("Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);

    return 0;
}
