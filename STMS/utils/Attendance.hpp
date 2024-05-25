#ifndef __ATTENDANCE__H__
#define __ATTENDANCE__H__

#include <chrono>
#include <sqlite3.h>
#include <string>

using namespace std;

class Attendance {
private:
  int id;
  int studentId;
  time_t date;
  string status;

public:
  Attendance();

  ~Attendance();
  void setId(int id);
  int getId();
  void setStudentId(int studentId);
  int getStudentId();

  void setDate(time_t date);
  time_t getDate();
  void setStatus(string &status);
  string getStatus();
};
class AttendanceOperation {
public:
  AttendanceOperation();
  ~AttendanceOperation();
  bool openDatabase(const char *dbPath);
  bool createTable();
  bool insertRecord(Attendance &data);
  bool selectAllRecords();

private:
  sqlite3 *db;
  bool executeQuery(const string &sql);
  static int callback(void *data, int argc, char **argv, char **azColName);
};
#endif //!__ATTENDANCE__H__
