#include <sqlite3.h>
#include <string>

using namespace std;
string authenticateUser(sqlite3 *db, const string &username,
                        const string &password) {
  string role = "";
  string sql = "SELECT role FROM Users WHERE username = " + username +
               "  AND password = " + password + " ;";
  sqlite3_stmt *stmt;

  sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
  sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

  if (sqlite3_step(stmt) == SQLITE_ROW) {
    role = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
  }

  sqlite3_finalize(stmt);
  return role;
}