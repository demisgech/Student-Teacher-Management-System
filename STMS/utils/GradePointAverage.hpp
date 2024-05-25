#ifndef __GRADEPOINTAVERAGE__H__
#define __GRADEPOINTAVERAGE__H__

#include <sqlite3.h>
#include <string>

using namespace std;

class GradePointAverage {
private:
  int gpaId;
  int studentId;
  float gpa;

public:
  GradePointAverage();
  void setGpaId(int gpaId);
  int getGpaId();

  void setStudentId(int studentId);
  int getStudentId();

  void setGpa(float gpa);
  float getGpa();
  ~GradePointAverage();
};
class GradePointAverageOperation {
public:
  GradePointAverageOperation();
  ~GradePointAverageOperation();
  bool openDatabase(const char *dbPath);
  bool createTable();
  bool insertRecord(GradePointAverage &data);
  bool selectAllRecords();

private:
  sqlite3 *db;
  bool executeQuery(const string &sql);
  static int callback(void *data, int argc, char **argv, char **azColName);
};

#endif //!__GRADEPOINTAVERAGE__H__