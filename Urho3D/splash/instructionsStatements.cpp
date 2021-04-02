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


/** 
 * instructionsStatement function. Prints player instructions on screen to alert when note given and expected
 * 
 */
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
