# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/charlie/Cpp-personal-projects/SolarSystemSim

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/charlie/Cpp-personal-projects/SolarSystemSim/build

# Include any dependencies generated for this target.
include CMakeFiles/MyGraphicsProgram.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MyGraphicsProgram.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MyGraphicsProgram.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MyGraphicsProgram.dir/flags.make

CMakeFiles/MyGraphicsProgram.dir/solarSystemSim.cpp.o: CMakeFiles/MyGraphicsProgram.dir/flags.make
CMakeFiles/MyGraphicsProgram.dir/solarSystemSim.cpp.o: ../solarSystemSim.cpp
CMakeFiles/MyGraphicsProgram.dir/solarSystemSim.cpp.o: CMakeFiles/MyGraphicsProgram.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/charlie/Cpp-personal-projects/SolarSystemSim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MyGraphicsProgram.dir/solarSystemSim.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MyGraphicsProgram.dir/solarSystemSim.cpp.o -MF CMakeFiles/MyGraphicsProgram.dir/solarSystemSim.cpp.o.d -o CMakeFiles/MyGraphicsProgram.dir/solarSystemSim.cpp.o -c /home/charlie/Cpp-personal-projects/SolarSystemSim/solarSystemSim.cpp

CMakeFiles/MyGraphicsProgram.dir/solarSystemSim.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyGraphicsProgram.dir/solarSystemSim.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/charlie/Cpp-personal-projects/SolarSystemSim/solarSystemSim.cpp > CMakeFiles/MyGraphicsProgram.dir/solarSystemSim.cpp.i

CMakeFiles/MyGraphicsProgram.dir/solarSystemSim.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyGraphicsProgram.dir/solarSystemSim.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/charlie/Cpp-personal-projects/SolarSystemSim/solarSystemSim.cpp -o CMakeFiles/MyGraphicsProgram.dir/solarSystemSim.cpp.s

# Object files for target MyGraphicsProgram
MyGraphicsProgram_OBJECTS = \
"CMakeFiles/MyGraphicsProgram.dir/solarSystemSim.cpp.o"

# External object files for target MyGraphicsProgram
MyGraphicsProgram_EXTERNAL_OBJECTS =

MyGraphicsProgram: CMakeFiles/MyGraphicsProgram.dir/solarSystemSim.cpp.o
MyGraphicsProgram: CMakeFiles/MyGraphicsProgram.dir/build.make
MyGraphicsProgram: /usr/lib/x86_64-linux-gnu/libGLEW.so
MyGraphicsProgram: CMakeFiles/MyGraphicsProgram.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/charlie/Cpp-personal-projects/SolarSystemSim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable MyGraphicsProgram"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MyGraphicsProgram.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MyGraphicsProgram.dir/build: MyGraphicsProgram
.PHONY : CMakeFiles/MyGraphicsProgram.dir/build

CMakeFiles/MyGraphicsProgram.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MyGraphicsProgram.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MyGraphicsProgram.dir/clean

CMakeFiles/MyGraphicsProgram.dir/depend:
	cd /home/charlie/Cpp-personal-projects/SolarSystemSim/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/charlie/Cpp-personal-projects/SolarSystemSim /home/charlie/Cpp-personal-projects/SolarSystemSim /home/charlie/Cpp-personal-projects/SolarSystemSim/build /home/charlie/Cpp-personal-projects/SolarSystemSim/build /home/charlie/Cpp-personal-projects/SolarSystemSim/build/CMakeFiles/MyGraphicsProgram.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MyGraphicsProgram.dir/depend

