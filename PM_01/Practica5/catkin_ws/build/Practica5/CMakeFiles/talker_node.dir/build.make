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
CMAKE_SOURCE_DIR = /home/robotica/catkin_ws/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/robotica/catkin_ws/build

# Include any dependencies generated for this target.
include Practica5/CMakeFiles/talker_node.dir/depend.make

# Include the progress variables for this target.
include Practica5/CMakeFiles/talker_node.dir/progress.make

# Include the compile flags for this target's objects.
include Practica5/CMakeFiles/talker_node.dir/flags.make

Practica5/CMakeFiles/talker_node.dir/src/talker.cpp.o: Practica5/CMakeFiles/talker_node.dir/flags.make
Practica5/CMakeFiles/talker_node.dir/src/talker.cpp.o: /home/robotica/catkin_ws/src/Practica5/src/talker.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/robotica/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Practica5/CMakeFiles/talker_node.dir/src/talker.cpp.o"
	cd /home/robotica/catkin_ws/build/Practica5 && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/talker_node.dir/src/talker.cpp.o -c /home/robotica/catkin_ws/src/Practica5/src/talker.cpp

Practica5/CMakeFiles/talker_node.dir/src/talker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/talker_node.dir/src/talker.cpp.i"
	cd /home/robotica/catkin_ws/build/Practica5 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/robotica/catkin_ws/src/Practica5/src/talker.cpp > CMakeFiles/talker_node.dir/src/talker.cpp.i

Practica5/CMakeFiles/talker_node.dir/src/talker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/talker_node.dir/src/talker.cpp.s"
	cd /home/robotica/catkin_ws/build/Practica5 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/robotica/catkin_ws/src/Practica5/src/talker.cpp -o CMakeFiles/talker_node.dir/src/talker.cpp.s

Practica5/CMakeFiles/talker_node.dir/src/talker.cpp.o.requires:

.PHONY : Practica5/CMakeFiles/talker_node.dir/src/talker.cpp.o.requires

Practica5/CMakeFiles/talker_node.dir/src/talker.cpp.o.provides: Practica5/CMakeFiles/talker_node.dir/src/talker.cpp.o.requires
	$(MAKE) -f Practica5/CMakeFiles/talker_node.dir/build.make Practica5/CMakeFiles/talker_node.dir/src/talker.cpp.o.provides.build
.PHONY : Practica5/CMakeFiles/talker_node.dir/src/talker.cpp.o.provides

Practica5/CMakeFiles/talker_node.dir/src/talker.cpp.o.provides.build: Practica5/CMakeFiles/talker_node.dir/src/talker.cpp.o


# Object files for target talker_node
talker_node_OBJECTS = \
"CMakeFiles/talker_node.dir/src/talker.cpp.o"

# External object files for target talker_node
talker_node_EXTERNAL_OBJECTS =

/home/robotica/catkin_ws/devel/lib/Practica5/talker_node: Practica5/CMakeFiles/talker_node.dir/src/talker.cpp.o
/home/robotica/catkin_ws/devel/lib/Practica5/talker_node: Practica5/CMakeFiles/talker_node.dir/build.make
/home/robotica/catkin_ws/devel/lib/Practica5/talker_node: /opt/ros/melodic/lib/libroscpp.so
/home/robotica/catkin_ws/devel/lib/Practica5/talker_node: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
/home/robotica/catkin_ws/devel/lib/Practica5/talker_node: /usr/lib/x86_64-linux-gnu/libboost_signals.so
/home/robotica/catkin_ws/devel/lib/Practica5/talker_node: /opt/ros/melodic/lib/librosconsole.so
/home/robotica/catkin_ws/devel/lib/Practica5/talker_node: /opt/ros/melodic/lib/librosconsole_log4cxx.so
/home/robotica/catkin_ws/devel/lib/Practica5/talker_node: /opt/ros/melodic/lib/librosconsole_backend_interface.so
/home/robotica/catkin_ws/devel/lib/Practica5/talker_node: /usr/lib/x86_64-linux-gnu/liblog4cxx.so
/home/robotica/catkin_ws/devel/lib/Practica5/talker_node: /usr/lib/x86_64-linux-gnu/libboost_regex.so
/home/robotica/catkin_ws/devel/lib/Practica5/talker_node: /opt/ros/melodic/lib/libxmlrpcpp.so
/home/robotica/catkin_ws/devel/lib/Practica5/talker_node: /opt/ros/melodic/lib/libroscpp_serialization.so
/home/robotica/catkin_ws/devel/lib/Practica5/talker_node: /opt/ros/melodic/lib/librostime.so
/home/robotica/catkin_ws/devel/lib/Practica5/talker_node: /opt/ros/melodic/lib/libcpp_common.so
/home/robotica/catkin_ws/devel/lib/Practica5/talker_node: /usr/lib/x86_64-linux-gnu/libboost_system.so
/home/robotica/catkin_ws/devel/lib/Practica5/talker_node: /usr/lib/x86_64-linux-gnu/libboost_thread.so
/home/robotica/catkin_ws/devel/lib/Practica5/talker_node: /usr/lib/x86_64-linux-gnu/libboost_chrono.so
/home/robotica/catkin_ws/devel/lib/Practica5/talker_node: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
/home/robotica/catkin_ws/devel/lib/Practica5/talker_node: /usr/lib/x86_64-linux-gnu/libboost_atomic.so
/home/robotica/catkin_ws/devel/lib/Practica5/talker_node: /usr/lib/x86_64-linux-gnu/libpthread.so
/home/robotica/catkin_ws/devel/lib/Practica5/talker_node: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so.0.4
/home/robotica/catkin_ws/devel/lib/Practica5/talker_node: Practica5/CMakeFiles/talker_node.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/robotica/catkin_ws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/robotica/catkin_ws/devel/lib/Practica5/talker_node"
	cd /home/robotica/catkin_ws/build/Practica5 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/talker_node.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Practica5/CMakeFiles/talker_node.dir/build: /home/robotica/catkin_ws/devel/lib/Practica5/talker_node

.PHONY : Practica5/CMakeFiles/talker_node.dir/build

Practica5/CMakeFiles/talker_node.dir/requires: Practica5/CMakeFiles/talker_node.dir/src/talker.cpp.o.requires

.PHONY : Practica5/CMakeFiles/talker_node.dir/requires

Practica5/CMakeFiles/talker_node.dir/clean:
	cd /home/robotica/catkin_ws/build/Practica5 && $(CMAKE_COMMAND) -P CMakeFiles/talker_node.dir/cmake_clean.cmake
.PHONY : Practica5/CMakeFiles/talker_node.dir/clean

Practica5/CMakeFiles/talker_node.dir/depend:
	cd /home/robotica/catkin_ws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/robotica/catkin_ws/src /home/robotica/catkin_ws/src/Practica5 /home/robotica/catkin_ws/build /home/robotica/catkin_ws/build/Practica5 /home/robotica/catkin_ws/build/Practica5/CMakeFiles/talker_node.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Practica5/CMakeFiles/talker_node.dir/depend

