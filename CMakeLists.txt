cmake_minimum_required(VERSION 3.5)
project(HelloWorld
    VERSION 0.0.1
    DESCRIPTION "Student Teacher Management System"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

add_executable(excute tester.cpp
STMS/utils/StudentCrudOperation.cpp
STMS/utils/TeacherCrudOperation.cpp 
STMS/utils/UserCrudOperation.cpp 
STMS/utils/Attendance.cpp
STMS/utils/GradePointAverage.cpp
STMS/utils/Teacher.cpp 
STMS/utils/Student.cpp 
STMS/utils/Person.cpp 
STMS/utils/User.cpp 
)

target_link_libraries(excute PRIVATE sqlite3)