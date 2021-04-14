##
# Finds boost, triggers an error otherwise
#
find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

##
# Include directories containing source directory (splash) boost include directories 
#
include_directories(${DEMO_SOURCE_DIR}/splash ${Boost_INCLUDE_DIRS})

##
# Define "-DBOOST_TEST_DYN_LINK" flag to build/use dynamic library.
#
add_definitions (-DBOOST_TEST_DYN_LINK)

##
# Inlcude the cmake source directory 
#
include_directories(${CMAKE_SOURCE_DIR})

##
# Specify the path in which the linker should search for libraries.
#
link_directories(${CMAKE_SOURCE_DIR})

##
# Set the include path to find the test's header files
#
set( header_include  ../)

##
# creates the executable for the fft and define note function tests
#
add_executable (FFT_TEST fft_test.cpp ${header_include}fft.h ${header_include}fft.cpp )
add_executable (DEFINE_NOTE_TEST define_note_test.cpp ${header_include}defineNote.h ${header_include}defineNote.cpp)

##
# Specify FFT test target to use Boost's filesystem; system and unit test framework libraries
#
target_link_libraries (FFT_TEST
	${Boost_FILESYSTEM_LIBRARY}
	${Boost_SYSTEM_LIBRARY}
	${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
	fftw3	
	 )

##
# Specify Define note test target to use Boost's filesystem; system and unit test framework libraries
#
target_link_libraries (DEFINE_NOTE_TEST
	${Boost_FILESYSTEM_LIBRARY}
	${Boost_SYSTEM_LIBRARY}
	${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}	
	 )


