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
#include <complex>     
#include <string>
#include "audioIn.h"
#include "fft.h"
#include "playNote.h"
#include "instructionsStatements.h"



#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>


#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <poll.h>
#include <thread>
#include <chrono>
#include <signal.h>

int freqMax;  
std::vector<signed short> window;


int pipefds[2];

const int bandNumber = 128;
unsigned int sampleRate = 44100;
unsigned int bufferFrames = 4410; // 512 sample frames
volatile sig_atomic_t stop;


/**
 * inthand function allows close of terminal with ctrl C
 * 
 */

void inthand(int signum) {
    stop = 1;
return;
}

/**
 * processBuffer fuction. Calls fft, takes output of fft and sorts max freq into note to report
 * output freqMax
 * called by record
 * 
 */
int processBuffer()
{  
    ::freqMax;
    ::pipefds[2];

    std::vector<double> output;
    fft(window, output);

    freqMax = 0;
    int freqMaxIndex = 51;
    int amplitudeThreshold = 10;

    for (int i = 51; i < 100; i++) {        
        if (output[i] > output[freqMaxIndex] && output[i] > amplitudeThreshold){
            freqMaxIndex = i;
            freqMax = i*44100.0/window.size();            
        }
    }     
            
    if (freqMax > 249 && freqMax < 268 ){ //could be 256 instead of 249
        freqMax = 262;
        write(pipefds[1], "C4", sizeof("C4"));
    }
    else if (freqMax > 288 && freqMax < 300){
        freqMax = 294;
        write(pipefds[1], "D4", sizeof("D4"));
    }
    else if (freqMax > 324 && freqMax < 336){
        freqMax = 330;
        write(pipefds[1], "E4", sizeof("E4"));
    }  
    else if (freqMax  > 343 && freqMax < 349){
        freqMax  = 349;
        write(pipefds[1], "F4", sizeof("F4"));
    }  
    else if (freqMax > 386 && freqMax < 398){
        freqMax = 392;
        write(pipefds[1], "G4", sizeof("G4"));
    }    
    else if (freqMax > 434 && freqMax < 446){
        freqMax = 440;
        write(pipefds[1], "A4", sizeof("A4"));
    }  
    else if (freqMax > 482 && freqMax < 500){
        freqMax = 494;
        write(pipefds[1], "B4", sizeof("B4"));
    }
    else{
        write(pipefds[1], "None", sizeof("None"));
        printf("Wrote None \n");
    }
    
    std::cout << freqMax << std::endl;
    return freqMax, pipefds[2];
}

/**
 * record function. Activate the audio input and write to buffer
 * called by audioIn
 *  
 */
int record(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
            double streamTime, RtAudioStreamStatus status, void *userData)
{
    printf("Called Record \n");
    if (status) {
        std::cout << "Stream overflow detected!" << std::endl;
    }

    int i = 0;
    signed short *a = (signed short*)inputBuffer;

    //Add nBufferFrames values from the input buffer into window
    while (window.size() < nBufferFrames*2 && i < nBufferFrames) {
        window.push_back(a[i++]);
    }

    processBuffer();
   
    if (window.size() == nBufferFrames*2) {
        //get rid of the first half of window
        window.erase(window.begin(), window.begin() + nBufferFrames);
    }

    return 0;
}



/**
 * audioIn function. 
 * calls record, which calls processBuffer,which calls fft
 * called by URHO3D_DEFINE_APPLICATION_MAIN(HelloWorld)
 * 
 */
int audioIn()
{  
    //access audio device
    RtAudio adc;
    if (adc.getDeviceCount() < 1) {
        std::cout << "No audio devices found!\n";
        return -1;
    }

    //Print device infos  
    unsigned int numDev = adc.getDeviceCount();
    RtAudio::DeviceInfo di;
    for ( unsigned int i = 0; i < numDev; ++i )
    {
        // use the Debugger if you need to know deviceID
        std::cout << "Device info" << std::endl;
        di = adc.getDeviceInfo( i );
        //std::cout << di << std::endl;
    }
   
    //Set parameters
    RtAudio::StreamParameters parameters;
    parameters.deviceId = adc.getDefaultInputDevice();
    parameters.nChannels = 1;
    parameters.firstChannel = 0;
    
    std::thread t1(instructionsStatements);
    t1.join();
   

    try {
        //Calls the record function
        adc.openStream(NULL, &parameters, RTAUDIO_SINT16, sampleRate, &bufferFrames, &record);
        adc.startStream();
        std::cout << adc.getVersion();
    } catch (RtAudioError& e) {
        e.printMessage();
        return -1;
    }

    char input;
    std::cout << "\nRecording ... press <enter> to quit.\n";
    
    signal(SIGINT, inthand);
    stop = 0;
    while(!stop){}
    adc.closeStream();
    return 0;
}



