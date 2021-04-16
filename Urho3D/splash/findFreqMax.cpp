/**
 * @file fft.cpp
 * FFT function. Takes input buffer and performs Fast Fourier Transform to shift into frequency 
 * domain. Produces new array with frequencies as position and amplitude as value
 * called by processBuffer function
 */
 
#include <vector>

int findFreqMax(int freqMax, int i, std::vector<double> &window){

 freqMax = i* 44100.0 / window.size();

return freqMax;
}
