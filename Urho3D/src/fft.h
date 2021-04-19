/**
 * \headerfile fft.h "fft.h"
 * header file for fft function
 */

#ifndef FFT_H
#define FFT_H
/**
 * fast fourier transform to change sound buffer input to frequency domain
 */
void fft(std::vector<double> &rawValues, std::vector<double> &output); 
#endif

