#include <sqlite3.h>
#include <stdexcept>
#include <string>

using namespace std;

string authenticateUser(sqlite3 *db, const string &username,
                        const string &password) {
  string role = "";
  string sql = "SELECT role FROM Users WHERE username = ? AND password = ?;";
  sqlite3_stmt *stmt;

  // Prepare the SQL statement
  int rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    throw runtime_error{sqlite3_errmsg(db)};
  }

  // Bind the username and password parameters
  sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

  // Execute the statement and check if a row is returned
  rc = sqlite3_step(stmt);
  if (rc == SQLITE_ROW) {
    // Column index 0 refers to the first column in the result set
    role = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
  } else if (rc != SQLITE_DONE) {
    throw runtime_error{sqlite3_errmsg(db)};
  }

  // Finalize the statement to release resources
  sqlite3_finalize(stmt);

  return role;
}
