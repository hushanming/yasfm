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

# Include any dependencies generated for this target.
include examples\CMakeFiles\flann_example_c.dir\depend.make

# Include the progress variables for this target.
include examples\CMakeFiles\flann_example_c.dir\progress.make

# Include the compile flags for this target's objects.
include examples\CMakeFiles\flann_example_c.dir\flags.make

examples\CMakeFiles\flann_example_c.dir\flann_example.c.obj: examples\CMakeFiles\flann_example_c.dir\flags.make
examples\CMakeFiles\flann_example_c.dir\flann_example.c.obj: ..\examples\flann_example.c
	$(CMAKE_COMMAND) -E cmake_progress_report C:\Users\Filip\Workspace\cmp\EAST_libs_build\flann-1.8.4-src\build\CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object examples/CMakeFiles/flann_example_c.dir/flann_example.c.obj"
	cd C:\Users\Filip\Workspace\cmp\EAST_libs_build\flann-1.8.4-src\build\examples
	C:\PROGRA~2\MICROS~1.0\VC\bin\cl.exe  @<<
 /nologo $(C_FLAGS) $(C_DEFINES) /FoCMakeFiles\flann_example_c.dir\flann_example.c.obj /FdCMakeFiles\flann_example_c.dir\ /FS -c C:\Users\Filip\Workspace\cmp\EAST_libs_build\flann-1.8.4-src\examples\flann_example.c
<<
	cd C:\Users\Filip\Workspace\cmp\EAST_libs_build\flann-1.8.4-src\build

examples\CMakeFiles\flann_example_c.dir\flann_example.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/flann_example_c.dir/flann_example.c.i"
	cd C:\Users\Filip\Workspace\cmp\EAST_libs_build\flann-1.8.4-src\build\examples
	C:\PROGRA~2\MICROS~1.0\VC\bin\cl.exe  > CMakeFiles\flann_example_c.dir\flann_example.c.i @<<
 /nologo $(C_FLAGS) $(C_DEFINES) -E C:\Users\Filip\Workspace\cmp\EAST_libs_build\flann-1.8.4-src\examples\flann_example.c
<<
	cd C:\Users\Filip\Workspace\cmp\EAST_libs_build\flann-1.8.4-src\build

examples\CMakeFiles\flann_example_c.dir\flann_example.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/flann_example_c.dir/flann_example.c.s"
	cd C:\Users\Filip\Workspace\cmp\EAST_libs_build\flann-1.8.4-src\build\examples
	C:\PROGRA~2\MICROS~1.0\VC\bin\cl.exe  @<<
 /nologo $(C_FLAGS) $(C_DEFINES) /FoNUL /FAs /FaCMakeFiles\flann_example_c.dir\flann_example.c.s /c C:\Users\Filip\Workspace\cmp\EAST_libs_build\flann-1.8.4-src\examples\flann_example.c
<<
	cd C:\Users\Filip\Workspace\cmp\EAST_libs_build\flann-1.8.4-src\build

examples\CMakeFiles\flann_example_c.dir\flann_example.c.obj.requires:
.PHONY : examples\CMakeFiles\flann_example_c.dir\flann_example.c.obj.requires

examples\CMakeFiles\flann_example_c.dir\flann_example.c.obj.provides: examples\CMakeFiles\flann_example_c.dir\flann_example.c.obj.requires
	$(MAKE) -f examples\CMakeFiles\flann_example_c.dir\build.make /nologo -$(MAKEFLAGS) examples\CMakeFiles\flann_example_c.dir\flann_example.c.obj.provides.build
.PHONY : examples\CMakeFiles\flann_example_c.dir\flann_example.c.obj.provides

examples\CMakeFiles\flann_example_c.dir\flann_example.c.obj.provides.build: examples\CMakeFiles\flann_example_c.dir\flann_example.c.obj

# Object files for target flann_example_c
flann_example_c_OBJECTS = \
"CMakeFiles\flann_example_c.dir\flann_example.c.obj"

# External object files for target flann_example_c
flann_example_c_EXTERNAL_OBJECTS =

bin\flann_example_c.exe: examples\CMakeFiles\flann_example_c.dir\flann_example.c.obj
bin\flann_example_c.exe: examples\CMakeFiles\flann_example_c.dir\build.make
bin\flann_example_c.exe: lib\flann.lib
bin\flann_example_c.exe: examples\CMakeFiles\flann_example_c.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable ..\bin\flann_example_c.exe"
	cd C:\Users\Filip\Workspace\cmp\EAST_libs_build\flann-1.8.4-src\build\examples
	"C:\Program Files (x86)\CMake\bin\cmake.exe" -E vs_link_exe C:\PROGRA~2\MICROS~1.0\VC\bin\link.exe /nologo @CMakeFiles\flann_example_c.dir\objects1.rsp @<<
 /out:..\bin\flann_example_c.exe /implib:..\bin\flann_example_c.lib /pdb:C:\Users\Filip\Workspace\cmp\EAST_libs_build\flann-1.8.4-src\build\bin\flann_example_c.pdb /version:0.0    /subsystem:console  ..\lib\flann.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<
	cd C:\Users\Filip\Workspace\cmp\EAST_libs_build\flann-1.8.4-src\build

# Rule to build all files generated by this target.
examples\CMakeFiles\flann_example_c.dir\build: bin\flann_example_c.exe
.PHONY : examples\CMakeFiles\flann_example_c.dir\build

examples\CMakeFiles\flann_example_c.dir\requires: examples\CMakeFiles\flann_example_c.dir\flann_example.c.obj.requires
.PHONY : examples\CMakeFiles\flann_example_c.dir\requires

examples\CMakeFiles\flann_example_c.dir\clean:
	cd C:\Users\Filip\Workspace\cmp\EAST_libs_build\flann-1.8.4-src\build\examples
	$(CMAKE_COMMAND) -P CMakeFiles\flann_example_c.dir\cmake_clean.cmake
	cd C:\Users\Filip\Workspace\cmp\EAST_libs_build\flann-1.8.4-src\build
.PHONY : examples\CMakeFiles\flann_example_c.dir\clean

examples\CMakeFiles\flann_example_c.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\Filip\Workspace\cmp\EAST_libs_build\flann-1.8.4-src C:\Users\Filip\Workspace\cmp\EAST_libs_build\flann-1.8.4-src\examples C:\Users\Filip\Workspace\cmp\EAST_libs_build\flann-1.8.4-src\build C:\Users\Filip\Workspace\cmp\EAST_libs_build\flann-1.8.4-src\build\examples C:\Users\Filip\Workspace\cmp\EAST_libs_build\flann-1.8.4-src\build\examples\CMakeFiles\flann_example_c.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : examples\CMakeFiles\flann_example_c.dir\depend

