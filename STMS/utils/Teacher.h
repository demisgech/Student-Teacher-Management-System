#include "Person.h"

class Teacher : public Person {
private:
  double resume;

public:
  // Base class constructor inheritance

  using Person::Person;
  Teacher(const string &name, const string &phoneNumber, const string &email,
          const string &gender, int age, double CGPA);

  Teacher(const string &name, const string &phoneNumber, const string &email,
          const string &gender, int age, int id, double CGPA);

  void setResume(double resume);
  double getResume() const;

  ~Teacher();
};
