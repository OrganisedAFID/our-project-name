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
#include "sinewave.h"
#include <complex>     
#include <string>
#include "lol.h"
#include "fft.h"


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

char note;
char OutputNote;
/**
 * playNote function. plays random note for player to match
 * otputs string for note played
 */
 void playNote(){
    
     srand (time(NULL));
  	int noteNum[7] = {262, 294, 330, 349, 392, 440, 494}; //frequencies responding to 4th octave
  	int RandIndex = rand() % 6; //generate a random integer between 0 and 7
    sf::SoundBuffer buffer;
	std::vector<sf::Int16> samples;
	
	for (int i = 0; i < 44100; i++) {
		samples.push_back(sound::SineWave(i, noteNum[RandIndex], 1));
	}

	buffer.loadFromSamples(&samples[0], samples.size(), 2, 44100);

	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.play();

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    if ( RandIndex == 0 ){

        OutputNote = 'C';

    }
    else if (RandIndex == 1){
    OutputNote =  'D';


    }
    else if (RandIndex == 2){
   OutputNote = 'E';

    }  
    else if (RandIndex == 3){

        OutputNote = 'F';
      
    }  
    else if (RandIndex == 4){

        OutputNote = 'G';
    }    
    else if (RandIndex == 5){

        OutputNote = 'A';
  
    }  
  else if (RandIndex == 6){

        OutputNote = 'B';
    }
    else{
                note = 'N';
            }
        
     std::cout << "Note played: " << OutputNote << "\n";
 
    
 
return;

    
}
