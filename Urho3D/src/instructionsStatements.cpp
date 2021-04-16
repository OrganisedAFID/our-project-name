/**
 * @file instructionsStatement.cpp
 * instructionsStatement function. Prints player instructions on screen to alert when note given and expected
 */
 
#include <fftw3.h>
#include "RtAudio.h"
#include <iostream>
#include "audioIn.h"
#include "fft.h"
#include "playNote.h"
#include <chrono>
#include <thread>


void instructionsStatements(){
   
    std::cout << "Playing random note (in the 4th octave)" << "\n";
    playNote();
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    std::cout << "Now you play back in..." << "\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    for (int i=5; i>0; --i) {
    std::cout << i << std::endl;
    std::this_thread::sleep_for (std::chrono::seconds(1));
  }
  std::cout << "Go!" << "\n";
      
return;
}
