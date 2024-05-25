#include "TeacherCrudOperation.h"
#include <iostream>
#include <sqlite3.h>
#include <stdexcept>

using namespace std;

static int callback(void *data, int argc, char **argv, char **azColName) {
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

  cout << "**** Teachers registration *** \nPlease, enter your info. carefully!"
       << endl;
  cout << "name: ";
  string name;
  getline(cin, name);
  data.setName(name);

  cout << "phoneNumber:";
  string phoneNumber;
  getline(cin, phoneNumber);
  data.setPhoneNumber(phoneNumber);

  cout << "Email: ";
  string email;
  getline(cin, email);
  data.setEmail(email);

  cout << "age: ";
  int age;
  cin >> age;
  data.setAge(age);

  cout << "resume: ";
  double resume;
  cin >> resume;
  data.setResume(resume);

  cout << "Subject: ";
  string subject;
  getline(cin, subject);
  data.setSubject(subject);

  string sql = "INSERT INTO Teachers"
               "(name,phoneNumber,email,age,resume,Subject) VALUES ('" +
               data.getName() + "','" + data.getPhoneNumber() + "','" +
               data.getEmail() + "','" + to_string(data.getAge()) + "','" +
               to_string(data.getResume()) + "','" + data.getSubject() + "');";
  executeSQL(sql);
  cout << "Data Successfully Inserted!!!" << endl;
}

void TeacherCrudOperation::update(int id, Teacher &data) {
  // You can update anything and everything ...
  cout << "Update your name ..." << endl << "New Name:";
  string name;
  getline(cin, name);
  data.setName(name);
  string sql = "UPDATE Teachers SET name = '" + data.getName() + "'" +
               " WHERE id = " + to_string(id) + ";";
  executeSQL(sql);
  cout << "Data Successfuly Updated!!!" << endl;
}

void TeacherCrudOperation::remove(int id) {
  string sql = "DELETE FROM Teachers WHERE id = " + to_string(id) + ";";
  executeSQL(sql);
  cout << "Record successfully deleted!!!" << endl;
}

void TeacherCrudOperation::read(int id) const {
  string sql = "SELECT * FROM Teachers WHERE id = " + to_string(id) + ";";
  executeSQL(sql);
}
void TeacherCrudOperation::readAll() {
  string sql = "SELECT * FROM Teahers";
  executeSQL(sql);
}

void TeacherCrudOperation::createTable() {
  const char *sql_create_table =
      "CREATE TABLE IF NOT EXISTS Teachers ( id INTEGER PRIMARY KEY "
      "AUTOINCREMENT,name TEXT "
      "NOT NULL, age INTEGER, phoneNumber TEXT,email TEXT gender TEXT,resume "
      "REAL NOT NULL,Subject TEXT NOT NULL);";
  return executeSQL(sql_create_table);
}