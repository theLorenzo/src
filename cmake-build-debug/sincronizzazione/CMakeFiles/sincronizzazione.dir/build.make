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
CMAKE_COMMAND = /snap/clion/151/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/151/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/davide/project1/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/davide/project1/src/cmake-build-debug

# Include any dependencies generated for this target.
include sincronizzazione/CMakeFiles/sincronizzazione.dir/depend.make

# Include the progress variables for this target.
include sincronizzazione/CMakeFiles/sincronizzazione.dir/progress.make

# Include the compile flags for this target's objects.
include sincronizzazione/CMakeFiles/sincronizzazione.dir/flags.make

sincronizzazione/CMakeFiles/sincronizzazione.dir/src/sincronizzatore.cpp.o: sincronizzazione/CMakeFiles/sincronizzazione.dir/flags.make
sincronizzazione/CMakeFiles/sincronizzazione.dir/src/sincronizzatore.cpp.o: ../sincronizzazione/src/sincronizzatore.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/davide/project1/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object sincronizzazione/CMakeFiles/sincronizzazione.dir/src/sincronizzatore.cpp.o"
	cd /home/davide/project1/src/cmake-build-debug/sincronizzazione && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sincronizzazione.dir/src/sincronizzatore.cpp.o -c /home/davide/project1/src/sincronizzazione/src/sincronizzatore.cpp

sincronizzazione/CMakeFiles/sincronizzazione.dir/src/sincronizzatore.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sincronizzazione.dir/src/sincronizzatore.cpp.i"
	cd /home/davide/project1/src/cmake-build-debug/sincronizzazione && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/davide/project1/src/sincronizzazione/src/sincronizzatore.cpp > CMakeFiles/sincronizzazione.dir/src/sincronizzatore.cpp.i

sincronizzazione/CMakeFiles/sincronizzazione.dir/src/sincronizzatore.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sincronizzazione.dir/src/sincronizzatore.cpp.s"
	cd /home/davide/project1/src/cmake-build-debug/sincronizzazione && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/davide/project1/src/sincronizzazione/src/sincronizzatore.cpp -o CMakeFiles/sincronizzazione.dir/src/sincronizzatore.cpp.s

# Object files for target sincronizzazione
sincronizzazione_OBJECTS = \
"CMakeFiles/sincronizzazione.dir/src/sincronizzatore.cpp.o"

# External object files for target sincronizzazione
sincronizzazione_EXTERNAL_OBJECTS =

devel/lib/sincronizzazione/sincronizzazione: sincronizzazione/CMakeFiles/sincronizzazione.dir/src/sincronizzatore.cpp.o
devel/lib/sincronizzazione/sincronizzazione: sincronizzazione/CMakeFiles/sincronizzazione.dir/build.make
devel/lib/sincronizzazione/sincronizzazione: /opt/ros/melodic/lib/libmessage_filters.so
devel/lib/sincronizzazione/sincronizzazione: /opt/ros/melodic/lib/libroscpp.so
devel/lib/sincronizzazione/sincronizzazione: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
devel/lib/sincronizzazione/sincronizzazione: /opt/ros/melodic/lib/librosconsole.so
devel/lib/sincronizzazione/sincronizzazione: /opt/ros/melodic/lib/librosconsole_log4cxx.so
devel/lib/sincronizzazione/sincronizzazione: /opt/ros/melodic/lib/librosconsole_backend_interface.so
devel/lib/sincronizzazione/sincronizzazione: /usr/lib/x86_64-linux-gnu/liblog4cxx.so
devel/lib/sincronizzazione/sincronizzazione: /usr/lib/x86_64-linux-gnu/libboost_regex.so
devel/lib/sincronizzazione/sincronizzazione: /opt/ros/melodic/lib/libxmlrpcpp.so
devel/lib/sincronizzazione/sincronizzazione: /opt/ros/melodic/lib/libroscpp_serialization.so
devel/lib/sincronizzazione/sincronizzazione: /opt/ros/melodic/lib/librostime.so
devel/lib/sincronizzazione/sincronizzazione: /opt/ros/melodic/lib/libcpp_common.so
devel/lib/sincronizzazione/sincronizzazione: /usr/lib/x86_64-linux-gnu/libboost_system.so
devel/lib/sincronizzazione/sincronizzazione: /usr/lib/x86_64-linux-gnu/libboost_thread.so
devel/lib/sincronizzazione/sincronizzazione: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
devel/lib/sincronizzazione/sincronizzazione: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
devel/lib/sincronizzazione/sincronizzazione: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
devel/lib/sincronizzazione/sincronizzazione: /usr/lib/x86_64-linux-gnu/libpthread.so
devel/lib/sincronizzazione/sincronizzazione: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so.0.4
devel/lib/sincronizzazione/sincronizzazione: sincronizzazione/CMakeFiles/sincronizzazione.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/davide/project1/src/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../devel/lib/sincronizzazione/sincronizzazione"
	cd /home/davide/project1/src/cmake-build-debug/sincronizzazione && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sincronizzazione.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
sincronizzazione/CMakeFiles/sincronizzazione.dir/build: devel/lib/sincronizzazione/sincronizzazione

.PHONY : sincronizzazione/CMakeFiles/sincronizzazione.dir/build

sincronizzazione/CMakeFiles/sincronizzazione.dir/clean:
	cd /home/davide/project1/src/cmake-build-debug/sincronizzazione && $(CMAKE_COMMAND) -P CMakeFiles/sincronizzazione.dir/cmake_clean.cmake
.PHONY : sincronizzazione/CMakeFiles/sincronizzazione.dir/clean

sincronizzazione/CMakeFiles/sincronizzazione.dir/depend:
	cd /home/davide/project1/src/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/davide/project1/src /home/davide/project1/src/sincronizzazione /home/davide/project1/src/cmake-build-debug /home/davide/project1/src/cmake-build-debug/sincronizzazione /home/davide/project1/src/cmake-build-debug/sincronizzazione/CMakeFiles/sincronizzazione.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : sincronizzazione/CMakeFiles/sincronizzazione.dir/depend

