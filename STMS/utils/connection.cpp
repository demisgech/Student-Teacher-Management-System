#include <iostream>
#include <sqlite3.h>

using namespace std;

void connect(sqlite3 *db) {

  int exit = sqlite3_open("school.db", &db);

  if (exit) {
    std::cerr << "Error open DB " << sqlite3_errmsg(db) << std::endl;
    return;
  } else {
    std::cout << "Opened Database Successfully!" << std::endl;
  }
}
