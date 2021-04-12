/**
 * @file playNote.cpp
 * playNote function. Plays random note for player to match
 * outputs string for note played
 */

#include <iostream>
#include <stdio.h>
#include <vector>
#include <SFML/Audio.hpp>
#include "sinewave.h"
#include <chrono>
#include <thread>

/**
 * Define "OutputNote" variable to define letter note that is played to user
 */
 char playNote(){
    char OutputNote;
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

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
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
        OutputNote = 'N';
    }
        
    std::cout << "Note played: " << OutputNote << "\n";

return OutputNote;

    
}
