#include <iostream>
#include <sqlite3.h>

static int callback(void *data, int argc, char **argv, char **azColName) {
  static bool headersPrinted = false;

  // Print column headers only once
  if (!headersPrinted) {
    for (int i = 0; i < argc; i++) {
      std::cout << azColName[i] << "\t";
    }
    std::cout << std::endl;
    headersPrinted = true;
  }

  // Print data rows
  for (int i = 0; i < argc; i++) {
    std::cout << (argv[i] ? argv[i] : "NULL") << "\t";
  }
  std::cout << std::endl;

  return 0;
}

int main() {
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc;
  const char *data = "Callback function called";

  rc = sqlite3_open("test.db", &db);
  if (rc) {
    std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    return (0);
  } else {
    std::cout << "Opened database successfully" << std::endl;
  }

  // Create table
  const char *sql_create_table = "CREATE TABLE COMPANY("
                                 "ID INT PRIMARY KEY     NOT NULL,"
                                 "NAME           TEXT    NOT NULL,"
                                 "AGE            INT     NOT NULL,"
                                 "ADDRESS        CHAR(50),"
                                 "SALARY         REAL );";
  rc = sqlite3_exec(db, sql_create_table, callback, 0, &zErrMsg);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error: " << zErrMsg << std::endl;
    sqlite3_free(zErrMsg);
  } else {
    std::cout << "Table created successfully" << std::endl;
  }

  // Insert 10 records
  for (int i = 1; i <= 10; ++i) {
    std::string sql_insert = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "
                             "VALUES (" +
                             std::to_string(i) + ", 'Name " +
                             std::to_string(i) + "', " +
                             std::to_string(20 + i) + ", 'Address " +
                             std::to_string(i) + "', 2000.00 );";
    rc = sqlite3_exec(db, sql_insert.c_str(), callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
      std::cerr << "SQL error: " << zErrMsg << std::endl;
      sqlite3_free(zErrMsg);
    } else {
      std::cout << "Records created successfully" << std::endl;
    }
  }

  // Select all records
  const char *sql_select = "SELECT * FROM COMPANY;";
  rc = sqlite3_exec(db, sql_select, callback, (void *)data, &zErrMsg);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error: " << zErrMsg << std::endl;
    sqlite3_free(zErrMsg);
  } else {
    std::cout << "Operation done successfully" << std::endl;
  }

  // Update record
  const char *sql_update = "UPDATE COMPANY set SALARY = 25000.00 where ID=1;";
  rc = sqlite3_exec(db, sql_update, callback, 0, &zErrMsg);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error: " << zErrMsg << std::endl;
    sqlite3_free(zErrMsg);
  } else {
    std::cout << "Operation done successfully" << std::endl;
  }

  // Delete record
  const char *sql_delete = "DELETE from COMPANY where ID=2;";
  rc = sqlite3_exec(db, sql_delete, callback, 0, &zErrMsg);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error: " << zErrMsg << std::endl;
    sqlite3_free(zErrMsg);
  } else {
    std::cout << "Operation done successfully" << std::endl;
  }

  // Select all records after update and delete
  rc = sqlite3_exec(db, sql_select, callback, (void *)data, &zErrMsg);
  if (rc != SQLITE_OK) {
    std::cerr << "SQL error: " << zErrMsg << std::endl;
    sqlite3_free(zErrMsg);
  } else {
    std::cout << "Operation done successfully" << std::endl;
  }

  sqlite3_close(db);
  system("cls");
  return 0;
}
