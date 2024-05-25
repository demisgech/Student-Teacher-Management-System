// #include "User.h"

#include "UserCrudOperation.h"
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

UserCrudOperation::UserCrudOperation(const string &dbPath) {
  if (sqlite3_open(dbPath.c_str(), &db)) {
    throw runtime_error("Can't open database: " + string(sqlite3_errmsg(db)));
  }
}

UserCrudOperation::~UserCrudOperation() { sqlite3_close(db); }

void UserCrudOperation::executeSQL(const string &sql) const {
  char *errMsg = nullptr;
  if (sqlite3_exec(db, sql.c_str(), callback, nullptr, &errMsg) != SQLITE_OK) {
    string error = "SQL error: " + string(errMsg);
    sqlite3_free(errMsg);
    throw runtime_error(error);
  }
}

void UserCrudOperation::insert(User &data) {

  cout << "**** User registration *** \nPlease, enter your info. carefully!"
       << endl;
  cout << "name: ";
  string name;
  cin >> name;
  // getline(cin, name);
  data.setUsername(name);

  cout << "Password: ";
  string password;
  cin >> password;
  // getline(cin, password);
  data.setPassword(password);

  cout << "Role:['Admin' or 'Guest'] : ";
  string Role;
  cin >> Role;
  // getline(cin, Role);
  data.setRole(Role);

  string sql = "INSERT INTO Users"
               "(username,password,role) VALUES ('" +
               data.getUsername() + "','" + data.getPassword() + "','" +
               data.getRole() + "');";
  executeSQL(sql);
  cout << "Account successfully created!!!" << endl;
}

void UserCrudOperation::update(int id, User &data) {
  // You can update anything and everything ...
  cout << "Update your username ..." << endl << "New Name:";
  string name;
  getline(cin, name);
  data.setUsername(name);

  string sql = "UPDATE Teachers SET name = '" + data.getUsername() + "'" +
               " WHERE id = " + to_string(id) + ";";
  executeSQL(sql);
  cout << "Data Successfuly Updated!!!" << endl;
}

void UserCrudOperation::remove(int id) {
  string sql = "DELETE FROM Users WHERE id = " + to_string(id) + ";";
  executeSQL(sql);
  cout << "Record successfully deleted!!!" << endl;
}

void UserCrudOperation::read(int id) const {
  string sql = "SELECT * FROM Users WHERE id = " + to_string(id) + ";";
  executeSQL(sql);
}
void UserCrudOperation::readAll() {
  string sql = "SELECT * FROM Users";
  executeSQL(sql);
}

void UserCrudOperation::createTable() {
  const char *sql_create_table =
      "CREATE TABLE IF NOT EXISTS Users ( id INTEGER PRIMARY KEY "
      "AUTOINCREMENT,username TEXT"
      "NOT NULL,password TEXT NOT NULL,"
      "role TEXT NOT NULL CHECK (role IN ('Admin', 'Guest')));";
  return executeSQL(sql_create_table);
}