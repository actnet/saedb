# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yecao/newsae/sae/saedb

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yecao/newsae/sae/saedb/build

# Include any dependencies generated for this target.
include computing/CMakeFiles/computing.dir/depend.make

# Include the progress variables for this target.
include computing/CMakeFiles/computing.dir/progress.make

# Include the compile flags for this target's objects.
include computing/CMakeFiles/computing.dir/flags.make

computing/CMakeFiles/computing.dir/dumb.cpp.o: computing/CMakeFiles/computing.dir/flags.make
computing/CMakeFiles/computing.dir/dumb.cpp.o: ../computing/dumb.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/yecao/newsae/sae/saedb/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object computing/CMakeFiles/computing.dir/dumb.cpp.o"
	cd /home/yecao/newsae/sae/saedb/build/computing && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/computing.dir/dumb.cpp.o -c /home/yecao/newsae/sae/saedb/computing/dumb.cpp

computing/CMakeFiles/computing.dir/dumb.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/computing.dir/dumb.cpp.i"
	cd /home/yecao/newsae/sae/saedb/build/computing && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/yecao/newsae/sae/saedb/computing/dumb.cpp > CMakeFiles/computing.dir/dumb.cpp.i

computing/CMakeFiles/computing.dir/dumb.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/computing.dir/dumb.cpp.s"
	cd /home/yecao/newsae/sae/saedb/build/computing && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/yecao/newsae/sae/saedb/computing/dumb.cpp -o CMakeFiles/computing.dir/dumb.cpp.s

computing/CMakeFiles/computing.dir/dumb.cpp.o.requires:
.PHONY : computing/CMakeFiles/computing.dir/dumb.cpp.o.requires

computing/CMakeFiles/computing.dir/dumb.cpp.o.provides: computing/CMakeFiles/computing.dir/dumb.cpp.o.requires
	$(MAKE) -f computing/CMakeFiles/computing.dir/build.make computing/CMakeFiles/computing.dir/dumb.cpp.o.provides.build
.PHONY : computing/CMakeFiles/computing.dir/dumb.cpp.o.provides

computing/CMakeFiles/computing.dir/dumb.cpp.o.provides.build: computing/CMakeFiles/computing.dir/dumb.cpp.o

# Object files for target computing
computing_OBJECTS = \
"CMakeFiles/computing.dir/dumb.cpp.o"

# External object files for target computing
computing_EXTERNAL_OBJECTS =

computing/libcomputing.a: computing/CMakeFiles/computing.dir/dumb.cpp.o
computing/libcomputing.a: computing/CMakeFiles/computing.dir/build.make
computing/libcomputing.a: computing/CMakeFiles/computing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX static library libcomputing.a"
	cd /home/yecao/newsae/sae/saedb/build/computing && $(CMAKE_COMMAND) -P CMakeFiles/computing.dir/cmake_clean_target.cmake
	cd /home/yecao/newsae/sae/saedb/build/computing && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/computing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
computing/CMakeFiles/computing.dir/build: computing/libcomputing.a
.PHONY : computing/CMakeFiles/computing.dir/build

computing/CMakeFiles/computing.dir/requires: computing/CMakeFiles/computing.dir/dumb.cpp.o.requires
.PHONY : computing/CMakeFiles/computing.dir/requires

computing/CMakeFiles/computing.dir/clean:
	cd /home/yecao/newsae/sae/saedb/build/computing && $(CMAKE_COMMAND) -P CMakeFiles/computing.dir/cmake_clean.cmake
.PHONY : computing/CMakeFiles/computing.dir/clean

computing/CMakeFiles/computing.dir/depend:
	cd /home/yecao/newsae/sae/saedb/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yecao/newsae/sae/saedb /home/yecao/newsae/sae/saedb/computing /home/yecao/newsae/sae/saedb/build /home/yecao/newsae/sae/saedb/build/computing /home/yecao/newsae/sae/saedb/build/computing/CMakeFiles/computing.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : computing/CMakeFiles/computing.dir/depend

