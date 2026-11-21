/*
 * ==========================================================
 *          STUDENT MANAGEMENT SYSTEM
 *          College Mini Project in C
 * ==========================================================
 *  Description : A console-based application to manage
 *                student records with file storage.
 *  Language    : C
 *  Author      : Student Project
 * ==========================================================
 */

#include <stdio.h>      /* For input/output functions       */
#include <stdlib.h>     /* For exit() function               */
#include <string.h>     /* For string handling functions      */

/* ---- Constant Definitions ---- */
#define MAX_NAME     50     /* Maximum length of student name   */
#define MAX_COURSE   50     /* Maximum length of course name    */
#define NUM_SUBJECTS  5     /* Number of subjects per student   */
#define FILENAME     "students.dat"  /* Data file name          */

/* ============================================================
 *  STRUCTURE DEFINITION
 *  Stores all information about a single student.
 * ============================================================ */
struct Student {
    int   id;                      /* Unique student ID         */
    char  name[MAX_NAME];          /* Student full name         */
    int   age;                     /* Student age               */
    char  course[MAX_COURSE];      /* Course enrolled in        */
    float marks[NUM_SUBJECTS];     /* Marks in 5 subjects       */
};

/* ---- Function Prototypes (Declarations) ---- */
void displayMenu(void);
void addStudent(void);
void displayAllStudents(void);
void searchStudent(void);
void updateStudent(void);
void deleteStudent(void);
void calculateResult(void);
int  isIdExists(int id);
void displayOneStudent(struct Student s);
void clearInputBuffer(void);

/* ============================================================
 *  MAIN FUNCTION
 *  Entry point of the program. Shows the menu and calls
 *  the appropriate function based on user choice.
 * ============================================================ */
int main(void) {
    int choice;   /* Variable to store user menu choice */

    /* Display welcome banner once at the start */
    printf("\n");
    printf("  =========================================\n");
    printf("     STUDENT MANAGEMENT SYSTEM\n");
    printf("     College Mini Project in C\n");
    printf("  =========================================\n");

    /* Infinite loop to keep showing the menu until user exits */
    while (1) {
        displayMenu();  /* Show the menu options */

        printf("  Enter your choice (1-7): ");

        /* Read user choice and validate it is a number */
        if (scanf("%d", &choice) != 1) {
            printf("\n  [ERROR] Invalid input! Please enter a number.\n");
            clearInputBuffer();  /* Clear any leftover characters */
            continue;            /* Go back to the start of the loop */
        }
        clearInputBuffer();  /* Clear the newline left by scanf */

        /* Use switch to call the correct function */
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayAllStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                calculateResult();
                break;
            case 7:
                printf("\n  Thank you for using Student Management System!\n");
                printf("  Exiting... Goodbye!\n\n");
                exit(0);  /* Terminate the program safely */
            default:
                printf("\n  [ERROR] Invalid choice! Enter a number between 1 and 7.\n");
        }
    }

    return 0;  /* This line is never reached but is good practice */
}

/* ============================================================
 *  FUNCTION: displayMenu
 *  Purpose : Prints the main menu options on the screen.
 * ============================================================ */
void displayMenu(void) {
    printf("\n  -----------------------------------------\n");
    printf("               MAIN MENU\n");
    printf("  -----------------------------------------\n");
    printf("   1. Add Student\n");
    printf("   2. Display All Students\n");
    printf("   3. Search Student\n");
    printf("   4. Update Student\n");
    printf("   5. Delete Student\n");
    printf("   6. Calculate Result\n");
    printf("   7. Exit\n");
    printf("  -----------------------------------------\n");
}

/* ============================================================
 *  FUNCTION: clearInputBuffer
 *  Purpose : Removes any extra characters left in the input
 *            buffer after scanf. This prevents input errors
 *            when reading strings after numbers.
 * ============================================================ */
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;  /* Keep reading characters until newline or end-of-file */
}

/* ============================================================
 *  FUNCTION: isIdExists
 *  Purpose : Checks if a student with the given ID already
 *            exists in the data file.
 *  Returns : 1 if ID exists, 0 if it does not.
 * ============================================================ */
int isIdExists(int id) {
    FILE *fp;          /* File pointer */
    struct Student s;  /* Temporary student variable */

    /* Open the file in read-binary mode */
    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        return 0;  /* File does not exist, so ID cannot exist */
    }

    /* Read each student record and check the ID */
    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        if (s.id == id) {
            fclose(fp);
            return 1;  /* ID found in file */
        }
    }

    fclose(fp);
    return 0;  /* ID not found */
}

/* ============================================================
 *  FUNCTION: displayOneStudent
 *  Purpose : Prints all details of a single student record
 *            in a formatted way.
 * ============================================================ */
void displayOneStudent(struct Student s) {
    int i;  /* Loop counter */

    printf("\n  +-------------------------------+\n");
    printf("  | Student ID   : %-14d |\n", s.id);
    printf("  | Name         : %-14s |\n", s.name);
    printf("  | Age          : %-14d |\n", s.age);
    printf("  | Course       : %-14s |\n", s.course);
    printf("  | Marks:                        |\n");
    for (i = 0; i < NUM_SUBJECTS; i++) {
        printf("  |   Subject %d  : %-14.2f |\n", i + 1, s.marks[i]);
    }
    printf("  +-------------------------------+\n");
}

/* ============================================================
 *  FUNCTION: addStudent
 *  Purpose : Takes student details from the user and saves
 *            the record to the data file.
 * ============================================================ */
void addStudent(void) {
    FILE *fp;          /* File pointer for saving data */
    struct Student s;  /* Variable to store student details */
    int i;             /* Loop counter for marks */

    printf("\n  ===== ADD NEW STUDENT =====\n");

    /* --- Step 1: Get Student ID --- */
    printf("  Enter Student ID (positive number): ");
    if (scanf("%d", &s.id) != 1 || s.id <= 0) {
        printf("  [ERROR] Invalid ID! Must be a positive number.\n");
        clearInputBuffer();
        return;  /* Go back to the main menu */
    }
    clearInputBuffer();

    /* --- Step 2: Check if ID already exists --- */
    if (isIdExists(s.id)) {
        printf("  [ERROR] Student ID %d already exists!\n", s.id);
        return;
    }

    /* --- Step 3: Get Student Name --- */
    printf("  Enter Student Name: ");
    fgets(s.name, MAX_NAME, stdin);
    s.name[strcspn(s.name, "\n")] = '\0';  /* Remove trailing newline */

    if (strlen(s.name) == 0) {
        printf("  [ERROR] Name cannot be empty!\n");
        return;
    }

    /* --- Step 4: Get Age --- */
    printf("  Enter Age (15-100): ");
    if (scanf("%d", &s.age) != 1 || s.age < 15 || s.age > 100) {
        printf("  [ERROR] Invalid age! Must be between 15 and 100.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    /* --- Step 5: Get Course Name --- */
    printf("  Enter Course Name: ");
    fgets(s.course, MAX_COURSE, stdin);
    s.course[strcspn(s.course, "\n")] = '\0';

    if (strlen(s.course) == 0) {
        printf("  [ERROR] Course name cannot be empty!\n");
        return;
    }

    /* --- Step 6: Get Marks for 5 Subjects --- */
    printf("  Enter marks for %d subjects (0 to 100 each):\n", NUM_SUBJECTS);
    for (i = 0; i < NUM_SUBJECTS; i++) {
        printf("    Subject %d: ", i + 1);
        if (scanf("%f", &s.marks[i]) != 1 || s.marks[i] < 0 || s.marks[i] > 100) {
            printf("  [ERROR] Invalid marks! Must be between 0 and 100.\n");
            clearInputBuffer();
            return;
        }
    }
    clearInputBuffer();

    /* --- Step 7: Save Record to File --- */
    fp = fopen(FILENAME, "ab");  /* Open file in append-binary mode */
    if (fp == NULL) {
        printf("  [ERROR] Unable to open file for saving!\n");
        return;
    }

    fwrite(&s, sizeof(struct Student), 1, fp);  /* Write the struct to file */
    fclose(fp);  /* Close the file */

    printf("\n  [SUCCESS] Student record added successfully!\n");
}

/* ============================================================
 *  FUNCTION: displayAllStudents
 *  Purpose : Reads all student records from the file and
 *            displays them on the screen.
 * ============================================================ */
void displayAllStudents(void) {
    FILE *fp;          /* File pointer */
    struct Student s;  /* Temporary variable for reading */
    int count = 0;     /* Counter for total records */

    printf("\n  ===== ALL STUDENT RECORDS =====\n");

    /* Open the file in read-binary mode */
    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("  No records found. Please add students first.\n");
        return;
    }

    /* Read and display each record one by one */
    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        displayOneStudent(s);
        count++;  /* Increment the counter */
    }

    fclose(fp);

    /* Show total count or a message if file was empty */
    if (count == 0) {
        printf("  No records found. Please add students first.\n");
    } else {
        printf("\n  Total students found: %d\n", count);
    }
}

/* ============================================================
 *  FUNCTION: searchStudent
 *  Purpose : Searches for a student by their ID and displays
 *            their complete information if found.
 * ============================================================ */
void searchStudent(void) {
    FILE *fp;          /* File pointer */
    struct Student s;  /* Temporary variable */
    int searchId;      /* ID to search for */
    int found = 0;     /* Flag: 0 = not found, 1 = found */

    printf("\n  ===== SEARCH STUDENT =====\n");
    printf("  Enter Student ID to search: ");

    if (scanf("%d", &searchId) != 1) {
        printf("  [ERROR] Invalid input!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    /* Open the file for reading */
    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("  No records found. Please add students first.\n");
        return;
    }

    /* Read each record and compare the ID */
    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        if (s.id == searchId) {
            printf("\n  [FOUND] Student record:\n");
            displayOneStudent(s);
            found = 1;
            break;  /* Stop searching after finding the student */
        }
    }

    fclose(fp);

    if (!found) {
        printf("  [NOT FOUND] No student found with ID %d.\n", searchId);
    }
}

/* ============================================================
 *  FUNCTION: updateStudent
 *  Purpose : Searches for a student by ID, displays the
 *            current record, takes new details from the user,
 *            and updates the record in the file.
 * ============================================================ */
void updateStudent(void) {
    FILE *fp;          /* File pointer */
    struct Student s;  /* Temporary variable */
    int updateId;      /* ID of student to update */
    int found = 0;     /* Flag */
    int i;             /* Loop counter */

    printf("\n  ===== UPDATE STUDENT =====\n");
    printf("  Enter Student ID to update: ");

    if (scanf("%d", &updateId) != 1) {
        printf("  [ERROR] Invalid input!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    /* Open file in read+write binary mode */
    fp = fopen(FILENAME, "r+b");
    if (fp == NULL) {
        printf("  No records found. Please add students first.\n");
        return;
    }

    /* Search for the student */
    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        if (s.id == updateId) {
            found = 1;

            /* Show current details */
            printf("\n  Current record:\n");
            displayOneStudent(s);

            /* Get new details from user */
            printf("\n  Enter new details:\n");

            printf("  Enter New Name: ");
            fgets(s.name, MAX_NAME, stdin);
            s.name[strcspn(s.name, "\n")] = '\0';

            if (strlen(s.name) == 0) {
                printf("  [ERROR] Name cannot be empty!\n");
                fclose(fp);
                return;
            }

            printf("  Enter New Age (15-100): ");
            if (scanf("%d", &s.age) != 1 || s.age < 15 || s.age > 100) {
                printf("  [ERROR] Invalid age!\n");
                clearInputBuffer();
                fclose(fp);
                return;
            }
            clearInputBuffer();

            printf("  Enter New Course: ");
            fgets(s.course, MAX_COURSE, stdin);
            s.course[strcspn(s.course, "\n")] = '\0';

            if (strlen(s.course) == 0) {
                printf("  [ERROR] Course name cannot be empty!\n");
                fclose(fp);
                return;
            }

            printf("  Enter new marks for %d subjects:\n", NUM_SUBJECTS);
            for (i = 0; i < NUM_SUBJECTS; i++) {
                printf("    Subject %d: ", i + 1);
                if (scanf("%f", &s.marks[i]) != 1 || s.marks[i] < 0 || s.marks[i] > 100) {
                    printf("  [ERROR] Invalid marks!\n");
                    clearInputBuffer();
                    fclose(fp);
                    return;
                }
            }
            clearInputBuffer();

            /* Move the file pointer back by one record size */
            fseek(fp, -(long)sizeof(struct Student), SEEK_CUR);

            /* Write the updated record at the same position */
            fwrite(&s, sizeof(struct Student), 1, fp);

            printf("\n  [SUCCESS] Student record updated successfully!\n");
            break;
        }
    }

    fclose(fp);

    if (!found) {
        printf("  [NOT FOUND] No student found with ID %d.\n", updateId);
    }
}

/* ============================================================
 *  FUNCTION: deleteStudent
 *  Purpose : Deletes a student record by copying all other
 *            records to a temporary file, then replacing
 *            the original file.
 * ============================================================ */
void deleteStudent(void) {
    FILE *fp;          /* File pointer for original file */
    FILE *temp;        /* File pointer for temporary file */
    struct Student s;  /* Temporary variable */
    int deleteId;      /* ID of student to delete */
    int found = 0;     /* Flag */

    printf("\n  ===== DELETE STUDENT =====\n");
    printf("  Enter Student ID to delete: ");

    if (scanf("%d", &deleteId) != 1) {
        printf("  [ERROR] Invalid input!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    /* Open the original file for reading */
    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("  No records found. Please add students first.\n");
        return;
    }

    /* Create a temporary file for writing */
    temp = fopen("temp.dat", "wb");
    if (temp == NULL) {
        printf("  [ERROR] Unable to create temporary file!\n");
        fclose(fp);
        return;
    }

    /* Read each record from the original file */
    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        if (s.id == deleteId) {
            /* Found the student to delete */
            found = 1;
            printf("\n  Deleting the following student:\n");
            displayOneStudent(s);
            /* Do NOT write this record to the temp file */
        } else {
            /* Write all other records to the temp file */
            fwrite(&s, sizeof(struct Student), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        /* Replace original file with temp file */
        remove(FILENAME);             /* Delete the original file */
        rename("temp.dat", FILENAME); /* Rename temp to original */
        printf("\n  [SUCCESS] Student record deleted successfully!\n");
    } else {
        remove("temp.dat");  /* Delete the temp file if not needed */
        printf("  [NOT FOUND] No student found with ID %d.\n", deleteId);
    }
}

/* ============================================================
 *  FUNCTION: calculateResult
 *  Purpose : Calculates total marks, percentage, pass/fail
 *            status, and grade for a specific student.
 * ============================================================ */
void calculateResult(void) {
    FILE *fp;          /* File pointer */
    struct Student s;  /* Temporary variable */
    int searchId;      /* ID of student */
    int found = 0;     /* Flag */
    float total;       /* Total of all marks */
    float percentage;  /* Percentage obtained */
    int i;             /* Loop counter */

    printf("\n  ===== CALCULATE RESULT =====\n");
    printf("  Enter Student ID: ");

    if (scanf("%d", &searchId) != 1) {
        printf("  [ERROR] Invalid input!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    /* Open the file for reading */
    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("  No records found. Please add students first.\n");
        return;
    }

    /* Search for the student */
    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        if (s.id == searchId) {
            found = 1;

            /* Display student details */
            displayOneStudent(s);

            /* Calculate total marks */
            total = 0;
            for (i = 0; i < NUM_SUBJECTS; i++) {
                total = total + s.marks[i];
            }

            /* Calculate percentage */
            percentage = total / (float)NUM_SUBJECTS;

            /* Display the result */
            printf("\n  ========== RESULT ==========\n");
            printf("  Student Name  : %s\n", s.name);
            printf("  Total Marks   : %.2f / %d\n", total, NUM_SUBJECTS * 100);
            printf("  Percentage    : %.2f%%\n", percentage);

            /* Check pass or fail (40% passing marks) */
            if (percentage >= 40.0) {
                printf("  Status        : PASS\n");
            } else {
                printf("  Status        : FAIL\n");
            }

            /* Assign grade based on percentage */
            if (percentage >= 90.0) {
                printf("  Grade         : A+ (Outstanding)\n");
            } else if (percentage >= 80.0) {
                printf("  Grade         : A  (Excellent)\n");
            } else if (percentage >= 70.0) {
                printf("  Grade         : B  (Very Good)\n");
            } else if (percentage >= 60.0) {
                printf("  Grade         : C  (Good)\n");
            } else if (percentage >= 40.0) {
                printf("  Grade         : D  (Pass)\n");
            } else {
                printf("  Grade         : F  (Fail)\n");
            }

            printf("  ==============================\n");
            break;
        }
    }

    fclose(fp);

    if (!found) {
        printf("  [NOT FOUND] No student found with ID %d.\n", searchId);
    }
}

/* ============================================================
 *  END OF PROGRAM
 * ============================================================ */
