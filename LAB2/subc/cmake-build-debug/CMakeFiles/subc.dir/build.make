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
CMAKE_SOURCE_DIR = /home/andrew/Projects/COMP362/LAB2/subc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/andrew/Projects/COMP362/LAB2/subc/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/subc.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/subc.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/subc.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/subc.dir/flags.make

CMakeFiles/subc.dir/subc.c.o: CMakeFiles/subc.dir/flags.make
CMakeFiles/subc.dir/subc.c.o: ../subc.c
CMakeFiles/subc.dir/subc.c.o: CMakeFiles/subc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrew/Projects/COMP362/LAB2/subc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/subc.dir/subc.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/subc.dir/subc.c.o -MF CMakeFiles/subc.dir/subc.c.o.d -o CMakeFiles/subc.dir/subc.c.o -c /home/andrew/Projects/COMP362/LAB2/subc/subc.c

CMakeFiles/subc.dir/subc.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/subc.dir/subc.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/andrew/Projects/COMP362/LAB2/subc/subc.c > CMakeFiles/subc.dir/subc.c.i

CMakeFiles/subc.dir/subc.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/subc.dir/subc.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/andrew/Projects/COMP362/LAB2/subc/subc.c -o CMakeFiles/subc.dir/subc.c.s

# Object files for target subc
subc_OBJECTS = \
"CMakeFiles/subc.dir/subc.c.o"

# External object files for target subc
subc_EXTERNAL_OBJECTS =

subc: CMakeFiles/subc.dir/subc.c.o
subc: CMakeFiles/subc.dir/build.make
subc: CMakeFiles/subc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/andrew/Projects/COMP362/LAB2/subc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable subc"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/subc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/subc.dir/build: subc
.PHONY : CMakeFiles/subc.dir/build

CMakeFiles/subc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/subc.dir/cmake_clean.cmake
.PHONY : CMakeFiles/subc.dir/clean

CMakeFiles/subc.dir/depend:
	cd /home/andrew/Projects/COMP362/LAB2/subc/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andrew/Projects/COMP362/LAB2/subc /home/andrew/Projects/COMP362/LAB2/subc /home/andrew/Projects/COMP362/LAB2/subc/cmake-build-debug /home/andrew/Projects/COMP362/LAB2/subc/cmake-build-debug /home/andrew/Projects/COMP362/LAB2/subc/cmake-build-debug/CMakeFiles/subc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/subc.dir/depend
