//  (C) Copyright Gennadiy Rozental 2002-2006.
//  (C) Copyright Gennadiy Rozental & Ullrich Koethe 2001.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at 
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for the library home page.



#define BOOST_TEST_MODULE SplashTests
#include <boost/test/unit_test.hpp>

#include <stdio.h>      /* printf */
#include <math.h>       /* sin */

#include <iostream>
#include <cstdlib>
#include <math.h>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <complex>     
#include <string>
#include <algorithm>
#include "defineNote.h"
using namespace std;

/**
 * Unit test to check that the input frequency tone matches up to its correpsonding note
 * 
 */


BOOST_AUTO_TEST_SUITE( test_suite2 )

BOOST_AUTO_TEST_CASE(mytest_1)
{
BOOST_CHECK_EQUAL('C', define_note(262)); //middle of band
}

BOOST_AUTO_TEST_CASE(mytest_2)
{
BOOST_CHECK_EQUAL('C', define_note(250)); // edge case 
}

BOOST_AUTO_TEST_CASE(mytest_3)
{
BOOST_CHECK_EQUAL('C', define_note(267)); // edge case 
}

BOOST_AUTO_TEST_CASE(mytest_4)
{
BOOST_CHECK_EQUAL('D', define_note(294)); //middle of band
}

BOOST_AUTO_TEST_CASE(mytest_5)
{
BOOST_CHECK_EQUAL('D', define_note(289)); // edge case 
}


BOOST_AUTO_TEST_CASE(mytest_6)
{
BOOST_CHECK_EQUAL('D', define_note(299)); // edge case 
}


BOOST_AUTO_TEST_CASE(mytest_7)
{
BOOST_CHECK_EQUAL('E', define_note(330)); //middle of band
}

BOOST_AUTO_TEST_CASE(mytest_8)
{
BOOST_CHECK_EQUAL('E', define_note(325)); // edge case 
}


BOOST_AUTO_TEST_CASE(mytest_9)
{
BOOST_CHECK_EQUAL('E', define_note(335)); // edge case 
}


BOOST_AUTO_TEST_CASE(mytest_10)
{
BOOST_CHECK_EQUAL('F', define_note(349)); //middle of band
}

BOOST_AUTO_TEST_CASE(mytest_11)
{
BOOST_CHECK_EQUAL('F', define_note(344)); // edge case 
}

BOOST_AUTO_TEST_CASE(mytest_12)
{
BOOST_CHECK_EQUAL('F', define_note(357)); // edge case 
}

BOOST_AUTO_TEST_CASE(mytest_13)
{
BOOST_CHECK_EQUAL('G', define_note(392)); //middle of band
}

BOOST_AUTO_TEST_CASE(mytest_14)
{
BOOST_CHECK_EQUAL('G', define_note(387)); // edge case 
}

BOOST_AUTO_TEST_CASE(mytest_15)
{
BOOST_CHECK_EQUAL('G', define_note(399)); // edge case 
}

BOOST_AUTO_TEST_CASE(mytest_16)
{
BOOST_CHECK_EQUAL('A', define_note(440)); //middle of band
}

BOOST_AUTO_TEST_CASE(mytest_17)
{
BOOST_CHECK_EQUAL('A', define_note(435)); // edge case 
}

BOOST_AUTO_TEST_CASE(mytest_18)
{
BOOST_CHECK_EQUAL('A', define_note(445)); // edge case 
}

BOOST_AUTO_TEST_CASE(mytest_19)
{
BOOST_CHECK_EQUAL('B', define_note(494)); //middle of band
}

BOOST_AUTO_TEST_CASE(mytest_20)
{
BOOST_CHECK_EQUAL('B', define_note(481)); // edge case
}

BOOST_AUTO_TEST_CASE(mytest_21)
{
BOOST_CHECK_EQUAL('B', define_note(499)); // edge case
}

BOOST_AUTO_TEST_CASE(mytest_22)
{
BOOST_CHECK_EQUAL('N', define_note(0)); //zero
}

BOOST_AUTO_TEST_CASE(mytest_23)
{
BOOST_CHECK_EQUAL('N', define_note(270)); //outside all defined notes
}


BOOST_AUTO_TEST_CASE(mytest_24)
{
BOOST_CHECK_EQUAL('N', define_note(-1)); //negative number
}

BOOST_AUTO_TEST_SUITE_END()
