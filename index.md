# Sound PIrates

![image](https://user-images.githubusercontent.com/44497996/114782410-b0529700-9d71-11eb-9d58-da91cf2f99eb.png)


## What is Sound PIrates?

Sound pirates is playable if you download the developper kit for the game!
Requires a pi, soundcard and microphone.

Welcome to Sound Pirates! – In space, the sounds will move you!
You are about to enter a universe where starships sing to each other across the void. Where buccaneers race the spaceways looking for loot and smugglers run their contraband from port to shady port. In the Galaxy of Audiorum, ships travel space carrying great prizes. Fleets move as one in warp jumps, synchronised by ‘The Resonance’ – a tone send out by the warp engines encoding each jump. Planned journeys are symphonies played out by ships in glorious rhythm across the stars.
You are taking on the role of Chantilly Lace, a pirate with such genius they can tweak their engines so that the Resonance sent out by other ships is trackable and you can catch and board great frigates in deep space in your mighty and feared ship ‘The Space Shanty’.
The game is currently limited to the C major scale and the chase is short. With updates there will be more complexity and sub-games to help train your ear and vocal chords or playing fingers to match whichever notes, tones, or microtones you might want to familiarise yourself with. We have tested it with raspberry pi 4 with Raspbian installed, a 3.5mm jack condenser mic and a USB sound card. It uses the Urho3D game engine and features original art and 3D models from the team.
Chantilly is a former engineer turned pirate who realised they could use their new technology to take from the rich to give to the poor Robin Hood style. Living outside the law means you need to work with unsavoury types though, so Lace has built a reputation as a fearsome Captain and a hardy warrior. The problem is, the crew of The Space Shanty can see a whole lot of wealth, and feel not enough is going in their pockets! Will you be able to guide Lace through the trials that await?

## What do you need to play the game?
![image](https://user-images.githubusercontent.com/44497996/114785061-088a9880-9d74-11eb-942a-61e387437b15.png)

## How the game works

### Building the project
When the game has been installed you can build the game by navigating to the Urho3D folder and type the following lines into command line
```markdown
mkdir current_build
cd current_build
cmake ../src
cmake --build .
cd bin
./sound-pirates
```
This will launch the game and you can start your journey of hunting sound PIrates!

![image](hhttps://raw.githubusercontent.com/OrganisedAFID/sound-pirates/main/assets/Game_Image_1.jpeg)

### After Launching the game 

Launching the game will create a start screen where you can view instructions of how to play the game and a **start game** button. 
As you select **Start game** you will hear a tone from the C major scale, it is now your job to replicate that same tone. If you are able to recognise the tone and replay the correct note you will get closer to the spaceship infront of you- one step closer to reaching your goal. 
If you are unable to replicate the note the space ship will fly further away. 

The game ends when either you have caught up to the space PIrates and win the game, or you have played the incorrect note too many times and let the space PIrates get away- loosing the game. 

## Latency Analysis

## User stories

## Future work

## The creators
- Alice Ravier
- David Hughes
- Fai Johnson
- Isabella Sheldon


