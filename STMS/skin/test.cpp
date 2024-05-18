#include "Person.cpp"
#include <iostream>
using namespace std;

int main() {
  Person anotherPerson{"Demis", "123456789", "demis@gmail.com", "Male", 21, 1};

  string email = anotherPerson.getEmail();
  cout << email << endl;
  return 0;
}

#include "StudentCrudOperation.h"
#include "TeacherCrudOperation.h"
#include <iostream>
#include <memory>

int main() {
  std::unique_ptr<DatabaseCrudOperation> studentOps =
      std::make_unique<StudentCrudOperation>();
  std::unique_ptr<DatabaseCrudOperation> teacherOps =
      std::make_unique<TeacherCrudOperation>();

  studentOps->insert("John Doe");
  teacherOps->insert("Jane Smith");

  studentOps->update(1, "Updated John Doe");
  teacherOps->update(1, "Updated Jane Smith");

  std::cout << studentOps->read(1) << std::endl;
  std::cout << teacherOps->read(1) << std::endl;

  studentOps->remove(1);
  teacherOps->remove(1);

  return 0;
}
