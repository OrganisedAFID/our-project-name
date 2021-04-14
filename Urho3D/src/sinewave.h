/**
 * \headerfile sinwave.h "sinwave.h"
 * header file that generates sinewave of with a specfic frequency 
 */


#ifndef SINEWAVE_H
#define SINEWAVE_H

#include <math.h>

namespace sound{
	#define TWOPI 6.283185037

	short SineWave(double time, double freq, double amp) {
		short result;
		double tpc = 88200 / freq; 
		double cycles = time /tpc;
		double rad = TWOPI * cycles;
		short amplitude = 32767 * amp;
		result = amplitude *sin(rad);
		return result;
	}
}

#endif

