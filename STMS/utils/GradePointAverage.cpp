#include "GradePointAverage.hpp"
#include <iostream>
#include <sqlite3.h>
#include <string>

using namespace std;

void GradePointAverage::setGpaId(int gpaId) { this->gpaId = gpaId; }
int GradePointAverage::getGpaId() { return gpaId; }

void GradePointAverage::setStudentId(int studentId) {
  this->studentId = studentId;
}
int GradePointAverage::getStudentId() { return studentId; }

void GradePointAverage::setGpa(float gpa) { this->gpa = gpa; }
float GradePointAverage::getGpa() { return gpa; }

GradePointAverageOperation::GradePointAverageOperation() : db(nullptr) {}

GradePointAverageOperation::~GradePointAverageOperation() {
  if (db) {
    sqlite3_close(db);
    db = nullptr;
  }
}

bool GradePointAverageOperation::openDatabase(const char *dbPath) {
  if (sqlite3_open(dbPath, &db)) {
    throw runtime_error("Can't open database: " + string(sqlite3_errmsg(db)));
  }
  return true;
}

bool GradePointAverageOperation::createTable() {
  const char *sql_create_table =
      "CREATE TABLE IF NOT EXISTS GradePointAverage("
      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
      "student_id  INTEGER  NOT NULL,"
      "gpa REAT NOT NULL,"
      "FOREIGN KEY (student_id) REFERENCES Students(id));";
  return executeQuery(sql_create_table);
}

bool GradePointAverageOperation::insertRecord(GradePointAverage &data) {
  cout << "Please, enter you info. carefully!!" << endl;
  cout << "StudentId: ";
  int studentId;
  cin >> studentId;
  data.setStudentId(studentId);

  cout << "GPA: ";
  float gpa;
  cin >> gpa;
  data.setGpa(gpa);
  std::string sql_insert = "INSERT INTO GradePointAverage (student_id,gpa) "
                           "VALUES ('" +
                           std::to_string(data.getStudentId()) + "', '" +
                           std::to_string(data.getGpa()) + "' );";
  return executeQuery(sql_insert.c_str());
}

bool GradePointAverageOperation::selectAllRecords() {
  const char *sql_select = "SELECT * FROM GradePointAverage;";
  return executeQuery(sql_select);
}

bool GradePointAverageOperation::executeQuery(const string &sql) {
  char *errMsg = nullptr;
  if (sqlite3_exec(db, sql.c_str(), callback, nullptr, &errMsg) != SQLITE_OK) {
    string error = "SQL error: " + string(errMsg);
    sqlite3_free(errMsg);
    throw runtime_error(error);
  }
  return true;
}

int GradePointAverageOperation::callback(void *data, int argc, char **argv,
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
