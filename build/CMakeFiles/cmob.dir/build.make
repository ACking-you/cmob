# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.22

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "D:\CLion Project\cmob"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:\CLion Project\cmob\build"

# Include any dependencies generated for this target.
include CMakeFiles/cmob.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/cmob.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/cmob.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cmob.dir/flags.make

CMakeFiles/cmob.dir/main.cpp.obj: CMakeFiles/cmob.dir/flags.make
CMakeFiles/cmob.dir/main.cpp.obj: CMakeFiles/cmob.dir/includes_CXX.rsp
CMakeFiles/cmob.dir/main.cpp.obj: ../main.cpp
CMakeFiles/cmob.dir/main.cpp.obj: CMakeFiles/cmob.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\CLion Project\cmob\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cmob.dir/main.cpp.obj"
	D:\Qt6\Tools\mingw900_64\bin\x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cmob.dir/main.cpp.obj -MF CMakeFiles\cmob.dir\main.cpp.obj.d -o CMakeFiles\cmob.dir\main.cpp.obj -c "D:\CLion Project\cmob\main.cpp"

CMakeFiles/cmob.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cmob.dir/main.cpp.i"
	D:\Qt6\Tools\mingw900_64\bin\x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\CLion Project\cmob\main.cpp" > CMakeFiles\cmob.dir\main.cpp.i

CMakeFiles/cmob.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cmob.dir/main.cpp.s"
	D:\Qt6\Tools\mingw900_64\bin\x86_64-w64-mingw32-g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\CLion Project\cmob\main.cpp" -o CMakeFiles\cmob.dir\main.cpp.s

# Object files for target cmob
cmob_OBJECTS = \
"CMakeFiles/cmob.dir/main.cpp.obj"

# External object files for target cmob
cmob_EXTERNAL_OBJECTS =

cmob.exe: CMakeFiles/cmob.dir/main.cpp.obj
cmob.exe: CMakeFiles/cmob.dir/build.make
cmob.exe: D:/vcpkg/vcpkg/packages/glog_x64-mingw-static/debug/lib/libglog.a
cmob.exe: D:/vcpkg/vcpkg/packages/gflags_x64-mingw-static/debug/lib/libgflags_static_debug.a
cmob.exe: CMakeFiles/cmob.dir/linklibs.rsp
cmob.exe: CMakeFiles/cmob.dir/objects1.rsp
cmob.exe: CMakeFiles/cmob.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="D:\CLion Project\cmob\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable cmob.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\cmob.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cmob.dir/build: cmob.exe
.PHONY : CMakeFiles/cmob.dir/build

CMakeFiles/cmob.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\cmob.dir\cmake_clean.cmake
.PHONY : CMakeFiles/cmob.dir/clean

CMakeFiles/cmob.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\CLion Project\cmob" "D:\CLion Project\cmob" "D:\CLion Project\cmob\build" "D:\CLion Project\cmob\build" "D:\CLion Project\cmob\build\CMakeFiles\cmob.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/cmob.dir/depend
