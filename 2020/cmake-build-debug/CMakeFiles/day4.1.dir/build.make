# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.19

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
CMAKE_COMMAND = /home/borysmn/.distrib/clion/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/borysmn/.distrib/clion/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/borysmn/Proj/AdventCalendar/2020

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/borysmn/Proj/AdventCalendar/2020/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/day4.1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/day4.1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/day4.1.dir/flags.make

CMakeFiles/day4.1.dir/day4.1.c.o: CMakeFiles/day4.1.dir/flags.make
CMakeFiles/day4.1.dir/day4.1.c.o: ../day4.1.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/borysmn/Proj/AdventCalendar/2020/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/day4.1.dir/day4.1.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/day4.1.dir/day4.1.c.o -c /home/borysmn/Proj/AdventCalendar/2020/day4.1.c

CMakeFiles/day4.1.dir/day4.1.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/day4.1.dir/day4.1.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/borysmn/Proj/AdventCalendar/2020/day4.1.c > CMakeFiles/day4.1.dir/day4.1.c.i

CMakeFiles/day4.1.dir/day4.1.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/day4.1.dir/day4.1.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/borysmn/Proj/AdventCalendar/2020/day4.1.c -o CMakeFiles/day4.1.dir/day4.1.c.s

# Object files for target day4.1
day4_1_OBJECTS = \
"CMakeFiles/day4.1.dir/day4.1.c.o"

# External object files for target day4.1
day4_1_EXTERNAL_OBJECTS =

day4.1: CMakeFiles/day4.1.dir/day4.1.c.o
day4.1: CMakeFiles/day4.1.dir/build.make
day4.1: CMakeFiles/day4.1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/borysmn/Proj/AdventCalendar/2020/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable day4.1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/day4.1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/day4.1.dir/build: day4.1

.PHONY : CMakeFiles/day4.1.dir/build

CMakeFiles/day4.1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/day4.1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/day4.1.dir/clean

CMakeFiles/day4.1.dir/depend:
	cd /home/borysmn/Proj/AdventCalendar/2020/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/borysmn/Proj/AdventCalendar/2020 /home/borysmn/Proj/AdventCalendar/2020 /home/borysmn/Proj/AdventCalendar/2020/cmake-build-debug /home/borysmn/Proj/AdventCalendar/2020/cmake-build-debug /home/borysmn/Proj/AdventCalendar/2020/cmake-build-debug/CMakeFiles/day4.1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/day4.1.dir/depend

