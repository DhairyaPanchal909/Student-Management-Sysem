# Student Management System in C

A console-based **Student Management System** developed in C using binary file handling, structures, modular functions, and input validation. Suitable for college mini-projects, practical lab exams, and beginners learning C programming.

---

## 📌 Features

1. **Add Student**: Add a new student record (ID, Name, Age, Course, and marks in 5 subjects). Prevents duplicate IDs.
2. **Display All Students**: View formatted details of all registered students.
3. **Search Student**: Search student details by unique ID.
4. **Update Student**: Modify existing student name, age, course, and marks in-place.
5. **Delete Student**: Safely delete a record using temporary file swapping.
6. **Calculate Result**: Calculate total marks, percentage, pass/fail status, and letter grades (A+ to F).
7. **Persistent Storage**: All records are stored permanently in a binary file (`students.dat`).

---

## 🛠️ Concepts Used

- **Structures (`struct Student`)**: Groups heterogeneous data fields for each student.
- **File Handling (`fopen`, `fread`, `fwrite`, `fseek`, `remove`, `rename`)**: Binary file operations.
- **Functions & Modular Programming**: 11 separate functions for specific operations.
- **Input Validation & Buffer Clearing**: Handling invalid inputs and cleaning stdin buffer.
- **Control Flow**: `switch-case` menu loop, `if-else` condition checking, and `while`/`for` loops.

---

## 💻 How to Compile and Run

### Prerequisites
- GCC Compiler (MinGW / MSYS2 / Linux GCC)
- Any IDE or text editor (VS Code, Code::Blocks, CLion, Dev-C++)

### 1. Compile
Open your terminal/command prompt in this project folder and run:

```bash
gcc student_management.c -o student_management -Wall
```

### 2. Run
```bash
# On Windows:
student_management.exe

# On Linux/macOS:
./student_management
```

---

## 📁 Project Structure

```
├── student_management.c                # Main C source code
├── README.md                           # Documentation & instructions
└── Student_Management_System_Report.md # Full project report, algorithms, flowcharts & viva Q&A
```

---

## 👤 Author
- GitHub: [@DhairyaPanchal909](https://github.com/DhairyaPanchal909)
