# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.11

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.11.0/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.11.0/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/euxcet/Files/tsinghua/大三下/计算机系统结构/homework/Tomasulo算法模拟器实验/tomasulo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/euxcet/Files/tsinghua/大三下/计算机系统结构/homework/Tomasulo算法模拟器实验/tomasulo/build

# Include any dependencies generated for this target.
include CMakeFiles/tomasulo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tomasulo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tomasulo.dir/flags.make

CMakeFiles/tomasulo.dir/src/core/parser.cpp.o: CMakeFiles/tomasulo.dir/flags.make
CMakeFiles/tomasulo.dir/src/core/parser.cpp.o: ../src/core/parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/euxcet/Files/tsinghua/大三下/计算机系统结构/homework/Tomasulo算法模拟器实验/tomasulo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tomasulo.dir/src/core/parser.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tomasulo.dir/src/core/parser.cpp.o -c /Users/euxcet/Files/tsinghua/大三下/计算机系统结构/homework/Tomasulo算法模拟器实验/tomasulo/src/core/parser.cpp

CMakeFiles/tomasulo.dir/src/core/parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tomasulo.dir/src/core/parser.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/euxcet/Files/tsinghua/大三下/计算机系统结构/homework/Tomasulo算法模拟器实验/tomasulo/src/core/parser.cpp > CMakeFiles/tomasulo.dir/src/core/parser.cpp.i

CMakeFiles/tomasulo.dir/src/core/parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tomasulo.dir/src/core/parser.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/euxcet/Files/tsinghua/大三下/计算机系统结构/homework/Tomasulo算法模拟器实验/tomasulo/src/core/parser.cpp -o CMakeFiles/tomasulo.dir/src/core/parser.cpp.s

CMakeFiles/tomasulo.dir/src/core/tomasulo.cpp.o: CMakeFiles/tomasulo.dir/flags.make
CMakeFiles/tomasulo.dir/src/core/tomasulo.cpp.o: ../src/core/tomasulo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/euxcet/Files/tsinghua/大三下/计算机系统结构/homework/Tomasulo算法模拟器实验/tomasulo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/tomasulo.dir/src/core/tomasulo.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tomasulo.dir/src/core/tomasulo.cpp.o -c /Users/euxcet/Files/tsinghua/大三下/计算机系统结构/homework/Tomasulo算法模拟器实验/tomasulo/src/core/tomasulo.cpp

CMakeFiles/tomasulo.dir/src/core/tomasulo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tomasulo.dir/src/core/tomasulo.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/euxcet/Files/tsinghua/大三下/计算机系统结构/homework/Tomasulo算法模拟器实验/tomasulo/src/core/tomasulo.cpp > CMakeFiles/tomasulo.dir/src/core/tomasulo.cpp.i

CMakeFiles/tomasulo.dir/src/core/tomasulo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tomasulo.dir/src/core/tomasulo.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/euxcet/Files/tsinghua/大三下/计算机系统结构/homework/Tomasulo算法模拟器实验/tomasulo/src/core/tomasulo.cpp -o CMakeFiles/tomasulo.dir/src/core/tomasulo.cpp.s

# Object files for target tomasulo
tomasulo_OBJECTS = \
"CMakeFiles/tomasulo.dir/src/core/parser.cpp.o" \
"CMakeFiles/tomasulo.dir/src/core/tomasulo.cpp.o"

# External object files for target tomasulo
tomasulo_EXTERNAL_OBJECTS =

libtomasulo.a: CMakeFiles/tomasulo.dir/src/core/parser.cpp.o
libtomasulo.a: CMakeFiles/tomasulo.dir/src/core/tomasulo.cpp.o
libtomasulo.a: CMakeFiles/tomasulo.dir/build.make
libtomasulo.a: CMakeFiles/tomasulo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/euxcet/Files/tsinghua/大三下/计算机系统结构/homework/Tomasulo算法模拟器实验/tomasulo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libtomasulo.a"
	$(CMAKE_COMMAND) -P CMakeFiles/tomasulo.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tomasulo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tomasulo.dir/build: libtomasulo.a

.PHONY : CMakeFiles/tomasulo.dir/build

CMakeFiles/tomasulo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tomasulo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tomasulo.dir/clean

CMakeFiles/tomasulo.dir/depend:
	cd /Users/euxcet/Files/tsinghua/大三下/计算机系统结构/homework/Tomasulo算法模拟器实验/tomasulo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/euxcet/Files/tsinghua/大三下/计算机系统结构/homework/Tomasulo算法模拟器实验/tomasulo /Users/euxcet/Files/tsinghua/大三下/计算机系统结构/homework/Tomasulo算法模拟器实验/tomasulo /Users/euxcet/Files/tsinghua/大三下/计算机系统结构/homework/Tomasulo算法模拟器实验/tomasulo/build /Users/euxcet/Files/tsinghua/大三下/计算机系统结构/homework/Tomasulo算法模拟器实验/tomasulo/build /Users/euxcet/Files/tsinghua/大三下/计算机系统结构/homework/Tomasulo算法模拟器实验/tomasulo/build/CMakeFiles/tomasulo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tomasulo.dir/depend

