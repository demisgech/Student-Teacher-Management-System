#include "Teacher.h"

Teacher::Teacher(const string &name, const string &phoneNumber,
                 const string &email, const string &gender, int age,
                 double resume)
    : Person(name, phoneNumber, email, gender, age), resume{resume} {}

Teacher::Teacher(const string &name, const string &phoneNumber,
                 const string &email, const string &gender, int age, int id,
                 double resume)
    : Person(name, phoneNumber, email, gender, age, id), resume{resume} {}

Teacher::~Teacher() {}

void Teacher::setResume(double resume) { this->resume = resume; }

double Teacher::getResume() const { return resume; }

void Teacher::setSubject(string subject) { this->subject = subject; }

string Teacher::getSubject() const { return subject; }