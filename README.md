# C++ with SQLite3 database (Student Teacher Management System(STMS))

Welcome to the Student Teacher Management System! This application is designed to manage student and teacher information using C++ and SQLite3. The system provides CRUD (Create, Read, Update, Delete) operations for managing data. There are two types of users: Admin and Guest, each with different levels of access and capabilities.

## Features
**Admin User**:
- Full access to all CRUD operations.
- Can manage student and teacher records.
- Can view, add, update, and delete information.

 **Guest User**:
- Limited access to read operations.
- Can view student and teacher records.
- Cannot modify any information.
## Prerequisites
- C++ compiler
- SQLite3 library
- CMake build tool
## Installation
1. **Clone the repository**
```bash
git clone https://github.com/demisgech/Student-Teacher-Management-System.git
cd student-teacher-management
```

2. **Install SQLite3**
- Follow the instructions for your operating system to install SQLite3.
3. **Install CMake**
- Follow the instructions for your operating system to install CMake.
4. **Compile the application**
```
g++ -o management_system tester.cpp -l sqlite3 | (g++ -o management_system tester.cpp sqlite3.dll)
```
## Usage
1. **Run the application**
```bash
./management_system
```

2. **Login as Admin or Guest or signup**
    - Username: admin
    - Password: admin
    - Username: guest
    - Password: guest
3. **Admin Operations**:
- View Records: View all student and teacher records.
- Add Records: Add new student or teacher records.
- Update Records: Update existing student or teacher records.
- Delete Records: Delete student or teacher records.
4. **Guest Operations**:
- View Records: View all student and teacher records.
## Project Structure
```bash

.├── STMS
    ├── database 
    ├──utils
       ├── ...
       ├── ...
├── tester.cpp        # Main file
├── README.md       # Project documentation
└── ...
```
## Database Schema
1. **Students Table**
```sql
 CREATE TABLE Students (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    age INTEGER,
    phoneNumber TEXT,
    email TEXT,
    gender TEXT,
    cgpa REAL NOT NULL
);
```
2. **Teachers Table**
```sql
CREATE TABLE Teachers (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    phoneNumber TEXT,
    email TEXT,
    age INTEGER,
    gender TEXT,
    resume REAL NOT NULL,
    subject TEXT NOT NULL
);
```
3. **Attendance Table**
```sql
CREATE TABLE Attendance (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    student_id INTEGER,
    date DATE DEFAULT CURRENT_DATE,
    status TEXT NOT NULL CHECK( status IN('Absent','Present')),
    FOREIGN KEY (student_id) REFERENCES Students(id)
);
```
4. **GradePointAverage Table**
```sql
CREATE TABLE GradePointAverage (
    gpa_id INTEGER PRIMARY KEY AUTOINCREMENT,
    student_id INTEGER,
    gpa REAL NOT NULL,
    FOREIGN KEY (student_id) REFERENCES Students(id)
);
```
5. **StudentTeacher Table**
```sql
-- Joint table examples, if needed
CREATE TABLE StudentTeacher (
    student_id INTEGER,
    teacher_id INTEGER,
    FOREIGN KEY (student_id) REFERENCES Students(id),
    FOREIGN KEY (teacher_id) REFERENCES Teachers(id)
);
```
6. **Users Table**
```sql
CREATE TABLE Users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    password TEXT NOT NULL,
    role TEXT NOT NULL CHECK (role IN ('Admin', 'Guest'))
);
```
## C++ code Structure
1. **DatabaseCrudOperation.h**
```cpp
#ifndef DATABASECRUDOPERATION_H
#define DATABASECRUDOPERATION_H

#include <string>

template <typename T> class DatabaseCrudOperation {
public:
  virtual ~DatabaseCrudOperation() = default;
  virtual void createTable() = 0;
  virtual void insert(T &data) = 0;
  virtual void update(int id, T &data) = 0;
  virtual void remove(int id) = 0;
  virtual void read(int id) const = 0;
  virtual void readAll() = 0;
};

#endif // DATABASECRUDOPERATION_H

```
2. **StudentCrudOperation.h**
```cpp
#ifndef STUDENTCRUDOPERATION_H
#define STUDENTCRUDOPERATION_H

#include "DatabaseCrudOperation.h"
#include "Student.h"
#include <sqlite3.h>
#include <string>

class StudentCrudOperation : public DatabaseCrudOperation<Student> {
public:
  StudentCrudOperation(const std::string &dbPath);
  ~StudentCrudOperation();

  void insert(Student &data) override;
  void update(int id, Student &data) override;
  void remove(int id) override;
  void read(int id) const override;
  void createTable() override;
  void readAll() override;

private:
  sqlite3 *db;
  void executeSQL(const std::string &sql) const;
};

#endif // STUDENTCRUDOPERATION_H
```
3. **TeacherCrudOperation.h**
```cpp
#ifndef TEACHERCRUDOPERATION_H
#define TEACHERCRUDOPERATION_H

#include "DatabaseCrudOperation.h"
#include "Teacher.h"
#include <sqlite3.h>
#include <string>

using namespace std;

class TeacherCrudOperation : public DatabaseCrudOperation<Teacher> {
public:
  TeacherCrudOperation(const string &dbPath);
  ~TeacherCrudOperation();

  void insert(Teacher &data) override;
  void update(int id, Teacher &data) override;
  void remove(int id) override;
  void read(int id) const override;
  void createTable() override;
  void readAll() override;

private:
  sqlite3 *db;
  void executeSQL(const string &sql) const;
};

#endif // TEACHERCRUDOPERATION_H
```

```cpp

#include "StudentCrudOperation.h"
#include "TeacherCrudOperation.h"
#include <iostream>
#include <memory>
#include <stdexcept>

using namespace std;

int main() {
  try {
    unique_ptr<DatabaseCrudOperation<Student>> studentOps =
        make_unique<StudentCrudOperation>("School.db");

    unique_ptr<DatabaseCrudOperation<Teacher>> teacherOps =
        make_unique<TeacherCrudOperation>("School.db");

    // Perform CRUD operations
    Student student;
    studentOps->insert(student);

    Teacher teacher;
    teacherOps->insert(teacher);

    studentOps->update(1, student);
    teacherOps->update(1, teacher);

    studentOps->read(1);
    teacherOps->read(1);

    studentOps->remove(1);
    teacherOps->remove(1);
  } catch (const exception &ex) {
    cout << ex.what() << endl;
  }
  return 0;
}

```
## Future Enhancements
- Add more granular user roles and permissions.
- Implement a graphical user interface (GUI).
- Enhance security features, such as password encryption.
## Contributing
Feel free to fork this repository and submit pull requests. For major changes, please open an issue first to discuss what you would like to change.

## License
This project is licensed under the MIT License - see the LICENSE file for details.

## Contact
For any inquiries or feedback, please contact demisgech@gmail.com.

Thank you for using the Student Teacher Management System! We hope it makes managing your data easier and more efficient.
