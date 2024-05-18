#include "Student.h"

Student::Student(const string &name, const string &phoneNumber,
                 const string &email, const string &gender, int age,
                 double CGPA)
    : Person(name, phoneNumber, email, gender, age), CGPA{CGPA} {}

Student::Student(const string &name, const string &phoneNumber,
                 const string &email, const string &gender, int age, int id,
                 double CGPA)
    : Person(name, phoneNumber, email, gender, age, id), CGPA{CGPA} {}

void Student::setCGPA(double CGPA) { this->CGPA = CGPA; }

double Student::getCGPA() const { return CGPA; }
