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
CMAKE_SOURCE_DIR = "/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week6/assignment_05"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week6/assignment_05/build"

# Include any dependencies generated for this target.
include tests/CMakeFiles/tests_algos.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/tests_algos.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/tests_algos.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/tests_algos.dir/flags.make

tests/CMakeFiles/tests_algos.dir/algo_tests.cpp.o: tests/CMakeFiles/tests_algos.dir/flags.make
tests/CMakeFiles/tests_algos.dir/algo_tests.cpp.o: ../tests/algo_tests.cpp
tests/CMakeFiles/tests_algos.dir/algo_tests.cpp.o: tests/CMakeFiles/tests_algos.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week6/assignment_05/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/tests_algos.dir/algo_tests.cpp.o"
	cd "/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week6/assignment_05/build/tests" && /usr/bin/clang++-18 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/tests_algos.dir/algo_tests.cpp.o -MF CMakeFiles/tests_algos.dir/algo_tests.cpp.o.d -o CMakeFiles/tests_algos.dir/algo_tests.cpp.o -c "/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week6/assignment_05/tests/algo_tests.cpp"

tests/CMakeFiles/tests_algos.dir/algo_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tests_algos.dir/algo_tests.cpp.i"
	cd "/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week6/assignment_05/build/tests" && /usr/bin/clang++-18 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week6/assignment_05/tests/algo_tests.cpp" > CMakeFiles/tests_algos.dir/algo_tests.cpp.i

tests/CMakeFiles/tests_algos.dir/algo_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tests_algos.dir/algo_tests.cpp.s"
	cd "/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week6/assignment_05/build/tests" && /usr/bin/clang++-18 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week6/assignment_05/tests/algo_tests.cpp" -o CMakeFiles/tests_algos.dir/algo_tests.cpp.s

tests/CMakeFiles/tests_algos.dir/test_runner.cpp.o: tests/CMakeFiles/tests_algos.dir/flags.make
tests/CMakeFiles/tests_algos.dir/test_runner.cpp.o: ../tests/test_runner.cpp
tests/CMakeFiles/tests_algos.dir/test_runner.cpp.o: tests/CMakeFiles/tests_algos.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week6/assignment_05/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object tests/CMakeFiles/tests_algos.dir/test_runner.cpp.o"
	cd "/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week6/assignment_05/build/tests" && /usr/bin/clang++-18 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/tests_algos.dir/test_runner.cpp.o -MF CMakeFiles/tests_algos.dir/test_runner.cpp.o.d -o CMakeFiles/tests_algos.dir/test_runner.cpp.o -c "/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week6/assignment_05/tests/test_runner.cpp"

tests/CMakeFiles/tests_algos.dir/test_runner.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tests_algos.dir/test_runner.cpp.i"
	cd "/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week6/assignment_05/build/tests" && /usr/bin/clang++-18 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week6/assignment_05/tests/test_runner.cpp" > CMakeFiles/tests_algos.dir/test_runner.cpp.i

tests/CMakeFiles/tests_algos.dir/test_runner.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tests_algos.dir/test_runner.cpp.s"
	cd "/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week6/assignment_05/build/tests" && /usr/bin/clang++-18 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week6/assignment_05/tests/test_runner.cpp" -o CMakeFiles/tests_algos.dir/test_runner.cpp.s

# Object files for target tests_algos
tests_algos_OBJECTS = \
"CMakeFiles/tests_algos.dir/algo_tests.cpp.o" \
"CMakeFiles/tests_algos.dir/test_runner.cpp.o"

# External object files for target tests_algos
tests_algos_EXTERNAL_OBJECTS =

tests/tests_algos: tests/CMakeFiles/tests_algos.dir/algo_tests.cpp.o
tests/tests_algos: tests/CMakeFiles/tests_algos.dir/test_runner.cpp.o
tests/tests_algos: tests/CMakeFiles/tests_algos.dir/build.make
tests/tests_algos: lib/libgtest.a
tests/tests_algos: lib/libgmock.a
tests/tests_algos: lib/libgtest.a
tests/tests_algos: tests/CMakeFiles/tests_algos.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week6/assignment_05/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable tests_algos"
	cd "/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week6/assignment_05/build/tests" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tests_algos.dir/link.txt --verbose=$(VERBOSE)
	cd "/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week6/assignment_05/build/tests" && /usr/bin/cmake -D TEST_TARGET=tests_algos -D "TEST_EXECUTABLE=/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week6/assignment_05/build/tests/tests_algos" -D TEST_EXECUTOR= -D "TEST_WORKING_DIR=/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week6/assignment_05/build/tests" -D TEST_EXTRA_ARGS= -D TEST_PROPERTIES= -D TEST_PREFIX= -D TEST_SUFFIX= -D TEST_FILTER= -D NO_PRETTY_TYPES=FALSE -D NO_PRETTY_VALUES=FALSE -D TEST_LIST=tests_algos_TESTS -D "CTEST_FILE=/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week6/assignment_05/build/tests/tests_algos[1]_tests.cmake" -D TEST_DISCOVERY_TIMEOUT=5 -D TEST_XML_OUTPUT_DIR= -P /usr/share/cmake-3.22/Modules/GoogleTestAddTests.cmake

# Rule to build all files generated by this target.
tests/CMakeFiles/tests_algos.dir/build: tests/tests_algos
.PHONY : tests/CMakeFiles/tests_algos.dir/build

tests/CMakeFiles/tests_algos.dir/clean:
	cd "/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week6/assignment_05/build/tests" && $(CMAKE_COMMAND) -P CMakeFiles/tests_algos.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/tests_algos.dir/clean

tests/CMakeFiles/tests_algos.dir/depend:
	cd "/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week6/assignment_05/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week6/assignment_05" "/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week6/assignment_05/tests" "/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week6/assignment_05/build" "/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week6/assignment_05/build/tests" "/mnt/c/Uni Year 2/AdvancedProgrammingConcepts/Week6/assignment_05/build/tests/CMakeFiles/tests_algos.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : tests/CMakeFiles/tests_algos.dir/depend

