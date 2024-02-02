cmake_minimum_required(VERSION 3.11)
project(FitnessTracker VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include main source file
add_executable(${PROJECT_NAME} main.cpp)

# Fetch SQLiteCpp library
include(FetchContent)
FetchContent_Declare(
    sqlitecpp
    GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
    GIT_TAG origin/master
)
FetchContent_MakeAvailable(sqlitecpp)

# Assuming SQLiteCpp exposes itself as SQLiteCpp target; adjust if necessary
target_link_libraries(${PROJECT_NAME} SQLiteCpp)

# If SQLiteCpp requires manually linking against SQLite3, uncomment the following:
# find_package(SQLite3 REQUIRED)
# target_link_libraries(${PROJECT_NAME} SQLite::SQLite3)

