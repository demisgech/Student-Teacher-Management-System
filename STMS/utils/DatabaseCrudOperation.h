#ifndef DATABASECRUDOPERATION_H
#define DATABASECRUDOPERATION_H

#include <string>

class DatabaseCrudOperation {
public:
  virtual ~DatabaseCrudOperation() = default;

  virtual void insert(const std::string &data) = 0;
  virtual void update(int id, const std::string &data) = 0;
  virtual void remove(int id) = 0;
  virtual std::string read(int id) const = 0;
};

#endif // DATABASECRUDOPERATION_H
