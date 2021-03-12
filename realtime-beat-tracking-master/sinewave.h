#ifndef SINEWAVE_H
#define SINEWAVE_H

#include <math.h>

namespace sinewave{
	#define TWOPI 6.283185037

	short SineWave(double time, double freq, double amp) {
		short result;
		double tpc = 44100 / freq; 
		double cycles = time /tpc;
		double rad = TWOPI * cycles;
		short amplitude = 32767 * amp;
		result = amplitude *sin(rad);
		return result;
	}
}

#endif
