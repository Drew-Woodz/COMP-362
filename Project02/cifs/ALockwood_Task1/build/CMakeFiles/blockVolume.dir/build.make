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
CMAKE_BINARY_DIR = /home/andrew/Projects/COMP362/Project02/cifs/build

# Include any dependencies generated for this target.
include CMakeFiles/blockVolume.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/blockVolume.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/blockVolume.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/blockVolume.dir/flags.make

CMakeFiles/blockVolume.dir/src/blockVolume.c.o: CMakeFiles/blockVolume.dir/flags.make
CMakeFiles/blockVolume.dir/src/blockVolume.c.o: ../src/blockVolume.c
CMakeFiles/blockVolume.dir/src/blockVolume.c.o: CMakeFiles/blockVolume.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/andrew/Projects/COMP362/Project02/cifs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/blockVolume.dir/src/blockVolume.c.o"
	/usr/bin/c89-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/blockVolume.dir/src/blockVolume.c.o -MF CMakeFiles/blockVolume.dir/src/blockVolume.c.o.d -o CMakeFiles/blockVolume.dir/src/blockVolume.c.o -c /home/andrew/Projects/COMP362/Project02/cifs/src/blockVolume.c

CMakeFiles/blockVolume.dir/src/blockVolume.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/blockVolume.dir/src/blockVolume.c.i"
	/usr/bin/c89-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/andrew/Projects/COMP362/Project02/cifs/src/blockVolume.c > CMakeFiles/blockVolume.dir/src/blockVolume.c.i

CMakeFiles/blockVolume.dir/src/blockVolume.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/blockVolume.dir/src/blockVolume.c.s"
	/usr/bin/c89-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/andrew/Projects/COMP362/Project02/cifs/src/blockVolume.c -o CMakeFiles/blockVolume.dir/src/blockVolume.c.s

# Object files for target blockVolume
blockVolume_OBJECTS = \
"CMakeFiles/blockVolume.dir/src/blockVolume.c.o"

# External object files for target blockVolume
blockVolume_EXTERNAL_OBJECTS =

bin/blockVolume: CMakeFiles/blockVolume.dir/src/blockVolume.c.o
bin/blockVolume: CMakeFiles/blockVolume.dir/build.make
bin/blockVolume: CMakeFiles/blockVolume.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/andrew/Projects/COMP362/Project02/cifs/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable bin/blockVolume"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/blockVolume.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/blockVolume.dir/build: bin/blockVolume
.PHONY : CMakeFiles/blockVolume.dir/build

CMakeFiles/blockVolume.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/blockVolume.dir/cmake_clean.cmake
.PHONY : CMakeFiles/blockVolume.dir/clean

CMakeFiles/blockVolume.dir/depend:
	cd /home/andrew/Projects/COMP362/Project02/cifs/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/andrew/Projects/COMP362/Project02/cifs /home/andrew/Projects/COMP362/Project02/cifs /home/andrew/Projects/COMP362/Project02/cifs/build /home/andrew/Projects/COMP362/Project02/cifs/build /home/andrew/Projects/COMP362/Project02/cifs/build/CMakeFiles/blockVolume.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/blockVolume.dir/depend

