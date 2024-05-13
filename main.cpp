// #include "library/sqlite3.h"
#include <iostream>
#include <sqlite3.h>

int main() {

  sqlite3 *db;
  int rc = sqlite3_open("example.db", &db);

  if (rc) {
    std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    return 1;
  }

  std::cout << "Opened database successfully" << std::endl;

  sqlite3_close(db);
  return 0;
}
