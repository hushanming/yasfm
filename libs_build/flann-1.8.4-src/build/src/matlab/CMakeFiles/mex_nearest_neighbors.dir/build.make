# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.1

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files (x86)\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files (x86)\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Filip\Workspace\cmp\EAST_libs_build\flann-1.8.4-src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Filip\Workspace\cmp\EAST_libs_build\flann-1.8.4-src\build

# Utility rule file for mex_nearest_neighbors.

# Include the progress variables for this target.
include src\matlab\CMakeFiles\mex_nearest_neighbors.dir\progress.make

src\matlab\CMakeFiles\mex_nearest_neighbors: src\matlab\nearest_neighbors.mexw64
	cd C:\Users\Filip\Workspace\cmp\EAST_libs_build\flann-1.8.4-src\build\src\matlab
	cd C:\Users\Filip\Workspace\cmp\EAST_libs_build\flann-1.8.4-src\build

src\matlab\nearest_neighbors.mexw64: lib\flann_s.lib
src\matlab\nearest_neighbors.mexw64: ..\src\matlab\nearest_neighbors.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\Filip\Workspace\cmp\EAST_libs_build\flann-1.8.4-src\build\CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Building MEX extension C:/Users/Filip/Workspace/cmp/EAST_libs_build/flann-1.8.4-src/build/src/matlab/nearest_neighbors.mexw64"
	cd C:\Users\Filip\Workspace\cmp\EAST_libs_build\flann-1.8.4-src\build\src\matlab
	call "C:\Program Files\MATLAB\R2014b\bin\mex.bat" C:/Users/Filip/Workspace/cmp/EAST_libs_build/flann-1.8.4-src/src/matlab/nearest_neighbors.cpp -IC:/Users/Filip/Workspace/cmp/EAST_libs_build/flann-1.8.4-src/src/cpp -LC:/Users/Filip/Workspace/cmp/EAST_libs_build/flann-1.8.4-src/build/lib -lflann_s COMPFLAGS="$$COMPFLAGS /openmp" LINKFLAGS="$$LINKFLAGS /openmp "
	cd C:\Users\Filip\Workspace\cmp\EAST_libs_build\flann-1.8.4-src\build

mex_nearest_neighbors: src\matlab\CMakeFiles\mex_nearest_neighbors
mex_nearest_neighbors: src\matlab\nearest_neighbors.mexw64
mex_nearest_neighbors: src\matlab\CMakeFiles\mex_nearest_neighbors.dir\build.make
.PHONY : mex_nearest_neighbors

# Rule to build all files generated by this target.
src\matlab\CMakeFiles\mex_nearest_neighbors.dir\build: mex_nearest_neighbors
.PHONY : src\matlab\CMakeFiles\mex_nearest_neighbors.dir\build

src\matlab\CMakeFiles\mex_nearest_neighbors.dir\clean:
	cd C:\Users\Filip\Workspace\cmp\EAST_libs_build\flann-1.8.4-src\build\src\matlab
	$(CMAKE_COMMAND) -P CMakeFiles\mex_nearest_neighbors.dir\cmake_clean.cmake
	cd C:\Users\Filip\Workspace\cmp\EAST_libs_build\flann-1.8.4-src\build
.PHONY : src\matlab\CMakeFiles\mex_nearest_neighbors.dir\clean

src\matlab\CMakeFiles\mex_nearest_neighbors.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\Filip\Workspace\cmp\EAST_libs_build\flann-1.8.4-src C:\Users\Filip\Workspace\cmp\EAST_libs_build\flann-1.8.4-src\src\matlab C:\Users\Filip\Workspace\cmp\EAST_libs_build\flann-1.8.4-src\build C:\Users\Filip\Workspace\cmp\EAST_libs_build\flann-1.8.4-src\build\src\matlab C:\Users\Filip\Workspace\cmp\EAST_libs_build\flann-1.8.4-src\build\src\matlab\CMakeFiles\mex_nearest_neighbors.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : src\matlab\CMakeFiles\mex_nearest_neighbors.dir\depend

