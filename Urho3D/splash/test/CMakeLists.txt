find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

include_directories(${DEMO_SOURCE_DIR}/splash ${Boost_INCLUDE_DIRS})
add_definitions (-DBOOST_TEST_DYN_LINK)
include_directories(${CMAKE_SOURCE_DIR})
link_directories(${CMAKE_SOURCE_DIR})
add_executable (Test test.cpp fft.h fft.cpp)
find_path (FFTW_INCLUDES fftw3.h)
find_library (FFTW_LIBRARIES NAMES fftw3)
FIND_LIBRARY(REQ_LIBRARIES NAMES libfftw3)
target_link_libraries (Test
	${Boost_FILESYSTEM_LIBRARY}
	${Boost_SYSTEM_LIBRARY}
	${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
	fftw3
	
	 )



