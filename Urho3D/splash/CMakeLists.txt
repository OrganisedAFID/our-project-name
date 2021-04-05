# Set project name
project (Splash)
# Define target name
set (TARGET_NAME Splash)
######################################


add_subdirectory (test)
enable_testing ()
add_test (NAME MyTest COMMAND Test)


# Set minimum version
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
# Set CMake modules search path
set (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake/Modules)
# Include Urho3D Cmake common module
include (Urho3D-CMake-common)
# Find Urho3D library
find_package (Urho3D REQUIRED)
include_directories (${URHO3D_INCLUDE_DIRS})
# Define source files
define_source_files ()
# Setup target with resource copying
setup_main_executable ()
# Activate C++11
add_compile_options ("-std=c++11")

# Setup SDK install destinations
set (PATH_SUFFIX Urho3D)
if (WIN32)
    set (SCRIPT_EXT .bat)
    if (CMAKE_HOST_WIN32)
        set (PATH_SUFFIX .)
        if (URHO3D_64BIT AND CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
            string (REPLACE " (x86)" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")
        endif ()
    endif ()
else ()
    set (SCRIPT_EXT .sh)
endif ()
if (URHO3D_64BIT)
    # Install to 'lib64' when one of these conditions is true
    if ((MINGW AND CMAKE_CROSSCOMPILING) OR URHO3D_USE_LIB64_RPM OR (HAS_LIB64 AND NOT URHO3D_USE_LIB_DEB))
        set (LIB_SUFFIX 64)
    endif ()
endif ()



find_path (FFTW_INCLUDES fftw3.h)

find_library (FFTW_LIBRARIES NAMES fftw3)


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.0 REQUIRED system window graphics network audio)
FIND_LIBRARY(REQ_LIBRARIES NAMES libfftw3 librtaudio5a asound pthread jack)

target_link_libraries(Splash ${SFML_LIBRARIES} rtaudio fftw3 asound pthread jack)

# add_definitions(-D__HAVE_RTAUDIO)
# add_dependencies(Splash asound pthread)



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