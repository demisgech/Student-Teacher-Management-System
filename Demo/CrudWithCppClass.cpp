#include <iostream>
#include <sqlite3.h>

class SQLiteCRUD {
public:
  SQLiteCRUD() : db(nullptr) {}

  ~SQLiteCRUD() {
    if (db) {
      sqlite3_close(db);
      db = nullptr;
    }
  }

  bool openDatabase(const char *filename) {
    int rc = sqlite3_open(filename, &db);
    if (rc) {
      std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
      return false;
    } else {
      std::cout << "Opened database successfully" << std::endl;
      return true;
    }
  }

  bool createTable() {
    const char *sql_create_table = "CREATE TABLE COMPANY("
                                   "ID INT PRIMARY KEY     NOT NULL,"
                                   "NAME           TEXT    NOT NULL,"
                                   "AGE            INT     NOT NULL,"
                                   "ADDRESS        CHAR(50),"
                                   "SALARY         REAL );";
    return executeQuery(sql_create_table);
  }

  bool insertRecord(int id, const char *name, int age, const char *address,
                    double salary) {
    std::string sql_insert = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "
                             "VALUES (" +
                             std::to_string(id) + ", '" + name + "', " +
                             std::to_string(age) + ", '" + address + "', " +
                             std::to_string(salary) + " );";
    return executeQuery(sql_insert.c_str());
  }

  bool selectAllRecords() {
    const char *sql_select = "SELECT * FROM COMPANY;";
    return executeQuery(sql_select);
  }

private:
  sqlite3 *db;

  bool executeQuery(const char *sql) {
    char *zErrMsg = 0;
    int rc = sqlite3_exec(db, sql, callback, nullptr, &zErrMsg);
    if (rc != SQLITE_OK) {
      std::cerr << "SQL error: " << zErrMsg << std::endl;
      sqlite3_free(zErrMsg);
      return false;
    } else {
      std::cout << "Operation done successfully" << std::endl;
      return true;
    }
  }

  static int callback(void *data, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
      std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << "\t";
    }
    std::cout << std::endl;
    return 0;
  }
};

int main() {
  SQLiteCRUD sqlite;

  if (!sqlite.openDatabase("test.db")) {
    return 1;
  }

  if (!sqlite.createTable()) {
    return 1;
  }

  for (int i = 1; i <= 10; ++i) {
    if (!sqlite.insertRecord(i, ("Name " + std::to_string(i)).c_str(), 20 + i,
                             ("Address " + std::to_string(i)).c_str(),
                             2000.00)) {
      return 1;
    }
  }

  if (!sqlite.selectAllRecords()) {
    return 1;
  }

  return 0;
}
