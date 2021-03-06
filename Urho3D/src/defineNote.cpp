/**
 * @file define_note.cpp
 * define_note function. Takes input maximum frequency and checks what note (in the 4th octave) that it corresponds to through a series of if else statements. 
 * Returns char variable note_string that correponses to note detected. 
 */


#include <stdio.h>

/**
 * Define "note_string" variable to define letter note for each frequecy range
 */
char note_string;

char define_note(int freqMax){
if (freqMax > 249 && freqMax < 268 ){ 
        freqMax = 262;
        note_string = 'C';
    }
    else if (freqMax > 288 && freqMax < 300){
        freqMax = 294;
        note_string = 'D';
  
    }
    else if (freqMax > 324 && freqMax < 336){
        freqMax = 330;
        note_string = 'E';
    
    }  
    else if (freqMax  > 343 && freqMax < 358){
        freqMax  = 349;
        note_string = 'F';
       
    }  
    else if (freqMax > 386 && freqMax < 400){
        freqMax = 392;
        note_string = 'G';
        
    }    
    else if (freqMax > 434 && freqMax < 446){
        freqMax = 440;
        note_string = 'A';
      
    }  
    else if (freqMax > 480 && freqMax < 500){
        freqMax = 494;
        note_string = 'B';
   
    }
    else{
        note_string = 'N';
        printf("Got None \n");
    }
    
    
    return note_string;
    }
