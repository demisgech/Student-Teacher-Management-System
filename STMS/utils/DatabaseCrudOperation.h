#ifndef DATABASECRUDOPERATION_H
#define DATABASECRUDOPERATION_H

#include <string>

template <typename T> class DatabaseCrudOperation {
public:
  virtual ~DatabaseCrudOperation() = default;
  virtual void createTable() = 0;
  virtual void insert(T &data) = 0;
  virtual void update(int id, T &data) = 0;
  virtual void remove(int id) = 0;
  virtual void read(int id) const = 0;
  virtual void readAll() = 0;
};

#endif // DATABASECRUDOPERATION_H
