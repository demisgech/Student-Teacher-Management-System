
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
