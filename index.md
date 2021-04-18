
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
make
cd bin
./sound-pirates
```
If it is unable to locate the Urho3D folder write
```markdown
export URHO3D_HOME=/path_to_your_Urho3D_folder/
```
This will launch the game and you can start your journey of hunting sound PIrates!

![image](https://user-images.githubusercontent.com/44497996/115146732-a7064a80-a04f-11eb-8b1c-208134bc23a7.png)

### After Launching the game 

Launching the game will create a start screen where you can view instructions of how to play the game and a **start game** button. 
As you select **Start game** you will hear a tone from the C major scale, it is now your job to replicate that same tone. If you are able to recognise the tone and replay the correct note you will get closer to the spaceship infront of you- one step closer to reaching your goal. 
If you are unable to replicate the note the space ship will fly further away. 

The game ends when either you have caught up to the space PIrates and win the game, or you have played the incorrect note too many times and let the space PIrates get away- loosing the game. 

## Latency Analysis

## User Stories

## Social Media
Sound PIrates can be found on Instagram @soundpirates and Twitter @SoundPIrates. 

Purpose of sharing on social media is to establish core of followers, likely in engineering, music, and game making communities. TO build our base we followed pages with similar interests and used similar hashtags to attract the attention of target users. Pact with other teams on course follow back to establish first followers as well as friends and family.

Instagram was the primary feed as group are established on this forum and is a viewed as a good medium to promote maker projects, with likelihood of shares high. Twitter has a secondary shorter lifespan of tweets and less tolerant of promotional accounts in general, though, Still a valid medium. 

#Phase 2. Video Of function available, proper promotion, attraction of testers.
Start 2 posts per week, timed for highest exposure (12-3) Mon & Thurs Instagram, 5pm Twitter*

/ * these were peak times pre-COVID, however there is yet to be data I could find of the current metrics. These metrics are also heavily influenced by American users so the 12-3 and 5pm UK times may be worth transposing and re-posting for the coastal zones of the US./

#Phase 3. Playable demo Promote game itself, invite feedback and log possible improvements & bugfixes
- Post on Raspberry Pi forums, pushing the specific to hardware nature
- Post on reddit/r/IMadeAGame to gain feedback and exposure
- Post on Urho3D website pushing use of game engine and unusual game mechanics
- Post videos with link on YouTube of friends and family trying with variety of instruments, gives participants more identification with the game and investment in sharing.
Continue posts on Insta, twitter, and Facebook.

#Phase 4. Post course – gauge interest in game and development
Invite collaboration on all media and develop game further or in whatever direction seems to garner most interest and excitement. To help us formulate our strategy for the game and our social media presence, the team managed to organise a chat with Colm ‘Gambrinous’ Larkin. Colm is a successful solo games developer who has expanded to a small team over the course of two games published internationally, receiving high praise and awards for them (Guild of Dungeoneering and Cardpocalypse, published by Versus Evil).
The social media strategy formed by the team was to concentrate on Instagram posts for the build up towards the game as this was the most established forum for the team members. An account was also created on twitter. The Github page was to be referred to and the core audience would be aimed at as content was produced.

On Colm’s advice, a greater push will be established when video is available as these posts do best in his experience. Colm’s advice was that the posts that really made a difference for his exposure and caught folks attention were videos of the game in action. Especially if a noticeable progress was gained from one video to the next. He also pointed out that consistency was good, posting a couple of times a week was how he saw the most benefit. Building up a small network of followers from the team members Instagram pools, we looked to angle posts to attract musicians and game developers. Starting a twitter account and posting updates and at the point of writing are establishing our Website, wiki, facebook, and Youtube presences.
With each release or significant improvement a further video will be released and promoted. Videos of testers engaged with the game will also be created and released.

OUr interaction on social media is visualized in the graphs (updated 18/04/2021 14:18)
![image](https://user-images.githubusercontent.com/44497996/115147018-fa2ccd00-a050-11eb-821e-05f71197e53e.png)

## Future Work

With the basic functionality in place, there is definetly scope to expand the game. Ideas were thinking of include:
- Planning along with different scales
- Increasing the length of the sequence of notes the player is required to replicate. 


## The creators
- Alice Ravier
- David Hughes
- Fai Johnson
- Isabella Sheldon


