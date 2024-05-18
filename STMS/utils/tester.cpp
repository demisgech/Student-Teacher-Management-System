
#include "StudentCrudOperation.h"
#include "TeacherCrudOperation.h"
#include <iostream>
#include <memory>
#include <stdexcept>

int main() {
  try {
    std::unique_ptr<DatabaseCrudOperation> studentOps =
        std::make_unique<StudentCrudOperation>("school.db");
    std::unique_ptr<DatabaseCrudOperation> teacherOps =
        std::make_unique<TeacherCrudOperation>("school.db");

    // Perform CRUD operations
    studentOps->insert("John Doe");
    teacherOps->insert("Jane Smith");

    studentOps->update(1, "Updated John Doe");
    teacherOps->update(1, "Updated Jane Smith");

    std::cout << studentOps->read(1) << std::endl;
    std::cout << teacherOps->read(1) << std::endl;

    studentOps->remove(1);
    teacherOps->remove(1);
  } catch (const std::exception &ex) {
    std::cout << ex.what() << std::endl;
  }
  return 0;
}
