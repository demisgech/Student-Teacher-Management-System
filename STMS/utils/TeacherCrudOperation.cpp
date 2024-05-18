#include "TeacherCrudOperation.h"
#include <iostream>
#include <stdexcept>

TeacherCrudOperation::TeacherCrudOperation(const std::string &dbPath) {
  if (sqlite3_open(dbPath.c_str(), &db)) {
    throw std::runtime_error("Can't open database: " +
                             std::string(sqlite3_errmsg(db)));
  }
}

TeacherCrudOperation::~TeacherCrudOperation() { sqlite3_close(db); }

void TeacherCrudOperation::executeSQL(const std::string &sql) const {
  char *errMsg = nullptr;
  if (sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
    std::string error = "SQL error: " + std::string(errMsg);
    sqlite3_free(errMsg);
    throw std::runtime_error(error);
  }
}

void TeacherCrudOperation::insert(const std::string &data) {
  std::string sql = "INSERT INTO teachers (name) VALUES ('" + data + "');";
  executeSQL(sql);
  std::cout << "Inserting teacher data: " << data << std::endl;
}

void TeacherCrudOperation::update(int id, const std::string &data) {
  std::string sql = "UPDATE teachers SET name = '" + data +
                    "' WHERE id = " + std::to_string(id) + ";";
  executeSQL(sql);
  std::cout << "Updating teacher with ID " << id << " with data: " << data
            << std::endl;
}

void TeacherCrudOperation::remove(int id) {
  std::string sql =
      "DELETE FROM teachers WHERE id = " + std::to_string(id) + ";";
  executeSQL(sql);
  std::cout << "Removing teacher with ID " << id << std::endl;
}

std::string TeacherCrudOperation::read(int id) const {
  std::string sql =
      "SELECT name FROM teachers WHERE id = " + std::to_string(id) + ";";
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

  std::cout << "Reading teacher with ID " << id << std::endl;
  return result.empty() ? "No data found" : result;
}

// Example
