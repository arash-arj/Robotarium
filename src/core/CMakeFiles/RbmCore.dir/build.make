# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/arash/dev/Robotarium

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/arash/dev/Robotarium

# Include any dependencies generated for this target.
include src/core/CMakeFiles/RbmCore.dir/depend.make

# Include the progress variables for this target.
include src/core/CMakeFiles/RbmCore.dir/progress.make

# Include the compile flags for this target's objects.
include src/core/CMakeFiles/RbmCore.dir/flags.make

src/core/CMakeFiles/RbmCore.dir/Manager.cpp.o: src/core/CMakeFiles/RbmCore.dir/flags.make
src/core/CMakeFiles/RbmCore.dir/Manager.cpp.o: src/core/Manager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arash/dev/Robotarium/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/core/CMakeFiles/RbmCore.dir/Manager.cpp.o"
	cd /home/arash/dev/Robotarium/src/core && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RbmCore.dir/Manager.cpp.o -c /home/arash/dev/Robotarium/src/core/Manager.cpp

src/core/CMakeFiles/RbmCore.dir/Manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RbmCore.dir/Manager.cpp.i"
	cd /home/arash/dev/Robotarium/src/core && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arash/dev/Robotarium/src/core/Manager.cpp > CMakeFiles/RbmCore.dir/Manager.cpp.i

src/core/CMakeFiles/RbmCore.dir/Manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RbmCore.dir/Manager.cpp.s"
	cd /home/arash/dev/Robotarium/src/core && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arash/dev/Robotarium/src/core/Manager.cpp -o CMakeFiles/RbmCore.dir/Manager.cpp.s

src/core/CMakeFiles/RbmCore.dir/Manager.cpp.o.requires:

.PHONY : src/core/CMakeFiles/RbmCore.dir/Manager.cpp.o.requires

src/core/CMakeFiles/RbmCore.dir/Manager.cpp.o.provides: src/core/CMakeFiles/RbmCore.dir/Manager.cpp.o.requires
	$(MAKE) -f src/core/CMakeFiles/RbmCore.dir/build.make src/core/CMakeFiles/RbmCore.dir/Manager.cpp.o.provides.build
.PHONY : src/core/CMakeFiles/RbmCore.dir/Manager.cpp.o.provides

src/core/CMakeFiles/RbmCore.dir/Manager.cpp.o.provides.build: src/core/CMakeFiles/RbmCore.dir/Manager.cpp.o


src/core/CMakeFiles/RbmCore.dir/Scene.cpp.o: src/core/CMakeFiles/RbmCore.dir/flags.make
src/core/CMakeFiles/RbmCore.dir/Scene.cpp.o: src/core/Scene.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arash/dev/Robotarium/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/core/CMakeFiles/RbmCore.dir/Scene.cpp.o"
	cd /home/arash/dev/Robotarium/src/core && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RbmCore.dir/Scene.cpp.o -c /home/arash/dev/Robotarium/src/core/Scene.cpp

src/core/CMakeFiles/RbmCore.dir/Scene.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RbmCore.dir/Scene.cpp.i"
	cd /home/arash/dev/Robotarium/src/core && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arash/dev/Robotarium/src/core/Scene.cpp > CMakeFiles/RbmCore.dir/Scene.cpp.i

src/core/CMakeFiles/RbmCore.dir/Scene.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RbmCore.dir/Scene.cpp.s"
	cd /home/arash/dev/Robotarium/src/core && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arash/dev/Robotarium/src/core/Scene.cpp -o CMakeFiles/RbmCore.dir/Scene.cpp.s

src/core/CMakeFiles/RbmCore.dir/Scene.cpp.o.requires:

.PHONY : src/core/CMakeFiles/RbmCore.dir/Scene.cpp.o.requires

src/core/CMakeFiles/RbmCore.dir/Scene.cpp.o.provides: src/core/CMakeFiles/RbmCore.dir/Scene.cpp.o.requires
	$(MAKE) -f src/core/CMakeFiles/RbmCore.dir/build.make src/core/CMakeFiles/RbmCore.dir/Scene.cpp.o.provides.build
.PHONY : src/core/CMakeFiles/RbmCore.dir/Scene.cpp.o.provides

src/core/CMakeFiles/RbmCore.dir/Scene.cpp.o.provides.build: src/core/CMakeFiles/RbmCore.dir/Scene.cpp.o


src/core/CMakeFiles/RbmCore.dir/Node.cpp.o: src/core/CMakeFiles/RbmCore.dir/flags.make
src/core/CMakeFiles/RbmCore.dir/Node.cpp.o: src/core/Node.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arash/dev/Robotarium/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/core/CMakeFiles/RbmCore.dir/Node.cpp.o"
	cd /home/arash/dev/Robotarium/src/core && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RbmCore.dir/Node.cpp.o -c /home/arash/dev/Robotarium/src/core/Node.cpp

src/core/CMakeFiles/RbmCore.dir/Node.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RbmCore.dir/Node.cpp.i"
	cd /home/arash/dev/Robotarium/src/core && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arash/dev/Robotarium/src/core/Node.cpp > CMakeFiles/RbmCore.dir/Node.cpp.i

src/core/CMakeFiles/RbmCore.dir/Node.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RbmCore.dir/Node.cpp.s"
	cd /home/arash/dev/Robotarium/src/core && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arash/dev/Robotarium/src/core/Node.cpp -o CMakeFiles/RbmCore.dir/Node.cpp.s

src/core/CMakeFiles/RbmCore.dir/Node.cpp.o.requires:

.PHONY : src/core/CMakeFiles/RbmCore.dir/Node.cpp.o.requires

src/core/CMakeFiles/RbmCore.dir/Node.cpp.o.provides: src/core/CMakeFiles/RbmCore.dir/Node.cpp.o.requires
	$(MAKE) -f src/core/CMakeFiles/RbmCore.dir/build.make src/core/CMakeFiles/RbmCore.dir/Node.cpp.o.provides.build
.PHONY : src/core/CMakeFiles/RbmCore.dir/Node.cpp.o.provides

src/core/CMakeFiles/RbmCore.dir/Node.cpp.o.provides.build: src/core/CMakeFiles/RbmCore.dir/Node.cpp.o


src/core/CMakeFiles/RbmCore.dir/SceneNode.cpp.o: src/core/CMakeFiles/RbmCore.dir/flags.make
src/core/CMakeFiles/RbmCore.dir/SceneNode.cpp.o: src/core/SceneNode.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arash/dev/Robotarium/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/core/CMakeFiles/RbmCore.dir/SceneNode.cpp.o"
	cd /home/arash/dev/Robotarium/src/core && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RbmCore.dir/SceneNode.cpp.o -c /home/arash/dev/Robotarium/src/core/SceneNode.cpp

src/core/CMakeFiles/RbmCore.dir/SceneNode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RbmCore.dir/SceneNode.cpp.i"
	cd /home/arash/dev/Robotarium/src/core && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arash/dev/Robotarium/src/core/SceneNode.cpp > CMakeFiles/RbmCore.dir/SceneNode.cpp.i

src/core/CMakeFiles/RbmCore.dir/SceneNode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RbmCore.dir/SceneNode.cpp.s"
	cd /home/arash/dev/Robotarium/src/core && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arash/dev/Robotarium/src/core/SceneNode.cpp -o CMakeFiles/RbmCore.dir/SceneNode.cpp.s

src/core/CMakeFiles/RbmCore.dir/SceneNode.cpp.o.requires:

.PHONY : src/core/CMakeFiles/RbmCore.dir/SceneNode.cpp.o.requires

src/core/CMakeFiles/RbmCore.dir/SceneNode.cpp.o.provides: src/core/CMakeFiles/RbmCore.dir/SceneNode.cpp.o.requires
	$(MAKE) -f src/core/CMakeFiles/RbmCore.dir/build.make src/core/CMakeFiles/RbmCore.dir/SceneNode.cpp.o.provides.build
.PHONY : src/core/CMakeFiles/RbmCore.dir/SceneNode.cpp.o.provides

src/core/CMakeFiles/RbmCore.dir/SceneNode.cpp.o.provides.build: src/core/CMakeFiles/RbmCore.dir/SceneNode.cpp.o


src/core/CMakeFiles/RbmCore.dir/SceneNodeBase.cpp.o: src/core/CMakeFiles/RbmCore.dir/flags.make
src/core/CMakeFiles/RbmCore.dir/SceneNodeBase.cpp.o: src/core/SceneNodeBase.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arash/dev/Robotarium/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/core/CMakeFiles/RbmCore.dir/SceneNodeBase.cpp.o"
	cd /home/arash/dev/Robotarium/src/core && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RbmCore.dir/SceneNodeBase.cpp.o -c /home/arash/dev/Robotarium/src/core/SceneNodeBase.cpp

src/core/CMakeFiles/RbmCore.dir/SceneNodeBase.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RbmCore.dir/SceneNodeBase.cpp.i"
	cd /home/arash/dev/Robotarium/src/core && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arash/dev/Robotarium/src/core/SceneNodeBase.cpp > CMakeFiles/RbmCore.dir/SceneNodeBase.cpp.i

src/core/CMakeFiles/RbmCore.dir/SceneNodeBase.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RbmCore.dir/SceneNodeBase.cpp.s"
	cd /home/arash/dev/Robotarium/src/core && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arash/dev/Robotarium/src/core/SceneNodeBase.cpp -o CMakeFiles/RbmCore.dir/SceneNodeBase.cpp.s

src/core/CMakeFiles/RbmCore.dir/SceneNodeBase.cpp.o.requires:

.PHONY : src/core/CMakeFiles/RbmCore.dir/SceneNodeBase.cpp.o.requires

src/core/CMakeFiles/RbmCore.dir/SceneNodeBase.cpp.o.provides: src/core/CMakeFiles/RbmCore.dir/SceneNodeBase.cpp.o.requires
	$(MAKE) -f src/core/CMakeFiles/RbmCore.dir/build.make src/core/CMakeFiles/RbmCore.dir/SceneNodeBase.cpp.o.provides.build
.PHONY : src/core/CMakeFiles/RbmCore.dir/SceneNodeBase.cpp.o.provides

src/core/CMakeFiles/RbmCore.dir/SceneNodeBase.cpp.o.provides.build: src/core/CMakeFiles/RbmCore.dir/SceneNodeBase.cpp.o


src/core/CMakeFiles/RbmCore.dir/Visitor.cpp.o: src/core/CMakeFiles/RbmCore.dir/flags.make
src/core/CMakeFiles/RbmCore.dir/Visitor.cpp.o: src/core/Visitor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arash/dev/Robotarium/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/core/CMakeFiles/RbmCore.dir/Visitor.cpp.o"
	cd /home/arash/dev/Robotarium/src/core && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/RbmCore.dir/Visitor.cpp.o -c /home/arash/dev/Robotarium/src/core/Visitor.cpp

src/core/CMakeFiles/RbmCore.dir/Visitor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RbmCore.dir/Visitor.cpp.i"
	cd /home/arash/dev/Robotarium/src/core && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arash/dev/Robotarium/src/core/Visitor.cpp > CMakeFiles/RbmCore.dir/Visitor.cpp.i

src/core/CMakeFiles/RbmCore.dir/Visitor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RbmCore.dir/Visitor.cpp.s"
	cd /home/arash/dev/Robotarium/src/core && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arash/dev/Robotarium/src/core/Visitor.cpp -o CMakeFiles/RbmCore.dir/Visitor.cpp.s

src/core/CMakeFiles/RbmCore.dir/Visitor.cpp.o.requires:

.PHONY : src/core/CMakeFiles/RbmCore.dir/Visitor.cpp.o.requires

src/core/CMakeFiles/RbmCore.dir/Visitor.cpp.o.provides: src/core/CMakeFiles/RbmCore.dir/Visitor.cpp.o.requires
	$(MAKE) -f src/core/CMakeFiles/RbmCore.dir/build.make src/core/CMakeFiles/RbmCore.dir/Visitor.cpp.o.provides.build
.PHONY : src/core/CMakeFiles/RbmCore.dir/Visitor.cpp.o.provides

src/core/CMakeFiles/RbmCore.dir/Visitor.cpp.o.provides.build: src/core/CMakeFiles/RbmCore.dir/Visitor.cpp.o


# Object files for target RbmCore
RbmCore_OBJECTS = \
"CMakeFiles/RbmCore.dir/Manager.cpp.o" \
"CMakeFiles/RbmCore.dir/Scene.cpp.o" \
"CMakeFiles/RbmCore.dir/Node.cpp.o" \
"CMakeFiles/RbmCore.dir/SceneNode.cpp.o" \
"CMakeFiles/RbmCore.dir/SceneNodeBase.cpp.o" \
"CMakeFiles/RbmCore.dir/Visitor.cpp.o"

# External object files for target RbmCore
RbmCore_EXTERNAL_OBJECTS =

lib/libRbmCore.a: src/core/CMakeFiles/RbmCore.dir/Manager.cpp.o
lib/libRbmCore.a: src/core/CMakeFiles/RbmCore.dir/Scene.cpp.o
lib/libRbmCore.a: src/core/CMakeFiles/RbmCore.dir/Node.cpp.o
lib/libRbmCore.a: src/core/CMakeFiles/RbmCore.dir/SceneNode.cpp.o
lib/libRbmCore.a: src/core/CMakeFiles/RbmCore.dir/SceneNodeBase.cpp.o
lib/libRbmCore.a: src/core/CMakeFiles/RbmCore.dir/Visitor.cpp.o
lib/libRbmCore.a: src/core/CMakeFiles/RbmCore.dir/build.make
lib/libRbmCore.a: src/core/CMakeFiles/RbmCore.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/arash/dev/Robotarium/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX static library ../../lib/libRbmCore.a"
	cd /home/arash/dev/Robotarium/src/core && $(CMAKE_COMMAND) -P CMakeFiles/RbmCore.dir/cmake_clean_target.cmake
	cd /home/arash/dev/Robotarium/src/core && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RbmCore.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/core/CMakeFiles/RbmCore.dir/build: lib/libRbmCore.a

.PHONY : src/core/CMakeFiles/RbmCore.dir/build

src/core/CMakeFiles/RbmCore.dir/requires: src/core/CMakeFiles/RbmCore.dir/Manager.cpp.o.requires
src/core/CMakeFiles/RbmCore.dir/requires: src/core/CMakeFiles/RbmCore.dir/Scene.cpp.o.requires
src/core/CMakeFiles/RbmCore.dir/requires: src/core/CMakeFiles/RbmCore.dir/Node.cpp.o.requires
src/core/CMakeFiles/RbmCore.dir/requires: src/core/CMakeFiles/RbmCore.dir/SceneNode.cpp.o.requires
src/core/CMakeFiles/RbmCore.dir/requires: src/core/CMakeFiles/RbmCore.dir/SceneNodeBase.cpp.o.requires
src/core/CMakeFiles/RbmCore.dir/requires: src/core/CMakeFiles/RbmCore.dir/Visitor.cpp.o.requires

.PHONY : src/core/CMakeFiles/RbmCore.dir/requires

src/core/CMakeFiles/RbmCore.dir/clean:
	cd /home/arash/dev/Robotarium/src/core && $(CMAKE_COMMAND) -P CMakeFiles/RbmCore.dir/cmake_clean.cmake
.PHONY : src/core/CMakeFiles/RbmCore.dir/clean

src/core/CMakeFiles/RbmCore.dir/depend:
	cd /home/arash/dev/Robotarium && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/arash/dev/Robotarium /home/arash/dev/Robotarium/src/core /home/arash/dev/Robotarium /home/arash/dev/Robotarium/src/core /home/arash/dev/Robotarium/src/core/CMakeFiles/RbmCore.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/core/CMakeFiles/RbmCore.dir/depend

