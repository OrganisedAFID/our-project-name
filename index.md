
# Sound PIrates

![image](https://user-images.githubusercontent.com/44497996/114782410-b0529700-9d71-11eb-9d58-da91cf2f99eb.png)


## What is Sound PIrates?

Sound pirates is playable if you download the developper kit for the game!
Requires a pi, soundcard and microphone.

Welcome to Sound Pirates! – In space, the sounds will move you!
.
The game is currently limited to the C major scale and the chase is short. With updates there will be more complexity and sub-games to help train your ear and vocal chords or playing fingers to match whichever notes, tones, or microtones you might want to familiarise yourself with. We have tested it with raspberry pi 4 with Raspbian installed, a 3.5mm jack condenser mic and a USB sound card. It uses the Urho3D game engine and features original art and 3D models from the team.
Chantilly is a former engineer turned pirate who realised they could use their new technology to take from the rich to give to the poor Robin Hood style. Living outside the law means you need to work with unsavoury types though, so Lace has built a reputation as a fearsome Captain and a hardy warrior. The problem is, the crew of The Space Shanty can see a whole lot of wealth, and feel not enough is going in their pockets! Will you be able to guide Lace through the trials that await?

## What do you need to play the game?
![image](https://user-images.githubusercontent.com/44497996/114785061-088a9880-9d74-11eb-942a-61e387437b15.png)

## How the game works

### Building the project
Before installing the game the following packages must be downloaded:
```markdown
sudo apt-get install \
    libx11-dev libxrandr-dev libasound2-dev libgl1-mesa-dev\
    libboost-dev libboost-all-dev  librtaudio-dev \ 
	libudev-dev libsfml-dev libfftw3-dev\
    git make cmake build-essential
```
To install the game type the following into command line:
```markdown
git clone https://github.com/OrganisedAFID/sound-pirates.git
```
When the game has been installed you can build the game by navigating to the Urho3D folder and type the following lines into command line
```markdown
cd sound-pirates/Urho3D
mkdir current_build
cd current_build
cmake ../src
cmake --build .
cd bin
./sound-pirates
```
If it is unable to locate the Urho3D folder write
```markdown
export URHO3D_HOME=/path_to_your_Urho3D_folder/
```
This will launch the game and you can start your journey of hunting sound PIrates!

![image](https://raw.githubusercontent.com/OrganisedAFID/sound-pirates/main/assets/Game_Image_1.jpeg)

### After Launching the game 

Launching the game will create a start screen where you can view instructions of how to play the game and a **start game** button. 
As you select **Start game** you will hear a tone from the C major scale, it is now your job to replicate that same tone. If you are able to recognise the tone and replay the correct note you will get closer to the spaceship infront of you- one step closer to reaching your goal. 
If you are unable to replicate the note the space ship will fly further away. 

The game ends when either you have caught up to the space PIrates and win the game, or you have played the incorrect note too many times and let the space PIrates get away- loosing the game. 

## Latency Analysis

## User Stories

## Social Media
Sound PIrates can be found 

## Future Work

With the basic functionality in place, there is definetly scope to expand the game. Ideas were thinking of include:
- Planning along with different scales
- Increasing the length of the sequence of notes the player is required to replicate. 


## The creators
- Alice Ravier
- David Hughes
- Fai Johnson
- Isabella Sheldon


