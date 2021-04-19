/**
 * @file fft.cpp
 * FFT function. Takes input buffer and performs Fast Fourier Transform to shift into frequency 
 * domain. Produces new array with frequencies as position and amplitude as value
 * called by processBuffer function
 */
 
#include <vector>

int freqMaxIndex = 51;
int amplitudeThreshold = 45000; 




int findFreqMax(int freqMax,std::vector<double> output, std::vector<double> &window){

 for (int i = 51; i < 100; i++) //i values bewteen 51 and 99 value means that loop is starting to look for the highest frequency values between 255 and 495 hertz, respectively. 
    {

          
    
        if (output[i] >= output[freqMaxIndex] && output[i] > amplitudeThreshold)
        {
            freqMaxIndex = i;  
            freqMax = i* 44100.0 / window.size();      //dividing sampling frquency with buffer length to get frequency resoltion then muliplting with the index values
                                                      //(of the vector "output" from 51 and 99 to find max frequency between 255 and495 hertz        
        }
    } 


return freqMax;
}
