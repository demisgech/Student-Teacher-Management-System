#include "StudentCrudOperation.h"
#include "TeacherCrudOperation.h"
#include "UserCrudOperation.h"
#include "authenticateUser.cpp"
#include <cctype>
#include <iostream>
#include <memory>
#include <stdexcept>

using namespace std;
void handleOperation() {

  try {
    unique_ptr<DatabaseCrudOperation<Student>> studentOps =
        make_unique<StudentCrudOperation>("Schools.db");

    unique_ptr<DatabaseCrudOperation<Teacher>> teacherOps =
        make_unique<TeacherCrudOperation>("Schools.db");

    unique_ptr<DatabaseCrudOperation<User>> userOps =
        make_unique<UserCrudOperation>("Schools.db");
    Student student;
    Teacher teacher;
    User user;

    studentOps->createTable();
    teacherOps->createTable();
    userOps->createTable();

    cout << "******@@@@@@@@@@@@@@@@@******" << endl
         << "*                           *" << endl
         << "*       WELCOME TO          *" << endl
         << "*     STUDENT TEACHER       *" << endl
         << "*  MANAGEMENT SYSTEM (STMS) *" << endl
         << "*                           *" << endl
         << "******@@@@@@@@@@@@@@@@*******" << endl;

    cout << "1. SignUp" << endl << "2. Login" << endl << "Choice: ";
    int choice;
    cin >> choice;
    switch (choice) {
    case 1:
      userOps->insert(user);
      break;
    case 2: {
      sqlite3 *db;
      sqlite3_open("school.db", &db);
      string username, password;

      cout << "Username: ";
      cin >> username;
      cout << "Password: ";
      cin >> password;
      string role = authenticateUser(db, username, password);

      if (role.empty()) {
        std::cout << "Invalid username or password!!!" << std::endl;
        sqlite3_close(db);
        return;
      }

      if (role == "Admin") {
        std::cout << "Logged in successfully as: " << role << std::endl;
        cout << "1. Register" << endl
             << "2. View" << endl
             << "3. Update" << endl
             << "4. Search" << endl
             << "5. Delete" << endl
             << "6. Logout" << endl
             << "Choice: ";
        int adminChoice;
        switch (adminChoice) {
        case 1: {
          cout << "1. Student" << endl << "2. Teacher" << endl << "Choice: ";
          int userResponse;
          cin >> userResponse;
          if (userResponse == 1)
            studentOps->insert(student);
          else if (userResponse == 2)
            teacherOps->insert(teacher);
          else
            cout << "Invalid choice!!! Please, try again!!" << endl;
          break;
        }
        case 2: {
          cout << "1. Student" << endl << "2. Teacher" << endl << "choice: ";
          int userResponse;
          cin >> userResponse;
          if (userResponse == 1)
            studentOps->readAll();
          else if (userResponse == 2)
            teacherOps->readAll();
          else
            cout << "Invalid choice!!! Please, try again!!" << endl;
          break;
        }
        case 3: {
          cout << "1. Student" << endl << "2. Teacher" << endl << "choice: ";
          int userResponse;
          cin >> userResponse;
          if (userResponse == 1) {
            int id;
            cout << "Id: ";
            cin >> id;
            studentOps->update(id, student);
          } else if (userResponse == 2) {
            int id;
            cout << "Id: ";
            cin >> id;
            teacherOps->update(id, teacher);
          } else
            cout << "Invalid choice!!! Please, try again!!" << endl;
          break;
        }
        case 4: {
          cout << "1. Student" << endl << "2. Teacher" << endl << "choice: ";
          int userResponse;
          if (userResponse == 1) {
            int id;
            cout << "Id: ";
            cin >> id;
            studentOps->read(id);
          } else if (userResponse == 2) {
            int id;
            cout << "Id: ";
            cin >> id;
            teacherOps->read(id);
          } else
            cout << "Invalid choice!!! Please, try again!!" << endl;
          break;
        }
        case 5: {
          cout << "1. Student" << endl << "2. Teacher" << endl << "choice: ";
          int userResponse;
          cin >> userResponse;
          if (userResponse == 1) {
            int id;
            cout << "Id: ";
            cin >> id;
            studentOps->remove(id);
          } else if (userResponse == 2) {
            int id;
            cout << "Id: ";
            cin >> id;
            teacherOps->remove(id);
          } else
            cout << "Invalid choice!!! Please, try again!!" << endl;
          break;
        }
        case 6: {
          cout << "Logged out!!!" << endl;
          exit(0);
        }
        default:
          cout << "Invalid choice!!! Please, try again!!" << endl;
          break;
        }
      } else if (role == "Guest") {
        std::cout << "Logged in successfully as: " << role << std::endl;
        cout << "1. View" << endl
             << "2. Search" << endl
             << "3. Update" << endl
             << "4. Logout" << endl
             << "Choice: ";
        int guestChoice;
        cin >> guestChoice;
        switch (guestChoice) {
        case 1: {
          cout << "1. Student" << endl << "2. Teacher" << endl << "choice: ";
          int userResponse;
          cin >> userResponse;
          if (userResponse == 1)
            studentOps->readAll();
          else if (userResponse == 2)
            teacherOps->readAll();
          else
            cout << "Invalid choice!!! Please, try again!!" << endl;
          break;
        }
        case 2: {
          cout << "1. Student" << endl << "2. Teacher" << endl << "choice: ";
          int userResponse;
          cin >> userResponse;
          if (userResponse == 1) {
            int id;
            cout << "Id: ";
            cin >> id;
            studentOps->read(id);
          } else if (userResponse == 2) {
            int id;
            cout << "Id: ";
            cin >> id;
            teacherOps->read(id);
          } else
            cout << "Invalid choice!!! Please, try again!!" << endl;
          break;
        }
        case 3: {
          cout << "1. Update user" << endl << "choice: ";
          int userResponse;
          cin >> userResponse;
          if (userResponse == 1) {
            int id;
            cout << "Id: ";
            cin >> id;
            userOps->update(id, user);
          } else
            cout << "Invalid choice!!! Please, try again!!" << endl;
          break;
        }
        case 4: {
          cout << "Logged out!!!" << endl;
          exit(0);
          break;
        }
        default:
          cout << "Invalid choice!!! Please, try again!!" << endl;
          break;
        }
      } else
        cout << "Invalid choice!!! Please, try again!!" << endl;
      break;
    }
    default:
      cout << "Invalid choice!!! Please, try again!!" << endl;
      break;
    }
  } catch (const exception &ex) {
    cout << ex.what() << endl;
  }
}