#include "Person.h"

Person::Person(const string &name, const string &phoneNumber,
               const string &email, const string &gender, int age) {
  this->name = name;
  this->phoneNumber = phoneNumber;
  this->email = email;
  this->gender = gender;
  this->age = age;
}

Person::Person(const string &name, const string &phoneNumber,
               const string &email, const string &gender, int age, int id)
    : Person(name, phoneNumber, email, gender, age) {
  this->id = id;
}

void Person::setId(int id) { this->id = id; }

void Person::setName(const string &name) { this->name = name; }

void Person::setPhoneNumber(const string &phoneNumber) {
  this->phoneNumber = phoneNumber;
}

void Person::setEmail(const string &email) { this->email = email; }

void Person::setGender(const string &gender) { this->gender = gender; }

void Person::setAge(int age) { this->age = age; }

int Person::getAge() const { return age; }

int Person::getId() const { return id; }

string Person::getName() const { return name; }

string Person::getPhoneNumber() const { return phoneNumber; }

string Person::getEmail() const { return email; }

string Person::getGender() const { return gender; }
