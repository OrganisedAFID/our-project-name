/**
 * @file freqMax_test.cpp
 * Unit test to check that the freqMax outputs the maximum frequency
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


#define BOOST_TEST_MODULE SplashTests
#include <boost/test/unit_test.hpp>
#include <vector>
#include "findFreqMax.h"
using namespace std;

int i =9;
int freqMaxIndex = 0;
int amplitudeThreshold = 0;
int detectfreqMax = 0;
int freqMax = 0;

std::vector<double> window={1,1,1,1,1,1,1,1,1,6000,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

BOOST_AUTO_TEST_SUITE( test_suite3 )

BOOST_AUTO_TEST_CASE(mytest_1)
{

    
    //findFreqMax(detectfreqMax, i, window); 
               
    
BOOST_CHECK_EQUAL(15876,findFreqMax(detectfreqMax,i,window));

}

BOOST_AUTO_TEST_SUITE_END()
