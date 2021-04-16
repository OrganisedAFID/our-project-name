/**
 * \headerfile sinwave.h "sinwave.h"
 * header file that generates sinewave of with a specfic frequency 
 */


#ifndef SINEWAVE_H
#define SINEWAVE_H

#include <math.h>

namespace sound
{
	short SineWave(double time, double freq, double amp);
}

#endif

