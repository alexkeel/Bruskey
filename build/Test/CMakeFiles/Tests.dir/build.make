# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alex/Bruskey

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alex/Bruskey/build

# Include any dependencies generated for this target.
include Test/CMakeFiles/Tests.dir/depend.make

# Include the progress variables for this target.
include Test/CMakeFiles/Tests.dir/progress.make

# Include the compile flags for this target's objects.
include Test/CMakeFiles/Tests.dir/flags.make

Test/CMakeFiles/Tests.dir/test_ArithmaticExpression.cpp.o: Test/CMakeFiles/Tests.dir/flags.make
Test/CMakeFiles/Tests.dir/test_ArithmaticExpression.cpp.o: ../Test/test_ArithmaticExpression.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/Bruskey/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Test/CMakeFiles/Tests.dir/test_ArithmaticExpression.cpp.o"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Tests.dir/test_ArithmaticExpression.cpp.o -c /home/alex/Bruskey/Test/test_ArithmaticExpression.cpp

Test/CMakeFiles/Tests.dir/test_ArithmaticExpression.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tests.dir/test_ArithmaticExpression.cpp.i"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alex/Bruskey/Test/test_ArithmaticExpression.cpp > CMakeFiles/Tests.dir/test_ArithmaticExpression.cpp.i

Test/CMakeFiles/Tests.dir/test_ArithmaticExpression.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tests.dir/test_ArithmaticExpression.cpp.s"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alex/Bruskey/Test/test_ArithmaticExpression.cpp -o CMakeFiles/Tests.dir/test_ArithmaticExpression.cpp.s

Test/CMakeFiles/Tests.dir/test_ArithmaticExpression.cpp.o.requires:

.PHONY : Test/CMakeFiles/Tests.dir/test_ArithmaticExpression.cpp.o.requires

Test/CMakeFiles/Tests.dir/test_ArithmaticExpression.cpp.o.provides: Test/CMakeFiles/Tests.dir/test_ArithmaticExpression.cpp.o.requires
	$(MAKE) -f Test/CMakeFiles/Tests.dir/build.make Test/CMakeFiles/Tests.dir/test_ArithmaticExpression.cpp.o.provides.build
.PHONY : Test/CMakeFiles/Tests.dir/test_ArithmaticExpression.cpp.o.provides

Test/CMakeFiles/Tests.dir/test_ArithmaticExpression.cpp.o.provides.build: Test/CMakeFiles/Tests.dir/test_ArithmaticExpression.cpp.o


Test/CMakeFiles/Tests.dir/test_BuiltInFunction.cpp.o: Test/CMakeFiles/Tests.dir/flags.make
Test/CMakeFiles/Tests.dir/test_BuiltInFunction.cpp.o: ../Test/test_BuiltInFunction.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/Bruskey/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object Test/CMakeFiles/Tests.dir/test_BuiltInFunction.cpp.o"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Tests.dir/test_BuiltInFunction.cpp.o -c /home/alex/Bruskey/Test/test_BuiltInFunction.cpp

Test/CMakeFiles/Tests.dir/test_BuiltInFunction.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tests.dir/test_BuiltInFunction.cpp.i"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alex/Bruskey/Test/test_BuiltInFunction.cpp > CMakeFiles/Tests.dir/test_BuiltInFunction.cpp.i

Test/CMakeFiles/Tests.dir/test_BuiltInFunction.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tests.dir/test_BuiltInFunction.cpp.s"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alex/Bruskey/Test/test_BuiltInFunction.cpp -o CMakeFiles/Tests.dir/test_BuiltInFunction.cpp.s

Test/CMakeFiles/Tests.dir/test_BuiltInFunction.cpp.o.requires:

.PHONY : Test/CMakeFiles/Tests.dir/test_BuiltInFunction.cpp.o.requires

Test/CMakeFiles/Tests.dir/test_BuiltInFunction.cpp.o.provides: Test/CMakeFiles/Tests.dir/test_BuiltInFunction.cpp.o.requires
	$(MAKE) -f Test/CMakeFiles/Tests.dir/build.make Test/CMakeFiles/Tests.dir/test_BuiltInFunction.cpp.o.provides.build
.PHONY : Test/CMakeFiles/Tests.dir/test_BuiltInFunction.cpp.o.provides

Test/CMakeFiles/Tests.dir/test_BuiltInFunction.cpp.o.provides.build: Test/CMakeFiles/Tests.dir/test_BuiltInFunction.cpp.o


Test/CMakeFiles/Tests.dir/test_IfStatement.cpp.o: Test/CMakeFiles/Tests.dir/flags.make
Test/CMakeFiles/Tests.dir/test_IfStatement.cpp.o: ../Test/test_IfStatement.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/Bruskey/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object Test/CMakeFiles/Tests.dir/test_IfStatement.cpp.o"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Tests.dir/test_IfStatement.cpp.o -c /home/alex/Bruskey/Test/test_IfStatement.cpp

Test/CMakeFiles/Tests.dir/test_IfStatement.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tests.dir/test_IfStatement.cpp.i"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alex/Bruskey/Test/test_IfStatement.cpp > CMakeFiles/Tests.dir/test_IfStatement.cpp.i

Test/CMakeFiles/Tests.dir/test_IfStatement.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tests.dir/test_IfStatement.cpp.s"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alex/Bruskey/Test/test_IfStatement.cpp -o CMakeFiles/Tests.dir/test_IfStatement.cpp.s

Test/CMakeFiles/Tests.dir/test_IfStatement.cpp.o.requires:

.PHONY : Test/CMakeFiles/Tests.dir/test_IfStatement.cpp.o.requires

Test/CMakeFiles/Tests.dir/test_IfStatement.cpp.o.provides: Test/CMakeFiles/Tests.dir/test_IfStatement.cpp.o.requires
	$(MAKE) -f Test/CMakeFiles/Tests.dir/build.make Test/CMakeFiles/Tests.dir/test_IfStatement.cpp.o.provides.build
.PHONY : Test/CMakeFiles/Tests.dir/test_IfStatement.cpp.o.provides

Test/CMakeFiles/Tests.dir/test_IfStatement.cpp.o.provides.build: Test/CMakeFiles/Tests.dir/test_IfStatement.cpp.o


Test/CMakeFiles/Tests.dir/test_Expression.cpp.o: Test/CMakeFiles/Tests.dir/flags.make
Test/CMakeFiles/Tests.dir/test_Expression.cpp.o: ../Test/test_Expression.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/Bruskey/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object Test/CMakeFiles/Tests.dir/test_Expression.cpp.o"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Tests.dir/test_Expression.cpp.o -c /home/alex/Bruskey/Test/test_Expression.cpp

Test/CMakeFiles/Tests.dir/test_Expression.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tests.dir/test_Expression.cpp.i"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alex/Bruskey/Test/test_Expression.cpp > CMakeFiles/Tests.dir/test_Expression.cpp.i

Test/CMakeFiles/Tests.dir/test_Expression.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tests.dir/test_Expression.cpp.s"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alex/Bruskey/Test/test_Expression.cpp -o CMakeFiles/Tests.dir/test_Expression.cpp.s

Test/CMakeFiles/Tests.dir/test_Expression.cpp.o.requires:

.PHONY : Test/CMakeFiles/Tests.dir/test_Expression.cpp.o.requires

Test/CMakeFiles/Tests.dir/test_Expression.cpp.o.provides: Test/CMakeFiles/Tests.dir/test_Expression.cpp.o.requires
	$(MAKE) -f Test/CMakeFiles/Tests.dir/build.make Test/CMakeFiles/Tests.dir/test_Expression.cpp.o.provides.build
.PHONY : Test/CMakeFiles/Tests.dir/test_Expression.cpp.o.provides

Test/CMakeFiles/Tests.dir/test_Expression.cpp.o.provides.build: Test/CMakeFiles/Tests.dir/test_Expression.cpp.o


Test/CMakeFiles/Tests.dir/test_ExpressionStatement.cpp.o: Test/CMakeFiles/Tests.dir/flags.make
Test/CMakeFiles/Tests.dir/test_ExpressionStatement.cpp.o: ../Test/test_ExpressionStatement.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/Bruskey/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object Test/CMakeFiles/Tests.dir/test_ExpressionStatement.cpp.o"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Tests.dir/test_ExpressionStatement.cpp.o -c /home/alex/Bruskey/Test/test_ExpressionStatement.cpp

Test/CMakeFiles/Tests.dir/test_ExpressionStatement.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tests.dir/test_ExpressionStatement.cpp.i"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alex/Bruskey/Test/test_ExpressionStatement.cpp > CMakeFiles/Tests.dir/test_ExpressionStatement.cpp.i

Test/CMakeFiles/Tests.dir/test_ExpressionStatement.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tests.dir/test_ExpressionStatement.cpp.s"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alex/Bruskey/Test/test_ExpressionStatement.cpp -o CMakeFiles/Tests.dir/test_ExpressionStatement.cpp.s

Test/CMakeFiles/Tests.dir/test_ExpressionStatement.cpp.o.requires:

.PHONY : Test/CMakeFiles/Tests.dir/test_ExpressionStatement.cpp.o.requires

Test/CMakeFiles/Tests.dir/test_ExpressionStatement.cpp.o.provides: Test/CMakeFiles/Tests.dir/test_ExpressionStatement.cpp.o.requires
	$(MAKE) -f Test/CMakeFiles/Tests.dir/build.make Test/CMakeFiles/Tests.dir/test_ExpressionStatement.cpp.o.provides.build
.PHONY : Test/CMakeFiles/Tests.dir/test_ExpressionStatement.cpp.o.provides

Test/CMakeFiles/Tests.dir/test_ExpressionStatement.cpp.o.provides.build: Test/CMakeFiles/Tests.dir/test_ExpressionStatement.cpp.o


Test/CMakeFiles/Tests.dir/test_FunctionCall.cpp.o: Test/CMakeFiles/Tests.dir/flags.make
Test/CMakeFiles/Tests.dir/test_FunctionCall.cpp.o: ../Test/test_FunctionCall.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/Bruskey/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object Test/CMakeFiles/Tests.dir/test_FunctionCall.cpp.o"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Tests.dir/test_FunctionCall.cpp.o -c /home/alex/Bruskey/Test/test_FunctionCall.cpp

Test/CMakeFiles/Tests.dir/test_FunctionCall.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tests.dir/test_FunctionCall.cpp.i"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alex/Bruskey/Test/test_FunctionCall.cpp > CMakeFiles/Tests.dir/test_FunctionCall.cpp.i

Test/CMakeFiles/Tests.dir/test_FunctionCall.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tests.dir/test_FunctionCall.cpp.s"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alex/Bruskey/Test/test_FunctionCall.cpp -o CMakeFiles/Tests.dir/test_FunctionCall.cpp.s

Test/CMakeFiles/Tests.dir/test_FunctionCall.cpp.o.requires:

.PHONY : Test/CMakeFiles/Tests.dir/test_FunctionCall.cpp.o.requires

Test/CMakeFiles/Tests.dir/test_FunctionCall.cpp.o.provides: Test/CMakeFiles/Tests.dir/test_FunctionCall.cpp.o.requires
	$(MAKE) -f Test/CMakeFiles/Tests.dir/build.make Test/CMakeFiles/Tests.dir/test_FunctionCall.cpp.o.provides.build
.PHONY : Test/CMakeFiles/Tests.dir/test_FunctionCall.cpp.o.provides

Test/CMakeFiles/Tests.dir/test_FunctionCall.cpp.o.provides.build: Test/CMakeFiles/Tests.dir/test_FunctionCall.cpp.o


Test/CMakeFiles/Tests.dir/test_Integer.cpp.o: Test/CMakeFiles/Tests.dir/flags.make
Test/CMakeFiles/Tests.dir/test_Integer.cpp.o: ../Test/test_Integer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/Bruskey/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object Test/CMakeFiles/Tests.dir/test_Integer.cpp.o"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Tests.dir/test_Integer.cpp.o -c /home/alex/Bruskey/Test/test_Integer.cpp

Test/CMakeFiles/Tests.dir/test_Integer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tests.dir/test_Integer.cpp.i"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alex/Bruskey/Test/test_Integer.cpp > CMakeFiles/Tests.dir/test_Integer.cpp.i

Test/CMakeFiles/Tests.dir/test_Integer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tests.dir/test_Integer.cpp.s"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alex/Bruskey/Test/test_Integer.cpp -o CMakeFiles/Tests.dir/test_Integer.cpp.s

Test/CMakeFiles/Tests.dir/test_Integer.cpp.o.requires:

.PHONY : Test/CMakeFiles/Tests.dir/test_Integer.cpp.o.requires

Test/CMakeFiles/Tests.dir/test_Integer.cpp.o.provides: Test/CMakeFiles/Tests.dir/test_Integer.cpp.o.requires
	$(MAKE) -f Test/CMakeFiles/Tests.dir/build.make Test/CMakeFiles/Tests.dir/test_Integer.cpp.o.provides.build
.PHONY : Test/CMakeFiles/Tests.dir/test_Integer.cpp.o.provides

Test/CMakeFiles/Tests.dir/test_Integer.cpp.o.provides.build: Test/CMakeFiles/Tests.dir/test_Integer.cpp.o


Test/CMakeFiles/Tests.dir/test_Identifier.cpp.o: Test/CMakeFiles/Tests.dir/flags.make
Test/CMakeFiles/Tests.dir/test_Identifier.cpp.o: ../Test/test_Identifier.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/Bruskey/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object Test/CMakeFiles/Tests.dir/test_Identifier.cpp.o"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Tests.dir/test_Identifier.cpp.o -c /home/alex/Bruskey/Test/test_Identifier.cpp

Test/CMakeFiles/Tests.dir/test_Identifier.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tests.dir/test_Identifier.cpp.i"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alex/Bruskey/Test/test_Identifier.cpp > CMakeFiles/Tests.dir/test_Identifier.cpp.i

Test/CMakeFiles/Tests.dir/test_Identifier.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tests.dir/test_Identifier.cpp.s"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alex/Bruskey/Test/test_Identifier.cpp -o CMakeFiles/Tests.dir/test_Identifier.cpp.s

Test/CMakeFiles/Tests.dir/test_Identifier.cpp.o.requires:

.PHONY : Test/CMakeFiles/Tests.dir/test_Identifier.cpp.o.requires

Test/CMakeFiles/Tests.dir/test_Identifier.cpp.o.provides: Test/CMakeFiles/Tests.dir/test_Identifier.cpp.o.requires
	$(MAKE) -f Test/CMakeFiles/Tests.dir/build.make Test/CMakeFiles/Tests.dir/test_Identifier.cpp.o.provides.build
.PHONY : Test/CMakeFiles/Tests.dir/test_Identifier.cpp.o.provides

Test/CMakeFiles/Tests.dir/test_Identifier.cpp.o.provides.build: Test/CMakeFiles/Tests.dir/test_Identifier.cpp.o


Test/CMakeFiles/Tests.dir/test_NotEqualsExpression.cpp.o: Test/CMakeFiles/Tests.dir/flags.make
Test/CMakeFiles/Tests.dir/test_NotEqualsExpression.cpp.o: ../Test/test_NotEqualsExpression.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/Bruskey/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object Test/CMakeFiles/Tests.dir/test_NotEqualsExpression.cpp.o"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Tests.dir/test_NotEqualsExpression.cpp.o -c /home/alex/Bruskey/Test/test_NotEqualsExpression.cpp

Test/CMakeFiles/Tests.dir/test_NotEqualsExpression.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tests.dir/test_NotEqualsExpression.cpp.i"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alex/Bruskey/Test/test_NotEqualsExpression.cpp > CMakeFiles/Tests.dir/test_NotEqualsExpression.cpp.i

Test/CMakeFiles/Tests.dir/test_NotEqualsExpression.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tests.dir/test_NotEqualsExpression.cpp.s"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alex/Bruskey/Test/test_NotEqualsExpression.cpp -o CMakeFiles/Tests.dir/test_NotEqualsExpression.cpp.s

Test/CMakeFiles/Tests.dir/test_NotEqualsExpression.cpp.o.requires:

.PHONY : Test/CMakeFiles/Tests.dir/test_NotEqualsExpression.cpp.o.requires

Test/CMakeFiles/Tests.dir/test_NotEqualsExpression.cpp.o.provides: Test/CMakeFiles/Tests.dir/test_NotEqualsExpression.cpp.o.requires
	$(MAKE) -f Test/CMakeFiles/Tests.dir/build.make Test/CMakeFiles/Tests.dir/test_NotEqualsExpression.cpp.o.provides.build
.PHONY : Test/CMakeFiles/Tests.dir/test_NotEqualsExpression.cpp.o.provides

Test/CMakeFiles/Tests.dir/test_NotEqualsExpression.cpp.o.provides.build: Test/CMakeFiles/Tests.dir/test_NotEqualsExpression.cpp.o


Test/CMakeFiles/Tests.dir/test_ParenthesesExpression.cpp.o: Test/CMakeFiles/Tests.dir/flags.make
Test/CMakeFiles/Tests.dir/test_ParenthesesExpression.cpp.o: ../Test/test_ParenthesesExpression.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/Bruskey/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object Test/CMakeFiles/Tests.dir/test_ParenthesesExpression.cpp.o"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Tests.dir/test_ParenthesesExpression.cpp.o -c /home/alex/Bruskey/Test/test_ParenthesesExpression.cpp

Test/CMakeFiles/Tests.dir/test_ParenthesesExpression.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tests.dir/test_ParenthesesExpression.cpp.i"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alex/Bruskey/Test/test_ParenthesesExpression.cpp > CMakeFiles/Tests.dir/test_ParenthesesExpression.cpp.i

Test/CMakeFiles/Tests.dir/test_ParenthesesExpression.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tests.dir/test_ParenthesesExpression.cpp.s"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alex/Bruskey/Test/test_ParenthesesExpression.cpp -o CMakeFiles/Tests.dir/test_ParenthesesExpression.cpp.s

Test/CMakeFiles/Tests.dir/test_ParenthesesExpression.cpp.o.requires:

.PHONY : Test/CMakeFiles/Tests.dir/test_ParenthesesExpression.cpp.o.requires

Test/CMakeFiles/Tests.dir/test_ParenthesesExpression.cpp.o.provides: Test/CMakeFiles/Tests.dir/test_ParenthesesExpression.cpp.o.requires
	$(MAKE) -f Test/CMakeFiles/Tests.dir/build.make Test/CMakeFiles/Tests.dir/test_ParenthesesExpression.cpp.o.provides.build
.PHONY : Test/CMakeFiles/Tests.dir/test_ParenthesesExpression.cpp.o.provides

Test/CMakeFiles/Tests.dir/test_ParenthesesExpression.cpp.o.provides.build: Test/CMakeFiles/Tests.dir/test_ParenthesesExpression.cpp.o


Test/CMakeFiles/Tests.dir/test_WhileStatement.cpp.o: Test/CMakeFiles/Tests.dir/flags.make
Test/CMakeFiles/Tests.dir/test_WhileStatement.cpp.o: ../Test/test_WhileStatement.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/Bruskey/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object Test/CMakeFiles/Tests.dir/test_WhileStatement.cpp.o"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Tests.dir/test_WhileStatement.cpp.o -c /home/alex/Bruskey/Test/test_WhileStatement.cpp

Test/CMakeFiles/Tests.dir/test_WhileStatement.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tests.dir/test_WhileStatement.cpp.i"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alex/Bruskey/Test/test_WhileStatement.cpp > CMakeFiles/Tests.dir/test_WhileStatement.cpp.i

Test/CMakeFiles/Tests.dir/test_WhileStatement.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tests.dir/test_WhileStatement.cpp.s"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alex/Bruskey/Test/test_WhileStatement.cpp -o CMakeFiles/Tests.dir/test_WhileStatement.cpp.s

Test/CMakeFiles/Tests.dir/test_WhileStatement.cpp.o.requires:

.PHONY : Test/CMakeFiles/Tests.dir/test_WhileStatement.cpp.o.requires

Test/CMakeFiles/Tests.dir/test_WhileStatement.cpp.o.provides: Test/CMakeFiles/Tests.dir/test_WhileStatement.cpp.o.requires
	$(MAKE) -f Test/CMakeFiles/Tests.dir/build.make Test/CMakeFiles/Tests.dir/test_WhileStatement.cpp.o.provides.build
.PHONY : Test/CMakeFiles/Tests.dir/test_WhileStatement.cpp.o.provides

Test/CMakeFiles/Tests.dir/test_WhileStatement.cpp.o.provides.build: Test/CMakeFiles/Tests.dir/test_WhileStatement.cpp.o


Test/CMakeFiles/Tests.dir/test_TranslationUnit.cpp.o: Test/CMakeFiles/Tests.dir/flags.make
Test/CMakeFiles/Tests.dir/test_TranslationUnit.cpp.o: ../Test/test_TranslationUnit.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/Bruskey/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object Test/CMakeFiles/Tests.dir/test_TranslationUnit.cpp.o"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Tests.dir/test_TranslationUnit.cpp.o -c /home/alex/Bruskey/Test/test_TranslationUnit.cpp

Test/CMakeFiles/Tests.dir/test_TranslationUnit.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tests.dir/test_TranslationUnit.cpp.i"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alex/Bruskey/Test/test_TranslationUnit.cpp > CMakeFiles/Tests.dir/test_TranslationUnit.cpp.i

Test/CMakeFiles/Tests.dir/test_TranslationUnit.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tests.dir/test_TranslationUnit.cpp.s"
	cd /home/alex/Bruskey/build/Test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alex/Bruskey/Test/test_TranslationUnit.cpp -o CMakeFiles/Tests.dir/test_TranslationUnit.cpp.s

Test/CMakeFiles/Tests.dir/test_TranslationUnit.cpp.o.requires:

.PHONY : Test/CMakeFiles/Tests.dir/test_TranslationUnit.cpp.o.requires

Test/CMakeFiles/Tests.dir/test_TranslationUnit.cpp.o.provides: Test/CMakeFiles/Tests.dir/test_TranslationUnit.cpp.o.requires
	$(MAKE) -f Test/CMakeFiles/Tests.dir/build.make Test/CMakeFiles/Tests.dir/test_TranslationUnit.cpp.o.provides.build
.PHONY : Test/CMakeFiles/Tests.dir/test_TranslationUnit.cpp.o.provides

Test/CMakeFiles/Tests.dir/test_TranslationUnit.cpp.o.provides.build: Test/CMakeFiles/Tests.dir/test_TranslationUnit.cpp.o


# Object files for target Tests
Tests_OBJECTS = \
"CMakeFiles/Tests.dir/test_ArithmaticExpression.cpp.o" \
"CMakeFiles/Tests.dir/test_BuiltInFunction.cpp.o" \
"CMakeFiles/Tests.dir/test_IfStatement.cpp.o" \
"CMakeFiles/Tests.dir/test_Expression.cpp.o" \
"CMakeFiles/Tests.dir/test_ExpressionStatement.cpp.o" \
"CMakeFiles/Tests.dir/test_FunctionCall.cpp.o" \
"CMakeFiles/Tests.dir/test_Integer.cpp.o" \
"CMakeFiles/Tests.dir/test_Identifier.cpp.o" \
"CMakeFiles/Tests.dir/test_NotEqualsExpression.cpp.o" \
"CMakeFiles/Tests.dir/test_ParenthesesExpression.cpp.o" \
"CMakeFiles/Tests.dir/test_WhileStatement.cpp.o" \
"CMakeFiles/Tests.dir/test_TranslationUnit.cpp.o"

# External object files for target Tests
Tests_EXTERNAL_OBJECTS =

Test/Tests: Test/CMakeFiles/Tests.dir/test_ArithmaticExpression.cpp.o
Test/Tests: Test/CMakeFiles/Tests.dir/test_BuiltInFunction.cpp.o
Test/Tests: Test/CMakeFiles/Tests.dir/test_IfStatement.cpp.o
Test/Tests: Test/CMakeFiles/Tests.dir/test_Expression.cpp.o
Test/Tests: Test/CMakeFiles/Tests.dir/test_ExpressionStatement.cpp.o
Test/Tests: Test/CMakeFiles/Tests.dir/test_FunctionCall.cpp.o
Test/Tests: Test/CMakeFiles/Tests.dir/test_Integer.cpp.o
Test/Tests: Test/CMakeFiles/Tests.dir/test_Identifier.cpp.o
Test/Tests: Test/CMakeFiles/Tests.dir/test_NotEqualsExpression.cpp.o
Test/Tests: Test/CMakeFiles/Tests.dir/test_ParenthesesExpression.cpp.o
Test/Tests: Test/CMakeFiles/Tests.dir/test_WhileStatement.cpp.o
Test/Tests: Test/CMakeFiles/Tests.dir/test_TranslationUnit.cpp.o
Test/Tests: Test/CMakeFiles/Tests.dir/build.make
Test/Tests: Components/SyntaxTree/libSyntaxTree.a
Test/Tests: Test/CMakeFiles/Tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alex/Bruskey/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX executable Tests"
	cd /home/alex/Bruskey/build/Test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Test/CMakeFiles/Tests.dir/build: Test/Tests

.PHONY : Test/CMakeFiles/Tests.dir/build

Test/CMakeFiles/Tests.dir/requires: Test/CMakeFiles/Tests.dir/test_ArithmaticExpression.cpp.o.requires
Test/CMakeFiles/Tests.dir/requires: Test/CMakeFiles/Tests.dir/test_BuiltInFunction.cpp.o.requires
Test/CMakeFiles/Tests.dir/requires: Test/CMakeFiles/Tests.dir/test_IfStatement.cpp.o.requires
Test/CMakeFiles/Tests.dir/requires: Test/CMakeFiles/Tests.dir/test_Expression.cpp.o.requires
Test/CMakeFiles/Tests.dir/requires: Test/CMakeFiles/Tests.dir/test_ExpressionStatement.cpp.o.requires
Test/CMakeFiles/Tests.dir/requires: Test/CMakeFiles/Tests.dir/test_FunctionCall.cpp.o.requires
Test/CMakeFiles/Tests.dir/requires: Test/CMakeFiles/Tests.dir/test_Integer.cpp.o.requires
Test/CMakeFiles/Tests.dir/requires: Test/CMakeFiles/Tests.dir/test_Identifier.cpp.o.requires
Test/CMakeFiles/Tests.dir/requires: Test/CMakeFiles/Tests.dir/test_NotEqualsExpression.cpp.o.requires
Test/CMakeFiles/Tests.dir/requires: Test/CMakeFiles/Tests.dir/test_ParenthesesExpression.cpp.o.requires
Test/CMakeFiles/Tests.dir/requires: Test/CMakeFiles/Tests.dir/test_WhileStatement.cpp.o.requires
Test/CMakeFiles/Tests.dir/requires: Test/CMakeFiles/Tests.dir/test_TranslationUnit.cpp.o.requires

.PHONY : Test/CMakeFiles/Tests.dir/requires

Test/CMakeFiles/Tests.dir/clean:
	cd /home/alex/Bruskey/build/Test && $(CMAKE_COMMAND) -P CMakeFiles/Tests.dir/cmake_clean.cmake
.PHONY : Test/CMakeFiles/Tests.dir/clean

Test/CMakeFiles/Tests.dir/depend:
	cd /home/alex/Bruskey/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alex/Bruskey /home/alex/Bruskey/Test /home/alex/Bruskey/build /home/alex/Bruskey/build/Test /home/alex/Bruskey/build/Test/CMakeFiles/Tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Test/CMakeFiles/Tests.dir/depend
