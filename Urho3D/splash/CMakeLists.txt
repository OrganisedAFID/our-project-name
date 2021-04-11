##
# Set minimum version
#
cmake_minimum_required (VERSION 3.0.0)
if (COMMAND cmake_policy)
    cmake_policy (SET CMP0003 NEW)
    if (CMAKE_VERSION VERSION_GREATER 2.8.12 OR CMAKE_VERSION VERSION_EQUAL 2.8.12)
        # INTERFACE_LINK_LIBRARIES defines the link interface
        cmake_policy (SET CMP0022 NEW)
    endif ()
    if (CMAKE_VERSION VERSION_GREATER 3.0.0 OR CMAKE_VERSION VERSION_EQUAL 3.0.0)
        # Disallow use of the LOCATION target property - therefore we set to OLD as we still need it
        cmake_policy (SET CMP0026 OLD)
        # MACOSX_RPATH is enabled by default
         # cmake_policy (SET CMP0042 NEW)
    endif ()
endif ()

##
# Set project name
project (Splash)
#

##
# Define target name
set (TARGET_NAME Splash)
#

##
# Recurse into the "test" subdirectory
#
add_subdirectory (test)


##
# Enable and add fft and define note function tests 
#
enable_testing ()


##
# Does the fft function work?
#
add_test (NAME FFT_TEST COMMAND FFT_TEST)

##
# Does the define_note function work?
#
add_test (NAME DEFINE_NOTE_TEST COMMAND DEFINE_NOTE_TEST)

##
# Set CMake modules search path to find Urho3D-CMake-common module
#
set (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake/Modules)

##
# Include Urho3D Cmake common module
#
include (Urho3D-CMake-common)

##
# Find Urho3D library
#
find_package (Urho3D REQUIRED)
include_directories (${URHO3D_INCLUDE_DIRS})


##
# Define source files
#
define_source_files ()

##
# Setup target with resource copying
#
setup_main_executable ()

##
# Activate C++11
#
add_compile_options ("-std=c++11")

##
# Find directory containing fftw3.h library required to perform fast fourier transform
#
find_path (FFTW_INCLUDES fftw3.h)
find_library (FFTW_LIBRARIES NAMES fftw3)

##
# Set CMake modules search path to find SFML; system; window; graphics; graphics; network and audio packages
# required for audio processing
#
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

##
# Find SFML; system; window; graphics; graphics; network and audio packages required for audio processing
#
find_package(SFML 2.0 REQUIRED system window graphics network audio)

##
# Find libfftw3;librtaudio5a;asound; pthread and jack ;libraries required for audio processing
#
FIND_LIBRARY(REQ_LIBRARIES NAMES libfftw3 librtaudio5a asound pthread jack)

##
# Specify Splash target to use SFML; rtaudio; fftw3; asound; pthread and jack libraries
#
target_link_libraries(Splash ${SFML_LIBRARIES} rtaudio fftw3 asound pthread jack)


##
# Set RtAudio flags
#
find_package(ALSA)
if (ALSA_FOUND)
	find_package(Threads REQUIRED CMAKE_THREAD_PREFER_PTHREAD)
	include_directories(SYSTEM ${ALSA_INCLUDE_DIR})
	list(APPEND OAML_LIBS ${ALSA_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})
	add_definitions(-D__LINUX_ALSA__)
	message(STATUS "RtAudio: Using Linux ALSA")
endif()
if (APPLE)
	find_library(COREAUDIO_LIB CoreAudio)
	find_library(COREFOUNDATION_LIB CoreFoundation)
	if (COREAUDIO_LIB AND COREFOUNDATION_LIB)
		list(APPEND OAML_LIBS ${COREAUDIO_LIB} ${COREFOUNDATION_LIB})
		add_definitions(-D__MACOSX_CORE__)
		message(STATUS "RtAudio: Using OSX CoreAudio")
	endif()
endif (APPLE)
if (WIN32)
	list(APPEND OAML_LIBS winmm ole32)

	add_definitions(-D__WINDOWS_DS__)
	message(STATUS "RtAudio: Using Windows DirectSound")
	list(APPEND OAML_LIBS dsound)

	add_definitions(-D__WINDOWS_WASAPI__)
	message(STATUS "RtAudio: Using Windows WASAPI")
	list(APPEND OAML_LIBS uuid ksuser)
endif (WIN32)