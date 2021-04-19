/**
 * @file fft.cpp
 * FFT function. Takes input buffer and performs Fast Fourier Transform to shift into frequency 
 * domain. Produces new array with frequencies as position and amplitude as value
 * called by processBuffer function
 */


#include "RtAudio.h"
#include <fftw3.h>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <cstring>
#include <stdio.h>
#include <SFML/Audio.hpp>
#include <vector>
#include <complex>     
#include <string>
#include "audioIn.h"
#include "chrono"
#include <iostream>
#include <fstream>
using namespace std;

void fft(std::vector<double> &rawValues, std::vector<double> &output) 
{
    FILE *pFile;
    pFile = fopen ("Fft.txt","a");    


    using namespace std::literals::chrono_literals;
    auto startFft = std::chrono::high_resolution_clock::now();

    
    int n = rawValues.size();
    int i;
    fftw_complex *inputChannel = new fftw_complex[n];
    fftw_complex *outputChannel = new fftw_complex[n];

    for (i = 0; i < n; i++) {
        inputChannel[i][0] = rawValues[i];
        inputChannel[i][1] = 0;
        outputChannel[i][0] = 0;
        outputChannel[i][1] = 0;
    }
    fftw_plan p = fftw_plan_dft_1d(n, inputChannel, outputChannel, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(p);
    for ( i = 0; i < n / 2; i++) {
        output.push_back(sqrt(outputChannel[i][0] * outputChannel[i][0] + outputChannel[i][1] * outputChannel[i][1]));
        }
    output[0] = 0;
    delete[] inputChannel;
    delete[] outputChannel;
    
    auto endFft = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> durationFft = endFft -startFft;
    std::cout << "duration of fft" << durationFft.count() << "s" <<std::endl;
  
    fprintf(pFile,"%f\n",durationFft.count());
    fflush(pFile);
    return;
}
