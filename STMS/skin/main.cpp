#include <iostream>
#include <sqlite3.h>

using namespace std;

int main() {
  // Initialize database connection
  sqlite3 *db;
  sqlite3_open("school.db", &db);

  while (true) {
    int choice;
    std::cout << "1. Add Student\n2. View Students\n3. Update Student\n4. "
                 "Delete Student\n5. Exit\n";
    std::cin >> choice;

    switch (choice) {
    case 1:
      // Call function to add student
      break;
    case 2:
      // Call function to view students
      break;
    case 3:
      // Call function to update student
      break;
    case 4:
      // Call function to delete student
      break;
    case 5:
      sqlite3_close(db);
      return 0;
    default:
      std::cout << "Invalid choice" << std::endl;
    }
  }

  //   g++ -o student_teacher_mgmt main.cpp sqlite3.c -lpthread -ldl
}
