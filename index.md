
# Sound PIrates

![image](https://user-images.githubusercontent.com/44497996/114782410-b0529700-9d71-11eb-9d58-da91cf2f99eb.png)



## What is Sound PIrates?

Sound PIrates is an interactive game targeted at musicians who want to learn how to play by ear. The concept of the game is simple. A short tone, within the C Major scale,  will be played out and the user has approximately 3 seconds to replicate the note on their chosen instrument. If the note played by the user and by the game is a match then a point is rewarded, and if the incorrect note is detected a point will be lost. There is no penalty for not playing a note. To make it more exciting a game featuring a spaceship has been developed. The objective is for the user to catch the spaceship, therefore when a correct note is detected the spaceship will appear closer, and if the incorrect note is played the spaceship will fly further away. The game goes on until enough wins or losses have been detected to either catch the spaceship, or it being too far out of reach. 

The game is currently limited to the C major scale and the chase is short. With updates there will be more complexity and sub-games to help train your ear and vocal chords or playing fingers to match whichever notes, tones, or microtones you might want to familiarise yourself with. We have tested it with raspberry pi 4 with Raspbian installed, a jack condenser input mic and a USB sound card. It uses the Urho3D game engine (https://urho3d.github.io/) and features original art and 3D models from the team.
![Sound PIrates_Trim](https://user-images.githubusercontent.com/44497996/115269380-2a4c9c80-a133-11eb-842b-642176235fca.gif)

## What do you need to play the game?

Sound pirates is playable if you download the developer kit for the game!

### Required Hardware

- Raspberry Pi (tested on Raspberry Pi 4B)
- USB Sound Card
- Microphone with jack connection
- Headphones or speakers with jack connection
- Instrument/Voice

<p align="center">
<img src= "https://user-images.githubusercontent.com/44497996/114785061-088a9880-9d74-11eb-942a-61e387437b15.png" width="500" height="500" >
</p>


## Building the project

After getting the hardware, follow these steps:

### Setup your pi

Before installing the game the following packages must be downloaded:
```markdown
sudo apt-get install 
    libx11-dev libxrandr-dev libasound2-dev libgl1-mesa-dev
    libboost-dev libboost-all-dev  librtaudio-dev 
    libudev-dev libsfml-dev libfftw3-dev
    git make cmake build-essential
```

### Setup your soundcard

#### Step 1: I2S communication setup

To setup the I2S communication execute these commands:

1) `sudo nano /boot/config.txt`
2)  Uncomment the line `"#dtparam=i2s=on"`
3)  Comment the line `"dtparam=audio=on"`

#### Step 2: Select your soundcard as I/O device for your pi

To set your soundcard as the input/output device, execute this command: `aplay -l`. Then check the line which has: "Device [USB PnP Sound Device]" 

It will have a number before it like this: "card 0: Device [USB PnP Sound Device]". In this case, the card number for the soundcard is 0 (Remeber this number). 

Now, execute this line: `sudo nano /etc/asound.conf` and write:

```
pcm.!default  { <br>
 type hw card <number-of-your-soundcard> <br>
}

ctl.!default { <br>
 type hw card <number-of-your-soundcard>  <br>
}


So, if your soundcard was card number 0, you would write:


pcm.!default  { <br>
 type hw card 0 <br>
}

ctl.!default { <br>
 type hw card 0 <br>
}
```

#### Step 3: Reboot

Now you can reboot your pi using the command: `reboot` and your soundcard should be setup!

#### Step 4: Test

You can test it with the command: `speaker-test` which should play some white noise through the soundcard.

If this fails, you can use this alternative method to make your soundcard work.
However it will mean you can't use HDMI with your pi, so only do this if the above steps fail.


### Alternative soundcard setup (only use this if the above fails)

#### Step 1: Select your soundcard as I/O device for your pi

Follow the instructions for Step 2 in the normal setup. Or, if you have already done that, skip this step.

#### Step 2: Blacklist all other input devices to your pi

Execute the following command:

`sudo nano /etc/modprobe.d/raspi-blacklist.conf`

Write `blacklist snd_bcm2835`

#### Step 3: Reboot

Now you can reboot your pi using the command: `reboot` and your soundcard should be setup!

#### Step 4: Test

You can test it with the command: `speaker-test` which should play some white noise through the soundcard.

Now you should be ready to play the game :)

### Running the game

https://user-images.githubusercontent.com/44497996/115253892-befbce00-a124-11eb-8b01-39e2d0b4e289.mp4

With your pi and soundcard setup you're all set to play sound pirates!

Now just execute these commands:

- Go into a directory in which you want the game to be.

- Clone the repo by running: `git clone https://github.com/OrganisedAFID/sound-pirates.git`

- Then go to our executable by running:  `cd sound-pirates/Urho3D/release_build/bin`

- Then run the game:  `./sound-pirates`

To watch a video of the install process go to: https://youtu.be/NzJbUrqUhCU 
<p align="center">
<img src= "https://user-images.githubusercontent.com/44497996/115208295-4ed55400-a0f4-11eb-8695-d28dd2b2fcbe.png" width="500" height="500" >
</p>

## After Launching the game 

Launching the game will create a start screen where you can view instructions of how to play the game and a **start game** button. 
As you select **Start game** you will hear a tone from the C major scale, it is now your job to replicate that same tone. If you are able to recognise the tone and replay the correct note you will get closer to the spaceship infront of you- one step closer to reaching your goal. 
If you are unable to replicate the note the space ship will fly further away. 

The game ends when either you have caught up to the space PIrates and win the game, or you have played the incorrect note too many times and let the space PIrates get away. 


## Latency Analysis
For the game to appear to be running in real-time the latency must be low. In gaming anything below 100ms is considered acceptable, while the standard latency is 20-40ms.

To assess the realtime responsiveness a latency analysis has been performed by timing various parts of the code. Simplified, the game will generate a screen, play a note, wait for the user to play a note, convert this into the frequency spectrum and identify the most dominant frequency, identify the note as correct/incorrect and finally have the spaceship in the game move depending on the detected note. Each of these were timed and the average of 5 games running  start to finish as seen in the list below. 

- scene generation: 430 ms
- process buffer: 2.2 ms
- finding maximum frequency: 0.000088 ms
- FFT: 1.5 ms
- Identify correct/incorrect note and move object (answer handler): 40 ms

This means that from a note has been detected to the spaceship moving in response to the note that was played takes a total of 44 ms. As seen in the boxplots below the majority of answer handler was significantly lower, around 0.3 ms, but a few significantly longer runs of answer handler brought the average up. Generating new scenes by far took the longest time with an average of 430 ms. The box plots of the timing of different functions are seen in the graphs below.  


![latency](https://user-images.githubusercontent.com/44497996/115292637-2712da00-a14e-11eb-8898-db9682023f2a.png)


## User Stories

So far, the game has been played with the clarinet, flute, violin and guitar. From feedback recived, users could quickly see how playing by ear is a difficult task to accoplish, yet the game is "addictive".  

![image](https://user-images.githubusercontent.com/44497996/115219661-a5945b00-a0ff-11eb-9959-3433e40e8265.png)

## Social Media

Sound PIrates can be found on Instagram @soundpirates and Twitter @SoundPIrates. 

Purpose of sharing on social media is to establish core of followers, likely in engineering, music, and game making communities. To build our base we followed pages with similar interests and used similar hashtags to attract the attention of target users. 

Instagram was the primary feed as group are established on this forum and is a viewed as a good medium to promote maker projects, with likelihood of shares high. Twitter has a secondary shorter lifespan of tweets and less tolerant of promotional accounts in general, though, Still a valid medium. 

**Playable demo Promote game itself, invite feedback and log possible improvements & bugfixes**
- Post on Raspberry Pi forums, pushing the specific to hardware nature
- Post on reddit/r/IMadeAGame to gain feedback and exposure
- Post on Urho3D website pushing use of game engine and unusual game mechanics
- Post videos with links to clips of friends and family trying with variety of instruments. This would give participants more identification with the game and investment in sharing.
Continue posts on Instagram, twitter, and Facebook.

**Post course – gauge interest in game and development**

Invite collaboration on all media and develop game further or in whatever direction seems to garner most interest and excitement. To help us formulate our strategy for the game and our social media presence, the team managed to organise a chat with Colm ‘Gambrinous’ Larkin. Colm is a successful solo games developer who has expanded to a small team over the course of two games published internationally, receiving high praise and awards for them (Guild of Dungeoneering and Cardpocalypse, published by Versus Evil).
The social media strategy formed by the team was to concentrate on Instagram posts for the build up towards the game as this was the most established forum for the team members. An account was also created on twitter. The Github page was to be referred to and the core audience would be aimed at as content was produced.

On Colm’s advice, a greater push will be established when video is available as these posts do best in his experience. Colm’s advice was that the posts that really made a difference for his exposure and caught people's attention were videos of the game in action. Especially if a noticeable progress was gained from one video to the next. He also pointed out that consistency was good, posting a couple of times a week was how he saw the most benefit. Building up a small network of followers from the team members Instagram pools, we looked to angle posts to attract musicians and game developers. Starting a twitter account and posting updates and at the point of writing are establishing our Website, wiki, facebook, and Youtube presences.
With each release or significant improvement a further video will be released and promoted. Videos of testers engaged with the game will also be created and released.

Our interaction on social media is visualized in the graphs (updated 18/04/2021 14:18)
![image](https://user-images.githubusercontent.com/44497996/115147018-fa2ccd00-a050-11eb-821e-05f71197e53e.png)

## Game development and requirements
When starting developmment of this project the following requirements were identified:
- **M**ust have:
	- Play specified frequency
	- Detect what has not been played by the user
	- Identify user's note as correct/incorrect
	- realtime audio processing
	- realtime responsiveness
- **S**hould have:
	- Game interface responding to correct/incorrect note
	- customized graphics for different scenes
- **C**ould have:
	- user feedback saying if note was too high/low
	- text displaying number of correct/incorrect notes
- **W**ould like to have:
	- Training mode where the sound is played while the name of the note is displayed to get users to associate the note with the sound
	- expand range of notes /scales 


## Future Work
With the basic functionality in place, there is definitely scope to expand the game. Ideas were thinking of include:
- Planning along with different scales
- Increasing the length of the sequence of notes the player is required to replicate. 


## The creators

**Alice:**  Main game developer; Tech lead; Team management

**David:**  Managed project's Doxygen documentation; Code refactoring; Game's graphics and story line; and main creator of project idea 

**Fai:** Audio programmer; Unit testing; Management of social media and project webpages; Management of project's CMakeLists files

**Isabella:** Audio programmer; Unit testing; Latency Analysis; Management of social media and project webpages; Game and social media graphics


