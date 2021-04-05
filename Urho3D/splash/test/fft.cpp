

#include <fftw3.h>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <complex>     
#include <string>
#include <algorithm>




void fft(std::vector<double> &rawValues, std::vector<double> &output) //move this over to GPU_FFT
{
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
    
    int maxElementIndex = std::max_element(output.begin(),output.end()) - output.begin();
   // std::cout << "maxElementIndex:" << maxElementIndex << '\n';
    
    return;// maxElementIndex;
}
