

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

GradePointAverage::GradePointAverage() {}
GradePointAverage::~GradePointAverage() {}

void GradePointAverage::setGpaId(int gpaId) { this->gpaId = gpaId; }
int GradePointAverage::getGpaid() { return gpaid; }

void GradePointAverage::setStudentId(int studentId) {
  this->studentId = studentId;
}
int GradePointAverage::getStudentid() { return studentId; }

void GradePointAverage::setGpa(float gpa) { this->gpa = gpa; }
float GradePointAverage::getGpa() { return gpa; }

class GradePointAverageOperation {
public:
  GradePointAverageOperation() : db(nullptr) {}

  ~GradePointAverageOperation() {
    if (db) {
      sqlite3_close(db);
      db = nullptr;
    }
  }

  bool openDatabase(const char *filename) {
    int rc = sqlite3_open(filename, &db);
    if (rc) {
      std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
      return false;
    } else {
      std::cout << "Database successfully opened!!!" << std::endl;
      return true;
    }
  }

  bool createTable() {
    const char *sql_create_table =
        "CREATE TABLE IF NOT EXISTS GradePointAverage("
        "id INTEGER PRIMARY KEY NOT NULL AUTOINCREMENT,"
        "studentId  INTEGER  NOT NULL,"
        "gpa REAT NOT NULL,"
        "FOREIGN KEY (student_id) REFERENCES Students(id);";
    return executeQuery(sql_create_table);
  }

  bool insertRecord(GradePointAverage &data) {
    cout << "Please, enter you info. carefully!!" << endl;
    cout << "StudentId: ";
    int studentId;
    cin >> studentId;
    data.setStudentId(studentId);

    cout << "GPA: ";
    float gpa;
    cin >> gpa;
    data.setGpa(gpa);
    std::string sql_insert = "INSERT INTO GradePointAverage (studentId,status) "
                             "VALUES (" +
                             std::to_string(data.getStudentId()) + ", '" +
                             data.getGpa() + " );";
    return executeQuery(sql_insert.c_str());
  }

  bool selectAllRecords() {
    const char *sql_select = "SELECT * FROM GradePointAverage ;";
    return executeQuery(sql_select);
  }

private:
  sqlite3 *db;

  bool executeQuery(const string &sql) {
    char *errMsg = nullptr;
    if (sqlite3_exec(db, sql.c_str(), callback, nullptr, &errMsg) !=
        SQLITE_OK) {
      string error = "SQL error: " + string(errMsg);
      sqlite3_free(errMsg);
      throw runtime_error(error);
    }
    return true;
  }

  static int callback(void *data, int argc, char **argv, char **azColName) {
    static bool headersPrinted = false;
    if (!headersPrinted) {
      for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << "\t";
      }
      std::cout << std::endl;
      headersPrinted = true;
    }
    for (int i = 0; i < argc; i++) {
      std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << "\t";
    }
    std::cout << std::endl;
    return 0;
  }
};