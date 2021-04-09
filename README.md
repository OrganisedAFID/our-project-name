# Sound PIrates
![alt text](https://raw.githubusercontent.com/OrganisedAFID/sound-pirates/main/assets/bushed-no-eye.svg)

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

## Installation

To build and execute this project, please do the following:
- Install  the following libraries: ```libboost-dev,  libboost-all-dev```
- Install the Urho3D Game engine: a free lightweight, cross-platform 2D and 3D game engine implemented in C++ and released under the MIT license. Visit https://urho3d.github.io/ and follow install instructions for Raspberry Pi
- Set the environment variable for the Urho3D folder on command line:\
```export URHO3D_HOME=folder_of_installed_Urho3D``` e.g ```export URHO3D_HOME=home/pi/Urho3D```
- Clone the repository
- Navigate to the project's Urho3D folder at: ```cd sound-pirates/Urho3D```
- Create build folder and make it the current directory: 
1) ```mkdir splash_build``` 
2) ```cd splash_build```
- Run cmake: 
1) ```cmake .```  
2) ``` make```
- Navigate to bin folder: ```cd bin```
- Run the project: ```./Splash```

You're all set!


## Usage


## Contributing 


## License 

[MIT](https://choosealicense.com/licenses/mit/)


