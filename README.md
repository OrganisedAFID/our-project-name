# Sound PIrates
![alt text](https://raw.githubusercontent.com/OrganisedAFID/sound-pirates/main/assets/Logo.svg)

Turn learning by ear into play with our fun interactive game. Produced on the Raspberry Pi, developed by final year engineering students at #UofG

Current status: Version 1 development in progress 

Check out our social media pages to keep up to date with  our progress
- Instagram:  https://www.instagram.com/soundpirates/
- Twitter: https://twitter.com/SoundPIrates

Link to our website: https://organisedafid.github.io/sound-pirates/

## Required Hardware

- Raspberry Pi
- USB Sound Card
- Microphone with 3.5mm jack connection
- Headphones or speakers with 3.5mm jack connection
- Instrument/Voice

<p align="center">
<img src= "https://raw.githubusercontent.com/OrganisedAFID/sound-pirates/main/assets/SoundPIratesHardware.gif" width="400" height="400" >
</p>

## Playing the game

After getting the hardware, follow these steps:
### Setup your pi

### Setup your soundcard
#### Step 1: I2S communication setup
To setup the I2S communication execute these commands:

`sudo nano /boot/config.txt`

- uncomment the line "#dtparam=i2s=on"

- comment the line "dtparam=audio=on"

#### Step 2: Select your soundcard as I/O device for your pi
To set your soundcard as the input/output device, execute this command:

`aplay -l`

Then check the line which has:

"Device [USB PnP Sound Device]" 

It will have a number before it like this: 

"card 0: Device [USB PnP Sound Device]"

In this case, the card number for the soundcard is 0

Remeber this number. Now, execute this line:

`sudo nano /etc/asound.conf`

and write:


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


#### Step 3: Reboot
Now you can reboot your pi using the command:

`reboot`

and your soundcard should be setup!

#### Step 4: Test
You can test it with the command:

`speaker-test`

which should play some white noise through the soundcard.

If this fails, you can use this alternative method to make your soundcard work. However it will mean you can't use HDMI with your pi, so only do this if the above steps fail.

### Alternative soundcard setup (only use this if the above fails)

#### Step 1: Select your soundcard as I/O device for your pi
Follow the instructions for Step 2 in the normal setup. Or, if you hae already done that, skip this step.

#### Step 2: Blacklist all other input devices to your pi
Execute the following command:

`sudo nano /etc/modprobe.d/raspi-blacklist.conf`

Write blacklist snd_bcm2835

#### Step 3: Reboot
Now you can reboot your pi using the command:

`reboot`

and your soundcard should be setup!

#### Step 4: Test
You can test it with the command:

`speaker-test`

which should play some white noise through the soundcard.

Now you should be ready to play the game :)

### Running the game
With your pi and soundcard setup you're all set to play sound pirates!

Now just execute these commands:

Go into a directory in which you want the game to be.

Clone the repo by running:

`git clone https://github.com/OrganisedAFID/sound-pirates.git`

Then go to our executable by running:

`cd sound-pirates/Urho3D/release_build/bin`

Then run the game:

`./sound-pirates`
  

## Developper instructions

To build and execute this project, please do the following:
- Install  the following libraries: ```libboost-dev,  libboost-all-dev```
- Install the Urho3D Game engine: a free lightweight, cross-platform 2D and 3D game engine implemented in C++ and released under the MIT license. Visit https://urho3d.github.io/ and follow install instructions for Raspberry Pi
- Set the environment variable for the Urho3D folder on command line:\
```export URHO3D_HOME=folder_of_installed_Urho3D``` e.g ```export URHO3D_HOME=home/pi/Urho3D```
- Clone the repository
- Navigate to the project's Urho3D folder at: ```cd sound-pirates/Urho3D```
- Create build folder and make it the current directory: 
1) ```mkdir current_build``` 
2) ```cd current_build```
- Run cmake: 
1) ```cmake ../src```  
2) ``` make```
- Navigate to bin folder: ```cd bin```
- Run the project: ```./sound-pirates```

You're all set!


## Usage


## Contributing 


## License 

[MIT](https://choosealicense.com/licenses/mit/)


