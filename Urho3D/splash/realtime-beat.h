#include "RtAudio.h"
#include <fftw3.h>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <cstring>
#include <stdio.h>
#include <SFML/Audio.hpp>
#include <vector>
//#include "sinewave.h"
#include <iostream>
#include <complex>    
#include <fstream>
#include<sstream>  
#include <string>



const float pi = 3.14159265;

unsigned int sampleRate = 44100;
unsigned int bufferFrames = 4410; // 512 sample frames
const int bandNumber = 128;
const int width = bufferFrames / bandNumber;
const int historyValues = sampleRate / (bufferFrames * 2);

const float nodeRadius = 100;
const float angularWidth = 2.0 * pi / bandNumber;
const float barWidth = angularWidth * nodeRadius;

int a = 0;
std::vector<signed short> window;
std::vector<double> v;
std::vector<std::vector<double>> historyBuffer; //rows are frequency, cols are histories
std::vector<double> meanHistory(bandNumber);

void fft(std::vector<signed short> &rawValues, std::vector<double> &output) //move this over to GPU_FFT
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
}







int record(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
            double streamTime, RtAudioStreamStatus status, void *userData)
{
    if (status) {
        std::cout << "Stream overflow detected!" << std::endl;
    }

    int i = 0;
    signed short *a = (signed short*)inputBuffer;

    while (window.size() < nBufferFrames*2 && i < nBufferFrames) {
        window.push_back(a[i++]);
    }

    processBuffer();
//add a function for processing the data here
    if (window.size() == nBufferFrames*2) {
        window.erase(window.begin(), window.begin() + nBufferFrames);
    }

    return 0;
}

int main()
{
    //access audio device
    RtAudio adc;
    if (adc.getDeviceCount() < 1) {
        std::cout << "No audio devices found!\n";
        return -1;
    }

    RtAudio::StreamParameters parameters;
    parameters.deviceId = adc.getDefaultInputDevice();
    parameters.nChannels = 1;
    parameters.firstChannel = 0;


    try {
        adc.openStream(NULL, &parameters, RTAUDIO_SINT16,
                        sampleRate, &bufferFrames, &record);
        adc.startStream();
        std::cout << adc.getVersion();
    } catch (RtAudioError& e) {
        e.printMessage();
        return -1;
    }

    char input;
    std::cout << "\nRecording ... press <enter> to quit.\n";
    //processBuffer();
    sf::RenderWindow window(sf::VideoMode(1280, 900), "FFT visualiser");

    window.setVerticalSyncEnabled(true);
    int frameCounter = 0;
    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        frameCounter++;
        window.clear();

    }
    return 0;
}
