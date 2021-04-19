/**
 * @file fft.cpp
 * FFT function. Takes input buffer and performs Fast Fourier Transform to shift into frequency 
 * domain. Produces new array with frequencies as position and amplitude as value
 * called by processBuffer function
 */
 
#include <vector>
#include <chrono>
#include <iostream>
#include <fstream>
using namespace std;

int findFreqMax(int freqMax, int i, std::vector<double> &window){

    FILE *pFile;
    pFile = fopen ("finfFrewqMax.txt","a");    


    using namespace std::literals::chrono_literals;
    auto startMax = std::chrono::high_resolution_clock::now();

    freqMax = i* 44100.0 / window.size();

    auto endMax = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> durationMax = endMax -startMax;
    std::cout << "duration of finding maximum frequency" << durationMax.count() << "s" <<std::endl;
  
    fprintf(pFile,"%f\n",durationMax.count());
    fflush(pFile);
return freqMax;
}
