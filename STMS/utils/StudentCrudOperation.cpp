#include "StudentCrudOperation.h"
#include "../../library/sqlite3.h"
#include <iostream>
#include <sqlite3.h>
#include <stdexcept>
using namespace std;

StudentCrudOperation::StudentCrudOperation(const string &dbPath) {
  if (sqlite3_open(dbPath.c_str(), &db)) {
    throw runtime_error("Can't open database: " + string(sqlite3_errmsg(db)));
  }
}

StudentCrudOperation::~StudentCrudOperation() { sqlite3_close(db); }

void StudentCrudOperation::executeSQL(const string &sql) const {
  char *errMsg = nullptr;
  if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
    string error = "SQL error: " + string(errMsg);
    sqlite3_free(errMsg);
    throw runtime_error(error);
  }
}

void StudentCrudOperation::insert(Student &data) {
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
  double cgpa;
  cin >> cgpa;
  data.setCGPA(cgpa);

  string sql = "INSERT INTO Students "
               "(name,phoneNumber,email,age,cgpa) VALUES (" +
               data.getName() + data.getPhoneNumber() + data.getEmail() +
               to_string(data.getAge()) + to_string(data.getCGPA()) + ");";
  executeSQL(sql);
  cout << "Data Successfully Inserted!!!" << endl;
}

void StudentCrudOperation::update(int id, Student &data) {
  // You can update anything and everything ...
  cout << "Update your name ..." << endl << "New Name:";
  string name;
  getline(cin, name);
  data.setName(name);
  string sql = "UPDATE Students SET name = " + data.getName() +
               " WHERE id = " + to_string(id) + ";";
  executeSQL(sql);
  cout << "Data Successfuly Updated!!!" << endl;
}

void StudentCrudOperation::remove(int id) {
  string sql = "DELETE FROM Students WHERE id = " + to_string(id) + ";";
  executeSQL(sql);
  cout << "Record successfully deleted!!!" << endl;
}

string StudentCrudOperation::read(int id) const {
  string sql = "SELECT name FROM students WHERE id = " + to_string(id) + ";";
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

  cout << "Reading student with ID " << id << endl;
  return result.empty() ? "No data found" : result;
}
