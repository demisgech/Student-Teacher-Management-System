#ifndef DATABASECRUDOPERATION_H
#define DATABASECRUDOPERATION_H

#include <string>

template <typename T> class DatabaseCrudOperation {
public:
  virtual ~DatabaseCrudOperation() = default;

  virtual void insert(T &data) = 0;
  virtual void update(int id, T &data) = 0;
  virtual void remove(int id) = 0;
  virtual std::string read(int id) const = 0;
};

#endif // DATABASECRUDOPERATION_H
