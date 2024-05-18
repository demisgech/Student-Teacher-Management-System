#ifndef __PERSON__H__
#define __PERSON__H__

#include <string>

using namespace std;

class Person {
public:
  Person(const string &name, const string &phoneNumber, const string &email,
         const string &gender, int age);
  Person(const string &name, const string &phoneNumber, const string &email,
         const string &gender, int age, int id);

  void setId(int id);
  void setAge(int age);

  void setName(const string &name);
  void setPhoneNumber(const string &phoneNumber);
  void setEmail(const string &email);
  void setGender(const string &gender);

  int getId() const;
  int getAge() const;

  string getName() const;
  string getPhoneNumber() const;
  string getEmail() const;
  string getGender() const;

protected:
  int id;
  string name;
  string phoneNumber;
  string email;
  int age;
  string gender;
};

#endif //!__PERSON__H__