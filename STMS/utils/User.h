#ifndef __USERS__H__
#define __USERS__H__

#include <string>

using namespace std;

class User {
private:
  int id;
  string username;
  string password;
  string role;

public:
  User() = default;
  void serId(int id);
  int getId();

  void setUsername(string &username);
  string getUsername();

  void setPassword(string &password);
  string getPassword();

  void setRole(string &role);
  string getRole();
};
#endif //!__USERS__H__