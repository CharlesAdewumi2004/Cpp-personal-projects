cmake_minimum_required(VERSION 3.11)  # Ensure CMake version is at least 3.11
project(FitnessYTracker VERSION 1.0)  # Replace 'YourProjectName' with your actual project name

set(CMAKE_CXX_STANDARD 11)  # Set C++ standard to C++11
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the FetchContent module
include(FetchContent)

# Declare SQLiteCpp as a content to fetch
FetchContent_Declare(
  sqlitecpp
  GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp.git
  GIT_TAG        origin/master  # You can specify a specific commit, tag, or branch
)

# Make the SQLiteCpp content available for building
FetchContent_MakeAvailable(sqlitecpp)

# Define your executable
add_executable(${PROJECT_NAME} main.cpp)  # Replace 'main.cpp' with the actual source files of your project

# Link SQLiteCpp with your executable
target_link_libraries(${PROJECT_NAME} SQLiteCpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${sqlitecpp_SOURCE_DIR}/include)

