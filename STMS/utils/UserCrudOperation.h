#include "DatabaseCrudOperation.h"
#include "User.h"
#include <sqlite3.h>

class UserCrudOperation : public DatabaseCrudOperation<User> {
  UserCrudOperation(const string &dbPath);
  ~UserCrudOperation();

  void insert(User &data) override;
  void update(int id, User &data) override;
  void remove(int id) override;
  void read(int id) const override;
  void createTable() override;
  void readAll() override;

private:
  sqlite3 *db;
  void executeSQL(const string &sql) const;
};