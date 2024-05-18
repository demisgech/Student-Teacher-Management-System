#ifndef TEACHERCRUDOPERATION_H
#define TEACHERCRUDOPERATION_H

#include "DatabaseCrudOperation.h"
#include <sqlite3.h>
#include <string>

class TeacherCrudOperation : public DatabaseCrudOperation {
public:
  TeacherCrudOperation(const std::string &dbPath);
  ~TeacherCrudOperation();

  void insert(const std::string &data) override;
  void update(int id, const std::string &data) override;
  void remove(int id) override;
  std::string read(int id) const override;

private:
  sqlite3 *db;
  void executeSQL(const std::string &sql) const;
};

#endif // TEACHERCRUDOPERATION_H
