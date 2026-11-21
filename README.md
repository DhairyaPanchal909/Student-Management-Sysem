# 🎓 Student Management System in C

A simple and beginner-friendly **Student Management System** developed using the C programming language as a college mini project.

This is a console-based application that helps manage student records. Users can add, display, search, update, and delete student information. It also calculates student results, percentages, and grades.

## 📌 Project Overview

The Student Management System is designed to make student record management simple and organized.

It uses basic C programming concepts such as structures, functions, loops, conditional statements, arrays, and file handling.

## ✨ Features

- **Add Student:** Add new student records with ID, name, age, course, and subject marks.
- **Display Students:** Display all registered student records.
- **Search Student:** Find a student using their unique ID.
- **Update Student:** Modify existing student information.
- **Delete Student:** Remove a student record using their ID.
- **Calculate Result:** Calculate total marks, percentage, pass/fail status, and grade.
- **Permanent Storage:** Save student records using file handling.
- **Input Validation:** Validate basic student information and marks.
- **Simple Menu:** Easy-to-use console interface.

## 🛠️ Technologies Used

- Programming Language: C
- Compiler: GCC
- Code Editor: Visual Studio Code
- Application Type: Console-Based
- Storage: File Handling

## 📚 C Programming Concepts Used

- Variables and Data Types
- Structures
- Arrays
- Functions
- Loops
- If-Else Statements
- Switch Statements
- String Handling
- File Handling
- Input Validation

## 📂 Project Structure

```text
Student-Management-System-C/
│
├── main.c
├── students.dat
└── README.md
```

**Note:** `students.dat` is automatically created when student records are saved for the first time.

## ⚙️ Installation and Execution

### Step 1: Clone the Repository

Open your terminal and execute:

```bash
git clone https://github.com/YOUR-USERNAME/Student-Management-System-C.git
```

### Step 2: Open the Project Folder

```bash
cd Student-Management-System-C
```

### Step 3: Compile the Program

Make sure GCC is installed on your system.

```bash
gcc main.c -o student
```

### Step 4: Run the Program

**For Windows:**

```bash
student.exe
```

**For Linux / macOS:**

```bash
./student
```

## 🖥️ Application Menu

When you run the program, the following menu appears:

```text
=========================================
       STUDENT MANAGEMENT SYSTEM
       College Mini Project in C
=========================================

-----------------------------------------
              MAIN MENU
-----------------------------------------
  1. Add Student
  2. Display All Students
  3. Search Student
  4. Update Student
  5. Delete Student
  6. Calculate Result
  7. Exit
-----------------------------------------

Enter your choice (1-7):
```

## 📊 Student Information

The application stores the following information:

| Field | Description |
|---|---|
| Student ID | Unique student identification number |
| Name | Student's full name |
| Age | Student's age |
| Course | Enrolled course |
| Marks | Marks in five subjects |

## 📝 Result Calculation

The application calculates:

- Total Marks
- Percentage
- Pass or Fail Status
- Student Grade

**Passing Criteria:** 40%

**Grade Criteria:**

| Percentage | Grade |
|---|---|
| 90% and above | A+ |
| 80% - 89% | A |
| 70% - 79% | B |
| 60% - 69% | C |
| 40% - 59% | D |
| Below 40% | F |

## 🎯 Project Objectives

1. Understand the fundamentals of C programming.
2. Learn how to use structures to store student information.
3. Understand functions and modular programming.
4. Practice file handling for permanent data storage.
5. Perform basic CRUD operations.
6. Develop a simple real-world console application.

## 🚀 Future Improvements

- Add a graphical user interface.
- Add student login functionality.
- Generate student report cards.
- Add subject names dynamically.
- Improve input validation.
- Export student records to a text or CSV file.

## 🎓 Academic Information

**Project Name:** Student Management System

**Subject:** Computer Programming with C

**Project Type:** College Mini Project

**Language:** C Programming

**Level:** Beginner

## 👨‍💻 Author

Developed as a college mini project to practice and understand the fundamentals of C programming.

## 📜 License

This project is open-source and available for educational and learning purposes.
