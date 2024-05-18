#include <sqlite3.h>
#include <string>

void deleteRecord(sqlite3 *db, sqlite3_stmt *stmt, std::string sql) {

  sql = "DELETE FROM Students WHERE id = ?;";
  sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

  sqlite3_bind_int(stmt, 1, 1);

  sqlite3_step(stmt);
  sqlite3_finalize(stmt);
}