# Sound PIrates
![alt text](https://raw.githubusercontent.com/OrganisedAFID/sound-pirates/main/assets/Logo.svg)

Turn learning by ear into play with our fun interactive game. Produced on the Raspberry Pi, developed by final year engineering students at #UofG

Current status: Beta version released 

Check out our social media pages to keep up to date with  our progress
- Instagram:  https://www.instagram.com/soundpirates/
- Twitter: https://twitter.com/SoundPIrates
- Youtube: https://youtu.be/fhjWzMPJlKY

Link to our website: https://organisedafid.github.io/sound-pirates/

## About the game

Sound PIrates is an interactive game targeted at musicians who want to learn how to play by ear. The concept of the game is simple. A short tone, within the C Major scale,  will be played out and the user has approximately 3 seconds to replicate the note on their chosen instrument. If the note played by the user and by the game is a match then a point is rewarded, and if no note or the incorrect note is detected a point will be lost. 

To make it more exciting a game featuring a spaceship has been developed. The objective is for the user to catch the spaceship, therefore when a correct note is detected the spaceship will appear closer, and if the incorrect note is played the spaceship will fly further away. The game goes on until enough wins or losses have been detected to either catch the spaceship, or it being too far out of reach. 
<p align="center">
<img src= "https://user-images.githubusercontent.com/44497996/115268362-18b6c500-a132-11eb-896d-6549926aac19.gif" width="600" height="400" >
</p>

The game is currently limited to the C major scale and the chase is short. With updates there will be more complexity and sub-games to help train your ear and vocal chords or playing fingers to match whichever notes, tones, or microtones you might want to familiarise yourself with. We have tested it with raspberry pi 4 with Raspbian installed, a jack condenser input mic and a USB sound card. It uses the Urho3D game engine (https://urho3d.github.io/) and features original art and 3D models from the team.


## Required Hardware

- Raspberry Pi
- USB Sound Card
- Microphone with jack connection
- Headphones or speakers with jack connection
- Instrument/Voice

<p align="center">
<img src= "https://raw.githubusercontent.com/OrganisedAFID/sound-pirates/main/assets/SoundPIratesHardware.gif" width="400" height="400" >
</p>

## Running the game

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

## Running the game

With your pi and soundcard setup you're all set to play sound pirates!

Now just execute these commands:

- Go into a directory in which you want the game to be.

- Clone the repo by running: `git clone https://github.com/OrganisedAFID/sound-pirates.git`

- Then go to our executable by running:  `cd sound-pirates/Urho3D/release_build/bin`

- Then run the game:  `./sound-pirates`
  

## Contributing 

Alternatively, to build and execute this project, please do the following:
- Install the following libraries to excute the unit tests: ```libboost-dev,  libboost-all-dev```
- Install the Urho3D Game engine: a free lightweight, cross-platform 2D and 3D game engine implemented in C++ and released under the MIT license. Visit https://urho3d.github.io/ and follow install instructions for Raspberry Pi
- Set the environment variable for the Urho3D folder on command line:\
```export URHO3D_HOME=folder_of_installed_Urho3D``` e.g ```export URHO3D_HOME=home/pi/Urho3D```
- Clone the repository
- Navigate to the project's Urho3D folder at: ```cd sound-pirates/Urho3D```
- Create build folder and make it the current directory: 
    1)  ```mkdir current_build``` 
    2)  ```cd current_build```
- Run cmake: 
    1)  ```cmake ../src```  
    2)  ``` make```
- Navigate to bin folder: ```cd bin```
- Run the project: ```./sound-pirates```

You're all set!

## Credits
[Alice Ravier](https://github.com/Aliceravier) </br>
[David Hughes](https://github.com/Thisaphid) </br>
[Fai Johnson](https://github.com/faij2009) </br>
[Isabella Sheldon](https://github.com/IsabellaSheldon) </br>


## License 

[MIT](https://choosealicense.com/licenses/mit/)


