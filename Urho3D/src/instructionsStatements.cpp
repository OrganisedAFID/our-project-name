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
   /// display message for player giving visual cues to assist in  timing
   /// can be altered to display actual note name in future if function required in future 
   /// releases
    std::cout << "Playing random note (in the 4th octave)" << "\n";
    playNote();
    
    /// display message to cue player to play note with countdown
    /// 5 to 0 in 3 seconds followed by go
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    std::cout << "Now you play back in..." << "\n";

    /// 
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    for (int i=5; i>0; --i) {
    std::cout << i << std::endl;
    std::this_thread::sleep_for (std::chrono::seconds(1));
  }
  std::cout << "Go!" << "\n";
      
return;
}
