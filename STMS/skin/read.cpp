#include <iostream>
#include <sqlite3.h>

void read() {
  sqlite3 *db;
  std::string sql = "SELECT * FROM Students;";
  sqlite3_stmt *stmt;

  sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    std::cout << "ID: " << sqlite3_column_int(stmt, 0) << std::endl;
    std::cout << "Name: " << sqlite3_column_text(stmt, 1) << std::endl;
    std::cout << "Age: " << sqlite3_column_int(stmt, 2) << std::endl;
    std::cout << "Gender: " << sqlite3_column_text(stmt, 3) << std::endl;
    std::cout << "GPA: " << sqlite3_column_double(stmt, 4) << std::endl;
  }
  sqlite3_finalize(stmt);
}