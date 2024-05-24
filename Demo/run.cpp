#include "sqlite3.h"
#include <iostream>

int main() {
  sqlite3 *db;
  char *errMsg = nullptr;

  // Open or create the database
  int rc = sqlite3_open("example.db", &db);
  if (rc != SQLITE_OK) {
    std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
    return 1;
  }

  // Create table if it doesn't exist
  const char *createTableSQL = "CREATE TABLE IF NOT EXISTS sample_table (id "
                               "INTEGER PRIMARY KEY, name TEXT, age INTEGER);";
  rc = sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMsg);
  if (rc != SQLITE_OK) {
    std::cerr << "Error creating table: " << errMsg << std::endl;
    sqlite3_free(errMsg);
    return 1;
  }

  // Insert sample data
  const char *insertDataSQL = "INSERT INTO sample_table (name, age) VALUES "
                              "('Alice', 30), ('Bob', 25), ('Charlie', 35);";
  rc = sqlite3_exec(db, insertDataSQL, nullptr, nullptr, &errMsg);
  if (rc != SQLITE_OK) {
    std::cerr << "Error inserting data: " << errMsg << std::endl;
    sqlite3_free(errMsg);
    return 1;
  }

  // Retrieve and print data
  const char *selectDataSQL = "SELECT * FROM sample_table;";
  sqlite3_stmt *stmt;
  rc = sqlite3_prepare_v2(db, selectDataSQL, -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    std::cerr << "Error preparing statement: " << sqlite3_errmsg(db)
              << std::endl;
    return 1;
  }

  std::cout << "Sample Data:" << std::endl;
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    int id = sqlite3_column_int(stmt, 0);
    const unsigned char *name = sqlite3_column_text(stmt, 1);
    int age = sqlite3_column_int(stmt, 2);
    std::cout << "ID: " << id << ", Name: " << name << ", Age: " << age
              << std::endl;
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);
  return 0;
}
