#include "User.h"

void User::serId(int id) { this->id = id; }
int User::getId() { return id; }

void User::setUsername(string &username) { this->username = username; }
string User::getUsername() { return username; }

void User::setPassword(string &password) { this->password = password; }
string User::getPassword() { return password; }

void User::setRole(string &role) { this->role = role; }
string User::getRole() { return role; }