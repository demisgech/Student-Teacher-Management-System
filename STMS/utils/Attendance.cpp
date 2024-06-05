
#include "Attendance.hpp"
#include <chrono>
#include <iostream>
#include <sqlite3.h>
#include <stdexcept>
#include <string>
using namespace std;


void Attendance::setId(int id) { this->id = id; }

int Attendance::getId() { return id; }

void Attendance::setStudentId(int studentId) { this->studentId = studentId; }

int Attendance::getStudentId() { return studentId; }

void Attendance::setDate(time_t date) { this->date = date; }
time_t Attendance::getDate() { return date; }

void Attendance::setStatus(string &status) { this->status = status; }

string Attendance::getStatus() { return status; }

AttendanceOperation::AttendanceOperation() : db(nullptr) {}

AttendanceOperation::~AttendanceOperation() {
  if (db) {
    sqlite3_close(db);
    db = nullptr;
  }
}

bool AttendanceOperation::openDatabase(const char *dbPath) {
  if (sqlite3_open(dbPath, &db)) {
    throw runtime_error("Can't open database: " + string(sqlite3_errmsg(db)));
  }
  return true;
}

bool AttendanceOperation::createTable() {
  const char *sql_create_table =
      "CREATE TABLE IF NOT EXISTS Attendance("
      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
      "student_id  INTEGER  NOT NULL,"
      "date DATE DEFAULT CURRENT_DATE,"
      "status TEXT NOT NULL CHECK( status IN('Absent','Present')),"
      "FOREIGN KEY (student_id) REFERENCES Students(id));";
  return executeQuery(sql_create_table);
}

bool AttendanceOperation::insertRecord(Attendance &data) {
  cout << "Please, enter you info. carefully!!" << endl;
  cout << "StudentId: ";
  int studentId;
  cin >> studentId;
  data.setStudentId(studentId);

  cout << "Status: ";
  string status;
  cin >> status;
  data.setStatus(status);
  std::string sql_insert = "INSERT INTO Attendance (student_id,status) "
                           "VALUES ('" +
                           std::to_string(data.getStudentId()) + "', '" +
                           data.getStatus() + "' );";
  return executeQuery(sql_insert.c_str());
}

bool AttendanceOperation::selectAllRecords() {
  const char *sql_select = "SELECT * FROM Attendance;";
  return executeQuery(sql_select);
}

bool AttendanceOperation::executeQuery(const string &sql) {
  char *errMsg = nullptr;
  if (sqlite3_exec(db, sql.c_str(), callback, nullptr, &errMsg) != SQLITE_OK) {
    string error = "SQL error he: " + string(errMsg);
    sqlite3_free(errMsg);
    throw runtime_error(error);
  }
  return true;
}

int AttendanceOperation::callback(void *data, int argc, char **argv,
                                  char **azColName) {
  static bool headersPrinted = false;
  if (!headersPrinted) {
    for (int i = 0; i < argc; i++) {
      std::cout << azColName[i] << "\t";
    }
    std::cout << std::endl;
    headersPrinted = true;
  }
  for (int i = 0; i < argc; i++) {
    std::cout << (argv[i] ? argv[i] : "NULL") << "\t";
  }
  std::cout << std::endl;
  return 0;
}
