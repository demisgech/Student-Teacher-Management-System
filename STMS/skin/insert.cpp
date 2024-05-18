#include <sqlite3.h>
#include <string>

using namespace std;

void insert(sqlite3 *db, sqlite3_stmt *stmt, std::string sql) {
  sql = "INSERT INTO Students (name, age, gender, gpa) VALUES (?, ?, ?, ?);";
  sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

  sqlite3_bind_text(stmt, 1, "John Doe", -1, SQLITE_STATIC);
  sqlite3_bind_int(stmt, 2, 20);
  sqlite3_bind_text(stmt, 3, "Male", -1, SQLITE_STATIC);
  sqlite3_bind_double(stmt, 4, 3.5);

  sqlite3_step(stmt);
  sqlite3_finalize(stmt);
}