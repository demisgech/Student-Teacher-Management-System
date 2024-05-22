#ifndef TEACHERCRUDOPERATION_H
#define TEACHERCRUDOPERATION_H

#include "../../library/sqlite3.h"
#include "DatabaseCrudOperation.h"
#include "Teacher.h"
#include <sqlite3.h>
#include <string>

using namespace std;

class TeacherCrudOperation : public DatabaseCrudOperation<Teacher> {
public:
  TeacherCrudOperation(const string &dbPath);
  ~TeacherCrudOperation();

  void insert(Teacher &data) override;
  void update(int id, Teacher &data) override;
  void remove(int id) override;
  string read(int id) const override;

private:
  sqlite3 *db;
  void executeSQL(const string &sql) const;
};

#endif // TEACHERCRUDOPERATION_H
