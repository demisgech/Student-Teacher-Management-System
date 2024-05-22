#include "TeacherCrudOperation.h"
#include "../../library/sqlite3.h"
#include <iostream>
#include <sqlite3.h>
#include <stdexcept>

using namespace std;

TeacherCrudOperation::TeacherCrudOperation(const string &dbPath) {
  if (sqlite3_open(dbPath.c_str(), &db)) {
    throw runtime_error("Can't open database: " + string(sqlite3_errmsg(db)));
  }
}

TeacherCrudOperation::~TeacherCrudOperation() { sqlite3_close(db); }

void TeacherCrudOperation::executeSQL(const string &sql) const {
  char *errMsg = nullptr;
  if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
    string error = "SQL error: " + string(errMsg);
    sqlite3_free(errMsg);
    throw runtime_error(error);
  }
}

void TeacherCrudOperation::insert(Teacher &data) {
  cout << "Please, enter your info. carefully!" << endl;
  cout << "name:";
  string name;
  getline(cin, name);
  data.setName(name);

  cout << "phoneNumber:";
  string phoneNumber;
  getline(cin, phoneNumber);
  data.setPhoneNumber(phoneNumber);

  cout << "Email:";
  string email;
  getline(cin, email);
  data.setEmail(email);

  cout << "age:";
  int age;
  cin >> age;
  data.setAge(age);

  cout << "resume:";
  double resume;
  cin >> resume;
  data.setResume(resume);

  cout << "Subject:";
  string subject;
  getline(cin, subject);
  data.setSubject(subject);

  string sql = "INSERT INTO Teachers "
               "(name,phoneNumber,email,age,resume,subject) VALUES (" +
               data.getName() + data.getPhoneNumber() + data.getEmail() +
               to_string(data.getAge()) + to_string(data.getResume()) +
               data.getSubject() + ");";
  executeSQL(sql);
  cout << "Data Successfully Inserted!!!" << endl;
}

void TeacherCrudOperation::update(int id, Teacher &data) {
  // You can update anything and everything ...
  cout << "Update your name ..." << endl << "New Name:";
  string name;
  getline(cin, name);
  data.setName(name);
  string sql = "UPDATE Teachers SET name = " + data.getName() +
               " WHERE id = " + to_string(id) + ";";
  executeSQL(sql);
  cout << "Data Successfuly Updated!!!" << endl;
}

void TeacherCrudOperation::remove(int id) {
  string sql = "DELETE FROM Teachers WHERE id = " + to_string(id) + ";";
  executeSQL(sql);
  cout << "Record successfully deleted!!!" << endl;
}

string TeacherCrudOperation::read(int id) const {
  string sql =
      "SELECT name,email,subject FROM Teachers WHERE id = " + to_string(id) +
      ";";
  sqlite3_stmt *stmt;
  string result;

  if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
    throw runtime_error("Failed to prepare statement: " +
                        string(sqlite3_errmsg(db)));
  }

  if (sqlite3_step(stmt) == SQLITE_ROW) {
    result = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
  }

  sqlite3_finalize(stmt);

  cout << "Fetching data ..." << endl;
  return result.empty() ? "No data found" : result;
}
