#ifndef STUDENTCRUDOPERATION_H
#define STUDENTCRUDOPERATION_H

#include "DatabaseCrudOperation.h"
#include <sqlite3.h>
#include <string>

class StudentCrudOperation : public DatabaseCrudOperation {
public:
  StudentCrudOperation(const std::string &dbPath);
  ~StudentCrudOperation();

  void insert(const std::string &data) override;
  void update(int id, const std::string &data) override;
  void remove(int id) override;
  std::string read(int id) const override;

private:
  sqlite3 *db;
  void executeSQL(const std::string &sql) const;
};

#endif // STUDENTCRUDOPERATION_H
