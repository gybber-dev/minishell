# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /mnt/c/Users/dinar/CLionProjects/minishell

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/dinar/CLionProjects/minishell/build

# Include any dependencies generated for this target.
include CMakeFiles/builtins.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/builtins.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/builtins.dir/flags.make

CMakeFiles/builtins.dir/src/builtins/builtins.c.o: CMakeFiles/builtins.dir/flags.make
CMakeFiles/builtins.dir/src/builtins/builtins.c.o: ../src/builtins/builtins.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/dinar/CLionProjects/minishell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/builtins.dir/src/builtins/builtins.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/builtins.dir/src/builtins/builtins.c.o   -c /mnt/c/Users/dinar/CLionProjects/minishell/src/builtins/builtins.c

CMakeFiles/builtins.dir/src/builtins/builtins.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/builtins.dir/src/builtins/builtins.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/dinar/CLionProjects/minishell/src/builtins/builtins.c > CMakeFiles/builtins.dir/src/builtins/builtins.c.i

CMakeFiles/builtins.dir/src/builtins/builtins.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/builtins.dir/src/builtins/builtins.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/dinar/CLionProjects/minishell/src/builtins/builtins.c -o CMakeFiles/builtins.dir/src/builtins/builtins.c.s

CMakeFiles/builtins.dir/src/builtins/cd.c.o: CMakeFiles/builtins.dir/flags.make
CMakeFiles/builtins.dir/src/builtins/cd.c.o: ../src/builtins/cd.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/dinar/CLionProjects/minishell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/builtins.dir/src/builtins/cd.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/builtins.dir/src/builtins/cd.c.o   -c /mnt/c/Users/dinar/CLionProjects/minishell/src/builtins/cd.c

CMakeFiles/builtins.dir/src/builtins/cd.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/builtins.dir/src/builtins/cd.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/dinar/CLionProjects/minishell/src/builtins/cd.c > CMakeFiles/builtins.dir/src/builtins/cd.c.i

CMakeFiles/builtins.dir/src/builtins/cd.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/builtins.dir/src/builtins/cd.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/dinar/CLionProjects/minishell/src/builtins/cd.c -o CMakeFiles/builtins.dir/src/builtins/cd.c.s

# Object files for target builtins
builtins_OBJECTS = \
"CMakeFiles/builtins.dir/src/builtins/builtins.c.o" \
"CMakeFiles/builtins.dir/src/builtins/cd.c.o"

# External object files for target builtins
builtins_EXTERNAL_OBJECTS =

builtins: CMakeFiles/builtins.dir/src/builtins/builtins.c.o
builtins: CMakeFiles/builtins.dir/src/builtins/cd.c.o
builtins: CMakeFiles/builtins.dir/build.make
builtins: CMakeFiles/builtins.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/dinar/CLionProjects/minishell/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable builtins"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/builtins.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/builtins.dir/build: builtins

.PHONY : CMakeFiles/builtins.dir/build

CMakeFiles/builtins.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/builtins.dir/cmake_clean.cmake
.PHONY : CMakeFiles/builtins.dir/clean

CMakeFiles/builtins.dir/depend:
	cd /mnt/c/Users/dinar/CLionProjects/minishell/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/dinar/CLionProjects/minishell /mnt/c/Users/dinar/CLionProjects/minishell /mnt/c/Users/dinar/CLionProjects/minishell/build /mnt/c/Users/dinar/CLionProjects/minishell/build /mnt/c/Users/dinar/CLionProjects/minishell/build/CMakeFiles/builtins.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/builtins.dir/depend

