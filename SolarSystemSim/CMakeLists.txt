cmake_minimum_required(VERSION 3.10)
project(SolarSystemSim)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Find GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

# Find Assimp
find_package(PkgConfig REQUIRED)
pkg_search_module(ASSIMP REQUIRED assimp)
if (ASSIMP_FOUND)
    include_directories(${ASSIMP_INCLUDE_DIRS})
    link_directories(${ASSIMP_LIBRARY_DIRS})
else()
    message(SEND_ERROR "Assimp not found")
endif()

# Add the executable
add_executable(MyGraphicsProgram solarSystemSim.cpp)

# Link the libraries to the executable
target_link_libraries(MyGraphicsProgram ${SDL2_LIBRARIES} ${GLEW_LIBRARIES} ${ASSIMP_LIBRARIES} GL dl)

