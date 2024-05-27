CREATE TABLE Students (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    age INTEGER,
    phoneNumber TEXT,
    email TEXT,
    gender TEXT,
    cgpa REAL NOT NULL
);

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

CREATE TABLE Attendance (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    student_id INTEGER,
    date DATE DEFAULT CURRENT_DATE,
    status TEXT NOT NULL CHECK( status IN('Absent','Present')),
    FOREIGN KEY (student_id) REFERENCES Students(id)
);

CREATE TABLE GPA (
    gpa_id INTEGER PRIMARY KEY AUTOINCREMENT,
    student_id INTEGER,
    gpa REAL NOT NULL,
    FOREIGN KEY (student_id) REFERENCES Students(id)
);

-- Joint table examples, if needed
CREATE TABLE StudentTeacher (
    student_id INTEGER,
    teacher_id INTEGER,
    FOREIGN KEY (student_id) REFERENCES Students(id),
    FOREIGN KEY (teacher_id) REFERENCES Teachers(id)
);

CREATE TABLE Users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    password TEXT NOT NULL,
    role TEXT NOT NULL CHECK (role IN ('Admin', 'Guest'))
);
