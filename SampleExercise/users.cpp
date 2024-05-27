#include "GPA.cpp"
#include <iostream>
#include <sqlite3.h>
#include <string>

// Function to authenticate user and return their role
std::string authenticateUser(sqlite3 *db, const std::string &username,
                             const std::string &password) {
  std::string role = "";
  std::string sql =
      "SELECT role FROM Users WHERE username = ? AND password = ?";
  sqlite3_stmt *stmt;

  sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
  sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

  if (sqlite3_step(stmt) == SQLITE_ROW) {
    role = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
  }

  sqlite3_finalize(stmt);
  return role;
}

int main() {
  sqlite3 *db;
  sqlite3_open("school.db", &db);

  std::string username, password, role;
  std::cout << "Username: ";
  std::cin >> username;
  std::cout << "Password: ";
  std::cin >> password;

  role = authenticateUser(db, username, password);

  if (role.empty()) {
    std::cout << "Invalid username or password." << std::endl;
    sqlite3_close(db);
    return 1;
  }

  std::cout << "Login successful. Role: " << role << std::endl;

  while (true) {
    int choice;
    std::cout << "1. Add Student\n2. View Students\n3. Update Student\n4. "
                 "Delete Student\n5. Add GPA\n6. View GPA\n7. Update GPA\n8. "
                 "Delete GPA\n9. Exit\n";
    std::cin >> choice;

    int student_id;
    double gpa;

    switch (choice) {
    case 1:
      if (role == "Admin") {
        // Call function to add student
      } else {
        std::cout << "Permission denied." << std::endl;
      }
      break;
    case 2:
      // Call function to view students
      break;
    case 3:
      if (role == "Admin") {
        // Call function to update student
      } else {
        std::cout << "Permission denied." << std::endl;
      }
      break;
    case 4:
      if (role == "Admin") {
        // Call function to delete student
      } else {
        std::cout << "Permission denied." << std::endl;
      }
      break;
    case 5:
      if (role == "Admin") {
        std::cout << "Enter student ID: ";
        std::cin >> student_id;
        std::cout << "Enter GPA: ";
        std::cin >> gpa;
        addGPA(db, student_id, gpa);
      } else {
        std::cout << "Permission denied." << std::endl;
      }
      break;
    case 6:
      std::cout << "Enter student ID: ";
      std::cin >> student_id;
      viewGPA(db, student_id);
      break;
    case 7:
      if (role == "Admin") {
        std::cout << "Enter student ID: ";
        std::cin >> student_id;
        std::cout << "Enter new GPA: ";
        std::cin >> gpa;
        updateGPA(db, student_id, gpa);
      } else {
        std::cout << "Permission denied." << std::endl;
      }
      break;
    case 8:
      if (role == "Admin") {
        int gpa_id;
        std::cout << "Enter GPA record ID to delete: ";
        std::cin >> gpa_id;
        deleteGPA(db, gpa_id);
      } else {
        std::cout << "Permission denied." << std::endl;
      }
      break;
    case 9:
      sqlite3_close(db);
      return 0;
    default:
      std::cout << "Invalid choice" << std::endl;
    }
  }
}
