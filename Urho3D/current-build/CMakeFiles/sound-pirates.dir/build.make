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
CMAKE_SOURCE_DIR = /home/pi/sound-pirates/Urho3D/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/sound-pirates/Urho3D/current-build

# Include any dependencies generated for this target.
include CMakeFiles/sound-pirates.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sound-pirates.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sound-pirates.dir/flags.make

CMakeFiles/sound-pirates.dir/RtAudio.cpp.o: CMakeFiles/sound-pirates.dir/flags.make
CMakeFiles/sound-pirates.dir/RtAudio.cpp.o: /home/pi/sound-pirates/Urho3D/src/RtAudio.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/sound-pirates/Urho3D/current-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sound-pirates.dir/RtAudio.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sound-pirates.dir/RtAudio.cpp.o -c /home/pi/sound-pirates/Urho3D/src/RtAudio.cpp

CMakeFiles/sound-pirates.dir/RtAudio.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sound-pirates.dir/RtAudio.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/sound-pirates/Urho3D/src/RtAudio.cpp > CMakeFiles/sound-pirates.dir/RtAudio.cpp.i

CMakeFiles/sound-pirates.dir/RtAudio.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sound-pirates.dir/RtAudio.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/sound-pirates/Urho3D/src/RtAudio.cpp -o CMakeFiles/sound-pirates.dir/RtAudio.cpp.s

CMakeFiles/sound-pirates.dir/defineNote.cpp.o: CMakeFiles/sound-pirates.dir/flags.make
CMakeFiles/sound-pirates.dir/defineNote.cpp.o: /home/pi/sound-pirates/Urho3D/src/defineNote.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/sound-pirates/Urho3D/current-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/sound-pirates.dir/defineNote.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sound-pirates.dir/defineNote.cpp.o -c /home/pi/sound-pirates/Urho3D/src/defineNote.cpp

CMakeFiles/sound-pirates.dir/defineNote.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sound-pirates.dir/defineNote.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/sound-pirates/Urho3D/src/defineNote.cpp > CMakeFiles/sound-pirates.dir/defineNote.cpp.i

CMakeFiles/sound-pirates.dir/defineNote.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sound-pirates.dir/defineNote.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/sound-pirates/Urho3D/src/defineNote.cpp -o CMakeFiles/sound-pirates.dir/defineNote.cpp.s

CMakeFiles/sound-pirates.dir/fft.cpp.o: CMakeFiles/sound-pirates.dir/flags.make
CMakeFiles/sound-pirates.dir/fft.cpp.o: /home/pi/sound-pirates/Urho3D/src/fft.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/sound-pirates/Urho3D/current-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/sound-pirates.dir/fft.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sound-pirates.dir/fft.cpp.o -c /home/pi/sound-pirates/Urho3D/src/fft.cpp

CMakeFiles/sound-pirates.dir/fft.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sound-pirates.dir/fft.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/sound-pirates/Urho3D/src/fft.cpp > CMakeFiles/sound-pirates.dir/fft.cpp.i

CMakeFiles/sound-pirates.dir/fft.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sound-pirates.dir/fft.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/sound-pirates/Urho3D/src/fft.cpp -o CMakeFiles/sound-pirates.dir/fft.cpp.s

CMakeFiles/sound-pirates.dir/findFreqMax.cpp.o: CMakeFiles/sound-pirates.dir/flags.make
CMakeFiles/sound-pirates.dir/findFreqMax.cpp.o: /home/pi/sound-pirates/Urho3D/src/findFreqMax.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/sound-pirates/Urho3D/current-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/sound-pirates.dir/findFreqMax.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sound-pirates.dir/findFreqMax.cpp.o -c /home/pi/sound-pirates/Urho3D/src/findFreqMax.cpp

CMakeFiles/sound-pirates.dir/findFreqMax.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sound-pirates.dir/findFreqMax.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/sound-pirates/Urho3D/src/findFreqMax.cpp > CMakeFiles/sound-pirates.dir/findFreqMax.cpp.i

CMakeFiles/sound-pirates.dir/findFreqMax.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sound-pirates.dir/findFreqMax.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/sound-pirates/Urho3D/src/findFreqMax.cpp -o CMakeFiles/sound-pirates.dir/findFreqMax.cpp.s

CMakeFiles/sound-pirates.dir/instructionsStatements.cpp.o: CMakeFiles/sound-pirates.dir/flags.make
CMakeFiles/sound-pirates.dir/instructionsStatements.cpp.o: /home/pi/sound-pirates/Urho3D/src/instructionsStatements.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/sound-pirates/Urho3D/current-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/sound-pirates.dir/instructionsStatements.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sound-pirates.dir/instructionsStatements.cpp.o -c /home/pi/sound-pirates/Urho3D/src/instructionsStatements.cpp

CMakeFiles/sound-pirates.dir/instructionsStatements.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sound-pirates.dir/instructionsStatements.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/sound-pirates/Urho3D/src/instructionsStatements.cpp > CMakeFiles/sound-pirates.dir/instructionsStatements.cpp.i

CMakeFiles/sound-pirates.dir/instructionsStatements.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sound-pirates.dir/instructionsStatements.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/sound-pirates/Urho3D/src/instructionsStatements.cpp -o CMakeFiles/sound-pirates.dir/instructionsStatements.cpp.s

CMakeFiles/sound-pirates.dir/main.cpp.o: CMakeFiles/sound-pirates.dir/flags.make
CMakeFiles/sound-pirates.dir/main.cpp.o: /home/pi/sound-pirates/Urho3D/src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/sound-pirates/Urho3D/current-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/sound-pirates.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sound-pirates.dir/main.cpp.o -c /home/pi/sound-pirates/Urho3D/src/main.cpp

CMakeFiles/sound-pirates.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sound-pirates.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/sound-pirates/Urho3D/src/main.cpp > CMakeFiles/sound-pirates.dir/main.cpp.i

CMakeFiles/sound-pirates.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sound-pirates.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/sound-pirates/Urho3D/src/main.cpp -o CMakeFiles/sound-pirates.dir/main.cpp.s

CMakeFiles/sound-pirates.dir/playNote.cpp.o: CMakeFiles/sound-pirates.dir/flags.make
CMakeFiles/sound-pirates.dir/playNote.cpp.o: /home/pi/sound-pirates/Urho3D/src/playNote.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/sound-pirates/Urho3D/current-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/sound-pirates.dir/playNote.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sound-pirates.dir/playNote.cpp.o -c /home/pi/sound-pirates/Urho3D/src/playNote.cpp

CMakeFiles/sound-pirates.dir/playNote.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sound-pirates.dir/playNote.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/sound-pirates/Urho3D/src/playNote.cpp > CMakeFiles/sound-pirates.dir/playNote.cpp.i

CMakeFiles/sound-pirates.dir/playNote.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sound-pirates.dir/playNote.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/sound-pirates/Urho3D/src/playNote.cpp -o CMakeFiles/sound-pirates.dir/playNote.cpp.s

CMakeFiles/sound-pirates.dir/sinewave.cpp.o: CMakeFiles/sound-pirates.dir/flags.make
CMakeFiles/sound-pirates.dir/sinewave.cpp.o: /home/pi/sound-pirates/Urho3D/src/sinewave.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/sound-pirates/Urho3D/current-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/sound-pirates.dir/sinewave.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sound-pirates.dir/sinewave.cpp.o -c /home/pi/sound-pirates/Urho3D/src/sinewave.cpp

CMakeFiles/sound-pirates.dir/sinewave.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sound-pirates.dir/sinewave.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/sound-pirates/Urho3D/src/sinewave.cpp > CMakeFiles/sound-pirates.dir/sinewave.cpp.i

CMakeFiles/sound-pirates.dir/sinewave.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sound-pirates.dir/sinewave.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/sound-pirates/Urho3D/src/sinewave.cpp -o CMakeFiles/sound-pirates.dir/sinewave.cpp.s

# Object files for target sound-pirates
sound__pirates_OBJECTS = \
"CMakeFiles/sound-pirates.dir/RtAudio.cpp.o" \
"CMakeFiles/sound-pirates.dir/defineNote.cpp.o" \
"CMakeFiles/sound-pirates.dir/fft.cpp.o" \
"CMakeFiles/sound-pirates.dir/findFreqMax.cpp.o" \
"CMakeFiles/sound-pirates.dir/instructionsStatements.cpp.o" \
"CMakeFiles/sound-pirates.dir/main.cpp.o" \
"CMakeFiles/sound-pirates.dir/playNote.cpp.o" \
"CMakeFiles/sound-pirates.dir/sinewave.cpp.o"

# External object files for target sound-pirates
sound__pirates_EXTERNAL_OBJECTS =

bin/sound-pirates: CMakeFiles/sound-pirates.dir/RtAudio.cpp.o
bin/sound-pirates: CMakeFiles/sound-pirates.dir/defineNote.cpp.o
bin/sound-pirates: CMakeFiles/sound-pirates.dir/fft.cpp.o
bin/sound-pirates: CMakeFiles/sound-pirates.dir/findFreqMax.cpp.o
bin/sound-pirates: CMakeFiles/sound-pirates.dir/instructionsStatements.cpp.o
bin/sound-pirates: CMakeFiles/sound-pirates.dir/main.cpp.o
bin/sound-pirates: CMakeFiles/sound-pirates.dir/playNote.cpp.o
bin/sound-pirates: CMakeFiles/sound-pirates.dir/sinewave.cpp.o
bin/sound-pirates: CMakeFiles/sound-pirates.dir/build.make
bin/sound-pirates: /opt/vc/lib/libbcm_host.so
bin/sound-pirates: /usr/lib/arm-linux-gnueabihf/libEGL.so
bin/sound-pirates: /usr/lib/arm-linux-gnueabihf/libGLESv2.so
bin/sound-pirates: /home/pi/Urho3D/lib/libUrho3D.a
bin/sound-pirates: /usr/lib/arm-linux-gnueabihf/libsfml-system.so
bin/sound-pirates: /usr/lib/arm-linux-gnueabihf/libsfml-window.so
bin/sound-pirates: /usr/lib/arm-linux-gnueabihf/libsfml-graphics.so
bin/sound-pirates: /usr/lib/arm-linux-gnueabihf/libsfml-network.so
bin/sound-pirates: /usr/lib/arm-linux-gnueabihf/libsfml-audio.so
bin/sound-pirates: CMakeFiles/sound-pirates.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/sound-pirates/Urho3D/current-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable bin/sound-pirates"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sound-pirates.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sound-pirates.dir/build: bin/sound-pirates

.PHONY : CMakeFiles/sound-pirates.dir/build

CMakeFiles/sound-pirates.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sound-pirates.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sound-pirates.dir/clean

CMakeFiles/sound-pirates.dir/depend:
	cd /home/pi/sound-pirates/Urho3D/current-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/sound-pirates/Urho3D/src /home/pi/sound-pirates/Urho3D/src /home/pi/sound-pirates/Urho3D/current-build /home/pi/sound-pirates/Urho3D/current-build /home/pi/sound-pirates/Urho3D/current-build/CMakeFiles/sound-pirates.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sound-pirates.dir/depend

