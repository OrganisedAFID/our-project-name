/**
 * @file freqMax_test.cpp
 * Unit test to check that finds the index of the highest value that meets the amplitude threshold and uses it to calculate the maximum frequency
 */

/************************************************************************/
/*! 
*  (C) Copyright Gennadiy Rozental 2002-2006.
*  (C) Copyright Gennadiy Rozental & Ullrich Koethe 2001.
*  Distributed under the Boost Software License, Version 1.0.
*  (See accompanying file LICENSE_1_0.txt or copy at 
*  http://www.boost.org/LICENSE_1_0.txt)

* See http://www.boost.org/libs/test for the library home page.
*/
/************************************************************************/


#define BOOST_TEST_MODULE MainTests
#include <boost/test/unit_test.hpp>
#include <vector>
#include "findFreqMax.h"
using namespace std;


int freqMax = 0;

std::vector<double> window(8820, 0); // vector simulates the window (buffer) variable which has a length of 8820



BOOST_AUTO_TEST_SUITE( test_suite1 )


BOOST_AUTO_TEST_CASE(mytest_1)
{
std::vector<double> output(100, 40000); // vector simulates 100 incomming fft values (with amplitude below the above the threshold of 45000)
output[60] = 50000; //put max frequency at index 60 which corresponds to 300Hz
    
BOOST_CHECK_EQUAL(300, findFreqMax(freqMax,output,window));

}


BOOST_AUTO_TEST_CASE(mytest_2)
{
std::vector<double> output(100, 40000); // vector simulates 100 incomming fft values (with amplitude below the above the threshold of 45000)
output[10] = 50000; //put max frequncy at index 10 which corresponds to 50Hz
    
BOOST_CHECK_EQUAL(0, findFreqMax(freqMax,output,window)); //Case below detection threshold of 255Hz

}


BOOST_AUTO_TEST_CASE(mytest_3)
{
std::vector<double> output(100, 40000); // vector simulates 100 incomming fft values (with amplitude below the above the threshold of 45000)
 for (int index = 60; index <= 75; index++){
   output[index] = 50000; //put indinces 60 to 70 above amplitude threshold (corresponds to frequencies 300 to 375)
    }
    
    
output[70] = 50004; //put max frequency at index 70 which corresponds to 350Hz 



BOOST_CHECK_EQUAL(350, findFreqMax(freqMax,output,window)); 

}

BOOST_AUTO_TEST_CASE(mytest_4)
{
    std::vector<double> output(100, 40000); // vector simulates 100 incomming fft values (with amplitude below the above the threshold of 45000)
output[51] = 50000; //put max frequency at index 51 which corresponds to 225Hz
    
BOOST_CHECK_EQUAL(255, findFreqMax(freqMax,output,window)); //Edge case

}

BOOST_AUTO_TEST_CASE(mytest_5)
{
    std::vector<double> output(100, 40000); // vector simulates 100 incomming fft values (with amplitude below the above the threshold of 45000)
output[99] = 50000; //put max frequency at index 51 which corresponds to 500Hz
    
BOOST_CHECK_EQUAL(495, findFreqMax(freqMax,output,window)); //Edge case

}

BOOST_AUTO_TEST_CASE(mytest_6)
{
std::vector<double> output(100, 40000); // vector simulates 100 incomming fft values (with amplitude below the above the threshold of 45000)
 for (int index = 0; index <= 99; index++){
   output[index] = 0; //simulation zero input
    }
    
BOOST_CHECK_EQUAL(0, findFreqMax(freqMax,output,window)); //no input, amplitude below detection threshold 

}

BOOST_AUTO_TEST_SUITE_END()
