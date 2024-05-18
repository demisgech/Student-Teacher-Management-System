#ifndef __STUDENT__H__
#define __STUDENT__H__

#include "Person.h"

class Student : public Person {
private:
  double CGPA;

public:
  void setCGPA(double CGPA);
  double getCGPA() const;

  using Person::Person;

  Student(const string &name, const string &phoneNumber, const string &email,
          const string &gender, int age, double CGPA);
  Student(const string &name, const string &phoneNumber, const string &email,
          const string &gender, int age, int id, double CGPA);
  ~Student() = default;
};

#endif //__STUDENT__H__