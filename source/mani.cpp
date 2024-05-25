#include "sqlite3.h"
#include <iomanip>
#include <iostream>

using namespace std;

int main() {

  sqlite3 *db;
  char *errMsg = nullptr;
  bool connection = sqlite3_open("School.db", &db);
  if (!connection) {
    cout << "Database opened successfully!!! " << endl;
  } else {
    cout << "Can't open database. " << sqlite3_errmsg(db) << endl;
    return 1;
  }
  const char *sql =
      "CREATE TABLE IF NOT EXISTS Users(id INTEGER PRIMARY KEY AUTOINCREMENT, "
      "name TEXT NOT NULL);";
  connection = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);

  if (connection != SQLITE_OK) {
    cout << "The table create an error: " << errMsg << endl;
    sqlite3_free(errMsg);
    return 1;
  } else {
    cout << "Table created successfully!!!" << endl;
  }

  const char *insertQuery =
      "INSERT INTO Users(name) VALUES('Demis'),('Abebe'),('Dejen'),('Kebede');";

  connection = sqlite3_exec(db, insertQuery, nullptr, nullptr, &errMsg);

  if (connection == SQLITE_OK) {
    cout << "Data inserted successfully!!!" << endl;
  } else {
    cout << "The table create an error: " << errMsg << endl;
    sqlite3_free(errMsg);
    return 1;
  }

  const char *selectQuery = "SELECT * FROM Users;";

  sqlite3_stmt *stmt;
  connection = sqlite3_prepare_v2(db, selectQuery, -1, &stmt, 0);

  if (connection == SQLITE_OK) {
    cout << "Data retrieved successfully!!!" << endl;
  } else {
    cout << "The table create an error: " << errMsg << endl;
    sqlite3_free(errMsg);
    return 1;
  }

  cout << "**** Sample data ****" << endl;
  cout << "ID" << setw(10) << "Name" << endl;
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    int id = sqlite3_column_int(stmt, 0);
    const unsigned char *name = sqlite3_column_text(stmt, 1);
    cout << id << setw(10) << name << endl;
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);
  return 0;
}
