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
CMAKE_SOURCE_DIR = /home/andrew/Projects/COMP362/Project02/cifs

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/andrew/Projects/COMP362/Project02/cifs/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/cifs.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/cifs.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/cifs.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cifs.dir/flags.make

CMakeFiles/cifs.dir/src/test_cifs.c.o: CMakeFiles/cifs.dir/flags.make
CMakeFiles/cifs.dir/src/test_cifs.c.o: ../src/test_cifs.c
CMakeFiles/cifs.dir/src/test_cifs.c.o: CMakeFiles/cifs.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrew/Projects/COMP362/Project02/cifs/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/cifs.dir/src/test_cifs.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/cifs.dir/src/test_cifs.c.o -MF CMakeFiles/cifs.dir/src/test_cifs.c.o.d -o CMakeFiles/cifs.dir/src/test_cifs.c.o -c /home/andrew/Projects/COMP362/Project02/cifs/src/test_cifs.c

CMakeFiles/cifs.dir/src/test_cifs.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cifs.dir/src/test_cifs.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/andrew/Projects/COMP362/Project02/cifs/src/test_cifs.c > CMakeFiles/cifs.dir/src/test_cifs.c.i

CMakeFiles/cifs.dir/src/test_cifs.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cifs.dir/src/test_cifs.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/andrew/Projects/COMP362/Project02/cifs/src/test_cifs.c -o CMakeFiles/cifs.dir/src/test_cifs.c.s

CMakeFiles/cifs.dir/src/cifs.c.o: CMakeFiles/cifs.dir/flags.make
CMakeFiles/cifs.dir/src/cifs.c.o: ../src/cifs.c
CMakeFiles/cifs.dir/src/cifs.c.o: CMakeFiles/cifs.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrew/Projects/COMP362/Project02/cifs/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/cifs.dir/src/cifs.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/cifs.dir/src/cifs.c.o -MF CMakeFiles/cifs.dir/src/cifs.c.o.d -o CMakeFiles/cifs.dir/src/cifs.c.o -c /home/andrew/Projects/COMP362/Project02/cifs/src/cifs.c

CMakeFiles/cifs.dir/src/cifs.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cifs.dir/src/cifs.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/andrew/Projects/COMP362/Project02/cifs/src/cifs.c > CMakeFiles/cifs.dir/src/cifs.c.i

CMakeFiles/cifs.dir/src/cifs.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cifs.dir/src/cifs.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/andrew/Projects/COMP362/Project02/cifs/src/cifs.c -o CMakeFiles/cifs.dir/src/cifs.c.s

# Object files for target cifs
cifs_OBJECTS = \
"CMakeFiles/cifs.dir/src/test_cifs.c.o" \
"CMakeFiles/cifs.dir/src/cifs.c.o"

# External object files for target cifs
cifs_EXTERNAL_OBJECTS =

bin/cifs: CMakeFiles/cifs.dir/src/test_cifs.c.o
bin/cifs: CMakeFiles/cifs.dir/src/cifs.c.o
bin/cifs: CMakeFiles/cifs.dir/build.make
bin/cifs: /usr/lib/x86_64-linux-gnu/libfuse.so
bin/cifs: CMakeFiles/cifs.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/andrew/Projects/COMP362/Project02/cifs/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable bin/cifs"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cifs.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cifs.dir/build: bin/cifs
.PHONY : CMakeFiles/cifs.dir/build

CMakeFiles/cifs.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cifs.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cifs.dir/clean

CMakeFiles/cifs.dir/depend:
	cd /home/andrew/Projects/COMP362/Project02/cifs/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andrew/Projects/COMP362/Project02/cifs /home/andrew/Projects/COMP362/Project02/cifs /home/andrew/Projects/COMP362/Project02/cifs/cmake-build-debug /home/andrew/Projects/COMP362/Project02/cifs/cmake-build-debug /home/andrew/Projects/COMP362/Project02/cifs/cmake-build-debug/CMakeFiles/cifs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cifs.dir/depend

