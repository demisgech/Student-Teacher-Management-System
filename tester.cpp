
#include "STMS/utils/StudentCrudOperation.h"
#include "STMS/utils/TeacherCrudOperation.h"
#include <iostream>
#include <memory>
#include <stdexcept>

using namespace std;

int main() {
  try {
    unique_ptr<DatabaseCrudOperation<Student>> studentOps =
        make_unique<StudentCrudOperation>("Schools.db");

    unique_ptr<DatabaseCrudOperation<Teacher>> teacherOps =
        make_unique<TeacherCrudOperation>("Schools.db");

    // Perform CRUD operations
    Student student;
    studentOps->createTable();
    studentOps->insert(student);
    studentOps->readAll();
    int id;
    cout << "Id:";
    cin >> id;
    studentOps->read(id);

    Teacher teacher;
    teacherOps->createTable();
    teacherOps->insert(teacher);

    // studentOps->update(1, student);
    // teacherOps->update(1, teacher);

    // cout << studentOps->read(1) << endl;
    // cout << teacherOps->read(1) << endl;

    // studentOps->remove(1);
    // teacherOps->remove(1);
  } catch (const exception &ex) {
    cout << ex.what() << endl;
  }
  return 0;
}
