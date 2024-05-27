#include "Attendance.hpp"
#include "GradePointAverage.hpp"
#include "StudentCrudOperation.h"
#include "TeacherCrudOperation.h"
#include "UserCrudOperation.h"
#include "authenticateUser.cpp"
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

    AttendanceOperation attendanceOps;
    attendanceOps.openDatabase("Schools.db");
    attendanceOps.createTable();

    GradePointAverageOperation gradePointAverageOps;
    gradePointAverageOps.openDatabase("Schools.db");
    gradePointAverageOps.createTable();

    cout << "******@@@@@@@@@@@@@@@@@******" << endl
         << "*                           *" << endl
         << "*       WELCOME TO          *" << endl
         << "*     STUDENT TEACHER       *" << endl
         << "*  MANAGEMENT SYSTEM (STMS) *" << endl
         << "*                           *" << endl
         << "******@@@@@@@@@@@@@@@@*******" << endl;

    char respose;
    do {
      cout << "1. SignUp" << endl << "2. Login" << endl << "Choice: ";
      int choice;
      cin >> choice;
      switch (choice) {
      case 1:
        userOps->insert(user);
        break;
      case 2: {
        sqlite3 *db;
        string username, password;

        if (sqlite3_open("Schools.db", &db)) {
          throw runtime_error("Can't open database: " +
                              string(sqlite3_errmsg(db)));
        }

        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;
        string role = authenticateUser(db, username, password);

        if (role.empty()) {
          sqlite3_close(db);
          throw invalid_argument{"Invalid username or password!!!"};
        }

        if (role == "Admin") {
          char res;
          do {
            std::cout << endl
                      << "Logged in successfully as: " << role << std::endl;
            cout << "1. Manage User" << endl
                 << "2. Take Attendance" << endl
                 << "3. Manage Student GPA" << endl
                 << "4. Logout" << endl
                 << "Choice: ";
            int manageTask;
            cin >> manageTask;
            if (manageTask == 1) {
              cout << "1. Register" << endl
                   << "2. View" << endl
                   << "3. Update" << endl
                   << "4. Search" << endl
                   << "5. Delete" << endl
                   << "6. Logout" << endl
                   << "Choice: ";
              int adminChoice;
              cin >> adminChoice;
              switch (adminChoice) {
              case 1: {
                cout << "1. Student" << endl
                     << "2. Teacher" << endl
                     << "Choice: ";
                int userResponse;
                cin >> userResponse;
                if (userResponse == 1)
                  studentOps->insert(student);
                else if (userResponse == 2)
                  teacherOps->insert(teacher);
                else
                  throw invalid_argument{
                      "Invalid choice!!! Please, try again!!"};
                break;
              }
              case 2: {
                cout << "1. Student" << endl
                     << "2. Teacher" << endl
                     << "choice: ";
                int userResponse;
                cin >> userResponse;
                if (userResponse == 1)
                  studentOps->readAll();
                else if (userResponse == 2)
                  teacherOps->readAll();
                else
                  throw invalid_argument{
                      "Invalid choice!!! Please, try again!!"};
                break;
              }
              case 3: {
                cout << "1. Student" << endl
                     << "2. Teacher" << endl
                     << "choice: ";
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
                  throw invalid_argument{
                      "Invalid choice!!! Please, try again!!"};
                break;
              }
              case 4: {
                cout << "1. Student" << endl
                     << "2. Teacher" << endl
                     << "choice: ";
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
                  throw invalid_argument{
                      "Invalid choice!!! Please, try again!!"};
                break;
              }
              case 5: {
                cout << "1. Student" << endl
                     << "2. Teacher" << endl
                     << "choice: ";
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
                  throw invalid_argument{
                      "Invalid choice!!! Please, try again!!"};
                break;
              }
              case 6: {
                cout << endl << "Logged out!!!" << endl;
                exit(0);
              }
              default:
                throw invalid_argument{"Invalid choice!!! Please, try again!!"};
              }
            } else if (manageTask == 2) {
              Attendance studAttendance;
              cout << "1. Insert record" << endl
                   << "2. View record" << endl
                   << "Choice: ";
              int attendanceTackerchoice;
              cin >> attendanceTackerchoice;
              if (attendanceTackerchoice == 1) {
                cout << "How many student would u like to record? : ";
                int n;
                cin >> n;

                for (int i = 0; i < n; i++) {
                  attendanceOps.insertRecord(studAttendance);
                }
              } else if (attendanceTackerchoice == 2)
                attendanceOps.selectAllRecords();
              else
                throw invalid_argument{"Invalid choice!!! Please, try again!!"};

            } else if (manageTask == 3) {
              // Manage Grade
              GradePointAverage studGradePointAverage;
              cout << "1. Insert record" << endl
                   << "2. View record" << endl
                   << "Choice: ";
              int gpaTakerChoice;
              cin >> gpaTakerChoice;
              if (gpaTakerChoice == 1) {
                cout << endl << "How many student would u like to record? : ";
                int n;
                cin >> n;

                for (int i = 0; i < n; i++) {
                  gradePointAverageOps.insertRecord(studGradePointAverage);
                }
              } else if (gpaTakerChoice == 2)
                gradePointAverageOps.selectAllRecords();
              else
                throw invalid_argument{"Invalid choice!!! Please, try again!!"};

            } else if (manageTask == 4) {
              cout << "Successfully logged out!!!" << endl;
              exit(0);
            } else
              throw invalid_argument{"Invalid choice!!! Please, try again!!"};

            cout << endl << "Would you like to do again? [Y(yes)/N(no)]: ";
            cin >> res;
          } while (res == 'y' || res == 'Y');
          cout << endl << "Thank you for using our app!!!" << endl;
          exit(0);
        } else if (role == "Guest") {
          char res;
          do {
            std::cout << endl
                      << "Logged in successfully as: " << role << std::endl;
            cout << "1. View" << endl
                 << "2. Search" << endl
                 << "3. Update" << endl
                 << "4. Logout" << endl
                 << "Choice: ";
            int guestChoice;
            cin >> guestChoice;
            switch (guestChoice) {
            case 1: {
              cout << "1. Student" << endl
                   << "2. Teacher" << endl
                   << "choice: ";
              int userResponse;
              cin >> userResponse;
              if (userResponse == 1)
                studentOps->readAll();
              else if (userResponse == 2)
                teacherOps->readAll();
              else
                throw invalid_argument{"Invalid choice!!! Please, try again!!"};
              break;
            }
            case 2: {
              cout << "1. Student" << endl
                   << "2. Teacher" << endl
                   << "choice: ";
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
                throw invalid_argument{"Invalid choice!!! Please, try again!!"};

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
                throw invalid_argument{"Invalid choice!!! Please, try again!!"};
              break;
            }
            case 4: {
              cout << endl << "Logged out!!!" << endl;
              exit(0);
              break;
            }
            default:
              throw invalid_argument{"Invalid choice!!! Please, try again!!"};
            }
            cout << endl << "Would you like to do again? [Y(yes)/N(no)]: ";
            cin >> res;
          } while (res == 'y' || res == 'Y');
          cout << endl << "Thank you for using out app!!" << endl;
          exit(0);
        } else
          throw invalid_argument{"Invalid choice!!! Please, try again!!"};
      }
      default:
        throw invalid_argument{"Invalid choice!!! Please, try again!!"};
      }
      cout << endl << "Would you like to continue? [Y(yes)/N(no)]: ";
      cin >> respose;
    } while (respose == 'y' || respose == 'Y');
    exit(0);
  } catch (const exception &ex) {
    cout << endl << ex.what() << endl;
  }
}