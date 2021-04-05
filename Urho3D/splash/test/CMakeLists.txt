find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

include_directories(${DEMO_SOURCE_DIR}/splash ${Boost_INCLUDE_DIRS})
add_definitions (-DBOOST_TEST_DYN_LINK)
include_directories(${CMAKE_SOURCE_DIR})

link_directories(${CMAKE_SOURCE_DIR})
set( header_include  ../)

add_executable (FFT_TEST fft_test.cpp ${header_include}fft.h ${header_include}fft.cpp )
add_executable (DEFINE_NOTE_TEST define_note_test.cpp ${header_include}defineNote.h ${header_include}defineNote.cpp)

find_path (FFTW_INCLUDES fftw3.h)
find_library (FFTW_LIBRARIES NAMES fftw3)
FIND_LIBRARY(REQ_LIBRARIES NAMES libfftw3)
target_link_libraries (FFT_TEST
	${Boost_FILESYSTEM_LIBRARY}
	${Boost_SYSTEM_LIBRARY}
	${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
	fftw3
	
	 )

target_link_libraries (DEFINE_NOTE_TEST
	${Boost_FILESYSTEM_LIBRARY}
	${Boost_SYSTEM_LIBRARY}
	${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
	
	 )


