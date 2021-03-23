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
#include <sstream>  
#include <string>
#include "lol.h"

/*

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



int processBuffer()
{
    int i;
    int j;
    int freqMaxIndex = 0;
    int freqMax = 0;   
    int n = window.size() / 2;

    std::vector<double> output;
    fft(window, output);
    
    for (i = 0; i < n; i++) {

        
        if (i > 50 && i < 100){
            if (output[i] > output[freqMaxIndex]){
                freqMaxIndex = i;
                freqMax = i*44100.0/(n*2);
                
            }
        }   
    /*
    if ( freqMax > 256 && freqMax < 268 ){
        freqMax = 262;
        std::string C4 = std::to_string(freqMax);
        //std::cout << freqMax;
        write(pipefds[1], "C4", sizeof("C4"));

    }
    else if (freqMax > 288 && freqMax < 300){
        freqMax = 294;
        std::string D4 = std::to_string(freqMax);
        //std::cout << freqMax;
        write(pipefds[1], "D4", sizeof("D4"));

    }
    else if (freqMax > 324 && freqMax < 336){
        freqMax = 330;
        std::string E4 = std::to_string(freqMax);
        //std::cout << freqMax;
        write(pipefds[1], "E4", sizeof("E4"));
    }  
    else if (freqMax  > 343 && freqMax < 349){
        freqMax  = 349;
        std::string F4 = std::to_string(freqMax);
        //std::cout << freqMax;
        write(pipefds[1], "F4", sizeof("F4"));
    }  
    else if (freqMax > 386 && freqMax < 398){
        freqMax = 392;
        std::string G4 = std::to_string(freqMax);
         //std::cout << freqMax;
        write(pipefds[1], "G4", sizeof("G4"));
    }    
    else if (freqMax > 334 && freqMax < 446){
        freqMax = 440;
        std::string A4 = std::to_string(freqMax);       
         //std::cout << freqMax;
        write(pipefds[1], "A4", sizeof("A4"));
    }  
    else if (freqMax > 482 && freqMax < 500){
        freqMax = 494;
        std::string B4 = std::to_string(freqMax);
                //std::cout << freqMax;
        write(pipefds[1], "B4", sizeof("B4"));
    }
    else{
        std::string no = std::to_string(freqMax);
        std::cout << "std::cout: " << no << '\n';
    //std::cout << freqMax;
        write(pipefds[1], "None", sizeof("None"));
    }  
    //std::cout << X << std::endl;
    }
  std::cout << freqMax << std::endl;
    return freqMax;

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


int lol()
{
    
          std::cout << "HELLO THERE" << std::endl;
    //access audio device
   RtAudio adc;
    if (adc.getDeviceCount() < 1) {
        std::cout << "No audio devices found!\n";
        std::cout << "Current API : " << adc.getCurrentApi() << std::endl;
        std::cout << "index of the default input device.: " << adc.getDefaultInputDevice() << std::endl;
        return -1;
    }
    //unsigned int i=0;
    
        std::cout << "Current API : " << adc.getCurrentApi() << std::endl;
        std::cout << "index of the default input device.: " << adc.getDefaultInputDevice() << std::endl;
         std::cout << "Device Count " << adc.getDeviceCount() << std::endl;
         
         unsigned int numDev = adc.getDeviceCount();
RtAudio::DeviceInfo di;
for ( unsigned int i = 0; i < numDev; ++i )
{
    // use the Debugger if you need to know deviceID
    std::cout << "Device info" << std::endl;
    di = adc.getDeviceInfo( i );
    std::cout << " " << std::endl;
    //printf(di);
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
*/

