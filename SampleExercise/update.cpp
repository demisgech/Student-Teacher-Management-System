#include <sqlite3.h>
#include <string>

void update(sqlite3 *db, sqlite3_stmt *stmt, std::string sql) {

  sql = "UPDATE Students SET name = ? WHERE id = ?;";
  sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

  sqlite3_bind_text(stmt, 1, "Jane Doe", -1, SQLITE_STATIC);
  sqlite3_bind_int(stmt, 2, 1);

  sqlite3_step(stmt);
  sqlite3_finalize(stmt);
}