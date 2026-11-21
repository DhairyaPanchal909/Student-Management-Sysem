

#include <stdio.h>      
#include <stdlib.h>    
#include <string.h>     


#define MAX_NAME     50     /* Maximum length of student name   */
#define MAX_COURSE   50     /* Maximum length of course name    */
#define NUM_SUBJECTS  5     /* Number of subjects per student   */
#define FILENAME     "students.dat"  /* Data file name          */


struct Student {
    int   id;                     
    char  name[MAX_NAME];          
    int   age;                   
    char  course[MAX_COURSE];     
    float marks[NUM_SUBJECTS];    
};


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


int main(void) {
    int choice;   
    printf("\n");
    printf("  =========================================\n");
    printf("     STUDENT MANAGEMENT SYSTEM\n");
    printf("     College Mini Project in C\n");
    printf("  =========================================\n");

   
    while (1) {
        displayMenu();  

        printf("  Enter your choice (1-7): ");

      
        if (scanf("%d", &choice) != 1) {
            printf("\n  [ERROR] Invalid input! Please enter a number.\n");
            clearInputBuffer(); 
            continue;           
        }
        clearInputBuffer(); 

      
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
                exit(0); 
            default:
                printf("\n  [ERROR] Invalid choice! Enter a number between 1 and 7.\n");
        }
    }

    return 0;  
}


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


void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;  /* Keep reading characters until newline or end-of-file */
}


    FILE *fp;         
    struct Student s; 

  
    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        return 0; 
    }

    
    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        if (s.id == id) {
            fclose(fp);
            return 1; 
        }
    }

    fclose(fp);
    return 0;  
}


void displayOneStudent(struct Student s) {
    int i; 

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


void addStudent(void) {
    FILE *fp;         
    struct Student s; 
    int i;             

    printf("\n  ===== ADD NEW STUDENT =====\n");

   
    printf("  Enter Student ID (positive number): ");
    if (scanf("%d", &s.id) != 1 || s.id <= 0) {
        printf("  [ERROR] Invalid ID! Must be a positive number.\n");
        clearInputBuffer();
        return;  
    }
    clearInputBuffer();

   
    if (isIdExists(s.id)) {
        printf("  [ERROR] Student ID %d already exists!\n", s.id);
        return;
    }

    
    printf("  Enter Student Name: ");
    fgets(s.name, MAX_NAME, stdin);
    s.name[strcspn(s.name, "\n")] = '\0'; 

    if (strlen(s.name) == 0) {
        printf("  [ERROR] Name cannot be empty!\n");
        return;
    }

    
    printf("  Enter Age (15-100): ");
    if (scanf("%d", &s.age) != 1 || s.age < 15 || s.age > 100) {
        printf("  [ERROR] Invalid age! Must be between 15 and 100.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

   
    printf("  Enter Course Name: ");
    fgets(s.course, MAX_COURSE, stdin);
    s.course[strcspn(s.course, "\n")] = '\0';

    if (strlen(s.course) == 0) {
        printf("  [ERROR] Course name cannot be empty!\n");
        return;
    }

   
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

   
    fp = fopen(FILENAME, "ab");  
    if (fp == NULL) {
        printf("  [ERROR] Unable to open file for saving!\n");
        return;
    }

    fwrite(&s, sizeof(struct Student), 1, fp);  
    fclose(fp);  

    printf("\n  [SUCCESS] Student record added successfully!\n");
}


void displayAllStudents(void) {
    FILE *fp;         
    struct Student s;  
    int count = 0;    

    printf("\n  ===== ALL STUDENT RECORDS =====\n");

  
    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("  No records found. Please add students first.\n");
        return;
    }

   
    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        displayOneStudent(s);
        count++; 
    }

    fclose(fp);

   
    if (count == 0) {
        printf("  No records found. Please add students first.\n");
    } else {
        printf("\n  Total students found: %d\n", count);
    }
}


void searchStudent(void) {
    FILE *fp;         
    struct Student s;  
    int searchId;      
    int found = 0;    

    printf("\n  ===== SEARCH STUDENT =====\n");
    printf("  Enter Student ID to search: ");

    if (scanf("%d", &searchId) != 1) {
        printf("  [ERROR] Invalid input!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

  
    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("  No records found. Please add students first.\n");
        return;
    }

  
    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        if (s.id == searchId) {
            printf("\n  [FOUND] Student record:\n");
            displayOneStudent(s);
            found = 1;
            break;  
        }
    }

    fclose(fp);

    if (!found) {
        printf("  [NOT FOUND] No student found with ID %d.\n", searchId);
    }
}


void updateStudent(void) {
    FILE *fp;          
    struct Student s;  
    int updateId;     
    int found = 0;    
    int i;            

    printf("\n  ===== UPDATE STUDENT =====\n");
    printf("  Enter Student ID to update: ");

    if (scanf("%d", &updateId) != 1) {
        printf("  [ERROR] Invalid input!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    
    fp = fopen(FILENAME, "r+b");
    if (fp == NULL) {
        printf("  No records found. Please add students first.\n");
        return;
    }

  
    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        if (s.id == updateId) {
            found = 1;

          
            printf("\n  Current record:\n");
            displayOneStudent(s);

           
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

           
            fseek(fp, -(long)sizeof(struct Student), SEEK_CUR);

            
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


void deleteStudent(void) {
    FILE *fp;        
    FILE *temp;       
    struct Student s;  
    int deleteId;      
    int found = 0;    

    printf("\n  ===== DELETE STUDENT =====\n");
    printf("  Enter Student ID to delete: ");

    if (scanf("%d", &deleteId) != 1) {
        printf("  [ERROR] Invalid input!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

   
    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("  No records found. Please add students first.\n");
        return;
    }

   
    temp = fopen("temp.dat", "wb");
    if (temp == NULL) {
        printf("  [ERROR] Unable to create temporary file!\n");
        fclose(fp);
        return;
    }

   
    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        if (s.id == deleteId) {
           
            found = 1;
            printf("\n  Deleting the following student:\n");
            displayOneStudent(s);
           
        } else {
           
            fwrite(&s, sizeof(struct Student), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if (found) {
       
        remove(FILENAME);             
        rename("temp.dat", FILENAME); 
        printf("\n  [SUCCESS] Student record deleted successfully!\n");
    } else {
        remove("temp.dat");  
        printf("  [NOT FOUND] No student found with ID %d.\n", deleteId);
    }
}



void calculateResult(void) {
    FILE *fp;         
    struct Student s;  
    int searchId;     
    int found = 0;     
    float total;       
    float percentage;  
    int i;            

    printf("\n  ===== CALCULATE RESULT =====\n");
    printf("  Enter Student ID: ");

    if (scanf("%d", &searchId) != 1) {
        printf("  [ERROR] Invalid input!\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    
    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("  No records found. Please add students first.\n");
        return;
    }

  
    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        if (s.id == searchId) {
            found = 1;

            
            displayOneStudent(s);

           
            total = 0;
            for (i = 0; i < NUM_SUBJECTS; i++) {
                total = total + s.marks[i];
            }

            
            percentage = total / (float)NUM_SUBJECTS;

           
            printf("\n  ========== RESULT ==========\n");
            printf("  Student Name  : %s\n", s.name);
            printf("  Total Marks   : %.2f / %d\n", total, NUM_SUBJECTS * 100);
            printf("  Percentage    : %.2f%%\n", percentage);

           
            if (percentage >= 40.0) {
                printf("  Status        : PASS\n");
            } else {
                printf("  Status        : FAIL\n");
            }

           
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
