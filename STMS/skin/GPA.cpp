#include <iostream>
#include <sqlite3.h>
#include <string>

void addGPA(sqlite3 *db, int student_id, double gpa) {
  std::string sql = "INSERT INTO GPA (student_id, gpa, recorded_date) VALUES "
                    "(?, ?, datetime('now'));";
  sqlite3_stmt *stmt;
  sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

  sqlite3_bind_int(stmt, 1, student_id);
  sqlite3_bind_double(stmt, 2, gpa);

  sqlite3_step(stmt);
  sqlite3_finalize(stmt);
}

void viewGPA(sqlite3 *db, int student_id) {
  std::string sql = "SELECT gpa, recorded_date FROM GPA WHERE student_id = ?;";
  sqlite3_stmt *stmt;
  sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

  sqlite3_bind_int(stmt, 1, student_id);

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    std::cout << "GPA: " << sqlite3_column_double(stmt, 0)
              << ", Recorded Date: " << sqlite3_column_text(stmt, 1)
              << std::endl;
  }
  sqlite3_finalize(stmt);
}

void updateGPA(sqlite3 *db, int student_id, double new_gpa) {
  std::string sql =
      "UPDATE GPA SET gpa = ?, recorded_date = datetime('now') WHERE "
      "student_id = ? AND id = (SELECT MAX(id) FROM GPA WHERE student_id = ?);";
  sqlite3_stmt *stmt;
  sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

  sqlite3_bind_double(stmt, 1, new_gpa);
  sqlite3_bind_int(stmt, 2, student_id);
  sqlite3_bind_int(stmt, 3, student_id);

  sqlite3_step(stmt);
  sqlite3_finalize(stmt);
}

void deleteGPA(sqlite3 *db, int gpa_id) {
  std::string sql = "DELETE FROM GPA WHERE id = ?;";
  sqlite3_stmt *stmt;
  sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

  sqlite3_bind_int(stmt, 1, gpa_id);

  sqlite3_step(stmt);
  sqlite3_finalize(stmt);
}
