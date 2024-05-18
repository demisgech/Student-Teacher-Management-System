#include "StudentCrudOperation.h"
#include <iostream>
#include <stdexcept>

StudentCrudOperation::StudentCrudOperation(const std::string &dbPath) {
  if (sqlite3_open(dbPath.c_str(), &db)) {
    throw std::runtime_error("Can't open database: " +
                             std::string(sqlite3_errmsg(db)));
  }
}

StudentCrudOperation::~StudentCrudOperation() { sqlite3_close(db); }

void StudentCrudOperation::executeSQL(const std::string &sql) const {
  char *errMsg = nullptr;
  if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
    std::string error = "SQL error: " + std::string(errMsg);
    sqlite3_free(errMsg);
    throw std::runtime_error(error);
  }
}

void StudentCrudOperation::insert(const std::string &data) {
  std::string sql = "INSERT INTO students (name) VALUES ('" + data + "');";
  executeSQL(sql);
  std::cout << "Inserting student data: " << data << std::endl;
}

void StudentCrudOperation::update(int id, const std::string &data) {
  std::string sql = "UPDATE students SET name = '" + data +
                    "' WHERE id = " + std::to_string(id) + ";";
  executeSQL(sql);
  std::cout << "Updating student with ID " << id << " with data: " << data
            << std::endl;
}

void StudentCrudOperation::remove(int id) {
  std::string sql =
      "DELETE FROM students WHERE id = " + std::to_string(id) + ";";
  executeSQL(sql);
  std::cout << "Removing student with ID " << id << std::endl;
}

std::string StudentCrudOperation::read(int id) const {
  std::string sql =
      "SELECT name FROM students WHERE id = " + std::to_string(id) + ";";
  sqlite3_stmt *stmt;
  std::string result;

  if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
    throw std::runtime_error("Failed to prepare statement: " +
                             std::string(sqlite3_errmsg(db)));
  }

  if (sqlite3_step(stmt) == SQLITE_ROW) {
    result = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
  }

  sqlite3_finalize(stmt);

  std::cout << "Reading student with ID " << id << std::endl;
  return result.empty() ? "No data found" : result;
}
