/**
 * @file splash.cpp
 * Creates a splash screen
 */


//
// Copyright (c) 2008-2020 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

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


#include <Urho3D/Urho3D.h>
#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Graphics/RenderPath.h>
#include <Urho3D/Engine/Application.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Input/InputEvents.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Resource/XMLFile.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/UI/UI.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/UI/UIEvents.h>
#include <Urho3D/UI/Window.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Geometry.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/DebugRenderer.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/Light.h>
#include <Urho3D/Graphics/Model.h>
#include <Urho3D/Graphics/StaticModel.h>
#include <Urho3D/Graphics/Material.h>
#include <Urho3D/Graphics/Skybox.h>
#include <Urho3D/Graphics/Zone.h>
#include <Urho3D/Audio/Sound.h>
#include <Urho3D/Audio/SoundSource3D.h>
#include <Urho3D/Audio/SoundListener.h>
#include <Urho3D/Audio/Audio.h>
#include <Urho3D/Graphics/ParticleEmitter.h>
#include <Urho3D/Graphics/ParticleEffect.h>
#include <Urho3D/Graphics/Terrain.h>
#include <Urho3D/Physics/RigidBody.h>

#include "splash.h"

#include <Urho3D/DebugNew.h>
int freqMax;  
int pipefds[2];

const float pi = 3.14159265;

unsigned int sampleRate = 44100;
unsigned int bufferFrames = 4410; // 512 sample frames
const int bandNumber = 128;
const int width = bufferFrames / bandNumber;
const int historyValues = sampleRate / (bufferFrames * 2);
char note;
char OutputNote;
const float nodeRadius = 100;
const float angularWidth = 2.0 * pi / bandNumber;
const float barWidth = angularWidth * nodeRadius;

int a = 0;
std::vector<signed short> window;
std::vector<double> v;

volatile sig_atomic_t stop;

void inthand(int signum) {
    stop = 1;
}

void fft(std::vector<signed short> &rawValues, std::vector<double> &output) //move this over to GPU_FFT
{
    int n = rawValues.size();
    int i;
    fftw_complex *inputChannel = new fftw_complex[n];
    fftw_complex *outputChannel = new fftw_complex[n];

    for (i = 0; i < n; i++) {
        inputChannel[i][0] = rawValues[i];
        inputChannel[i][1] = 0;
        outputChannel[i][0] = 0;
        outputChannel[i][1] = 0;
    }
    fftw_plan p = fftw_plan_dft_1d(n, inputChannel, outputChannel, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(p);
    for ( i = 0; i < n / 2; i++) {
        output.push_back(sqrt(outputChannel[i][0] * outputChannel[i][0] + outputChannel[i][1] * outputChannel[i][1]));
        }
    output[0] = 0;
    delete[] inputChannel;
    delete[] outputChannel;
}

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
void instructionsStatements(){
   
    std::cout << "Playing random note (in the 4th octave)" << "\n";
    playNote();
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    std::cout << "Now you play back in..." << "\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    for (int i=5; i>0; --i) {
    std::cout << i << std::endl;
    std::this_thread::sleep_for (std::chrono::seconds(1));
  }
  std::cout << "Go!" << "\n";
      
}


int processBuffer()
{  
    ::freqMax;
    ::pipefds[2];

    std::vector<double> output;
    fft(window, output);

    freqMax = 0;
    int freqMaxIndex = 51;
    int amplitudeThreshold = 10000;

    for (int i = 51; i < 100; i++) {        
        if (output[i] > output[freqMaxIndex] && output[i] > amplitudeThreshold){
            freqMaxIndex = i;
            freqMax = i*44100.0/window.size();            
        }
    }     
            
    if (freqMax > 249 && freqMax < 268 ){ //could be 256 instead of 249
        freqMax = 262;
        write(pipefds[1], "C4", sizeof("C4"));
    }
    else if (freqMax > 288 && freqMax < 300){
        freqMax = 294;
        write(pipefds[1], "D4", sizeof("D4"));
    }
    else if (freqMax > 324 && freqMax < 336){
        freqMax = 330;
        write(pipefds[1], "E4", sizeof("E4"));
    }  
    else if (freqMax  > 343 && freqMax < 349){
        freqMax  = 349;
        write(pipefds[1], "F4", sizeof("F4"));
    }  
    else if (freqMax > 386 && freqMax < 398){
        freqMax = 392;
        write(pipefds[1], "G4", sizeof("G4"));
    }    
    else if (freqMax > 434 && freqMax < 446){
        freqMax = 440;
        write(pipefds[1], "A4", sizeof("A4"));
    }  
    else if (freqMax > 482 && freqMax < 500){
        freqMax = 494;
        write(pipefds[1], "B4", sizeof("B4"));
    }
    else{
        write(pipefds[1], "None", sizeof("None"));
        printf("Wrote None \n");
    }

    
    std::cout << freqMax << std::endl;
    return freqMax;
}



int record(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
            double streamTime, RtAudioStreamStatus status, void *userData)
{
    printf("Called Record \n");
    if (status) {
        std::cout << "Stream overflow detected!" << std::endl;
    }

    int i = 0;
    signed short *a = (signed short*)inputBuffer;

    //Add nBufferFrames values from the input buffer into window
    while (window.size() < nBufferFrames*2 && i < nBufferFrames) {
        window.push_back(a[i++]);
    }

    processBuffer();
   
    if (window.size() == nBufferFrames*2) {
        //get rid of the first half of window
        window.erase(window.begin(), window.begin() + nBufferFrames);
    }

    return 0;
}


int lol()
{  
    //access audio device
    RtAudio adc;
    if (adc.getDeviceCount() < 1) {
        std::cout << "No audio devices found!\n";
        return -1;
    }

    //Print device infos  
    unsigned int numDev = adc.getDeviceCount();
    RtAudio::DeviceInfo di;
    for ( unsigned int i = 0; i < numDev; ++i )
    {
        // use the Debugger if you need to know deviceID
        std::cout << "Device info" << std::endl;
        di = adc.getDeviceInfo( i );
        //std::cout << di << std::endl;
    }
   
    //Set parameters
    RtAudio::StreamParameters parameters;
    parameters.deviceId = adc.getDefaultInputDevice();
    parameters.nChannels = 1;
    parameters.firstChannel = 0;
    
    std::thread t1(instructionsStatements);
    t1.join();
   

    try {
        //Calls the record function
        adc.openStream(NULL, &parameters, RTAUDIO_SINT16, sampleRate, &bufferFrames, &record);
        adc.startStream();
        std::cout << adc.getVersion();
    } catch (RtAudioError& e) {
        e.printMessage();
        return -1;
    }

    char input;
    std::cout << "\nRecording ... press <enter> to quit.\n";
    
    signal(SIGINT, inthand);
    stop = 0;
    while(!stop){}
    adc.closeStream();
    return 0;
}


// Expands to this example's entry-point
URHO3D_DEFINE_APPLICATION_MAIN(HelloWorld)

//Entry point
HelloWorld::HelloWorld(Context* context) :
    Sample(context)
{   
    ::pipefds[2];
    int returnstatus;
    int pid;
    returnstatus = pipe(pipefds);
    if (returnstatus == -1) 
    {
        printf("Unable to create pipe\n");
        return;
    }   
    pid = fork();
    //Game process
    if (pid == 0){}  
    //SP process
    else
    { 
        engine_->Exit();
        lol();
        playNote();   
    }
}

void HelloWorld::Start()
{   
    // Execute base class startup
    Sample::Start();

    // Create "Hello World" Text
    CreateScene1();

    // Set the mouse mode to use in the sample
    Sample::InitMouseMode(MM_FREE);
}

void HelloWorld::CreateScene1()
{
    auto* ui = GetSubsystem<UI>();
    UIElement* root = ui->GetRoot();
    auto* cache = GetSubsystem<ResourceCache>();
    // Load the style sheet from xml
    root->SetDefaultStyle(cache->GetResource<XMLFile>("UI/DefaultStyle.xml"));
    auto* startButton = CreateButton
    (root, "StartButton", "StartText", "Start Game!", 400, 500);
    auto* helloText = 
    CreateText("Welcome to Sound Pirates!", "welcomeText", 
                cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 400, 300);
    SubscribeToEvent(startButton, E_CLICK, URHO3D_HANDLER(HelloWorld, HandleStartClick));
}

Text* HelloWorld::CreateText(String content, String tagName, Urho3D::Font* font, int x, int y)
{  
    // Construct new Text object
    SharedPtr<Text> text(new Text(context_));

    // Set String to display
    text->SetText(content);

    // Set font and text color
    text->SetFont(font, 30);
    text->SetColor(Color(0.0f, 5.0f, 1.0f));
    text->SetPosition(IntVector2(x, y));
    text->AddTag(tagName);

    // Add Text instance to the UI root element
    GetSubsystem<UI>()->GetRoot()->AddChild(text);  
    return text; 
}

/**
 * Creates a button on the given root, with the given tag.
 * It also adds a text to the button given a name with txtName, and a content with txtCont.
 * It will place the button according to x and y coordinates.
 * Possible hAlign values = HA_LEFT, HA_CENTER, HA_RIGHT, HA_CUSTOM
 * Possible vAlign values =  VA_TOP = 0, VA_CENTER, VA_BOTTOM, VA_CUSTOM 
 * 
 */ 
Button* HelloWorld::CreateButton
(UIElement* root, String tag, String txtName, String txtCont, 
  int x, int y, int width)
{
    auto* b = new Button(context_);
    
    root->AddChild(b);
    // Reference a style from the style sheet loaded earlier:
    b->SetStyleAuto();
    
    b->SetWidth(width);
    
    b->AddTag(tag);
    b->SetPosition(IntVector2(x, y));

    // Set the layout mode to make the child text elements aligned vertically
    b->SetLayout(LM_VERTICAL, 20, {40, 40, 40, 40});    
    
    // Add text
    b->CreateChild<Text>(txtName)->SetStyleAuto();
    auto* t = b->GetChildStaticCast<Text>(txtName, false);
    t->SetText(txtCont);
    t->SetHorizontalAlignment(HA_CENTER);
    
    return b;
}

void HelloWorld::SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(HelloWorld, HandleUpdate));
    
}

void HelloWorld::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;

    // Take the frame time step, which is stored as a float
    float timeStep = eventData[P_TIMESTEP].GetFloat();

    // Move the camera, scale movement with time step
    MoveCamera(timeStep);

    int fd = ::pipefds[0];
    struct pollfd *fds;
    fds = (pollfd*) calloc(1, sizeof(pollfd));
    fds[0].fd = fd; fds[0].events |= POLLIN;
    int rv = poll(fds, 1, 0);
    if (rv == -1) {
        printf("An error occurred: %d\n", errno);
        return;
    }
    
    if (rv==1) {
        printf("Events occurred: %d.", rv);
        char readmessage[20];
        read(::pipefds[0], readmessage, sizeof(readmessage));
        printf("Child Process - Reading from pipe – Message 1 is %s\n", readmessage);
        ChangeTexts(readmessage);
    }
}

void HelloWorld::ChangeTexts(String note, String OutputNote)
{
    UIElement* root = GetSubsystem<UI>()->GetRoot();
    auto* cache = GetSubsystem<ResourceCache>();

    const float MOVE_SPEED = 20.0f;
    const float timestep = 20.0f;
    float y = 5.0;
    Node* boxNode = scene_->CreateChild("Box");
    boxNode->SetPosition(Vector3(0.0f, y, 0.0f));
    boxNode->SetRotation(Quaternion(0.0f, 90.0f, -45.0f));
    boxNode->SetScale(Vector3(1.0f, 2.0f, 1.0f));
    auto* boxObject = boxNode->CreateComponent<StaticModel>();
    boxObject->SetModel(cache->GetResource<Model>("Models/SpaceFighter.mdl"));
    boxObject->SetMaterial(cache->GetResource<Material>("Materials/StoneEnvMapSmall.xml"));
    boxObject->SetCastShadows(true);


    String notes[8] = {"C4", "D4", "E4", "F4", "G4", "A4", "B4", "None"};
    if ( note == OutputNote ){
        std::cout << "You played the correct note\n";
    }
        else {
                    std::cout << "You played the wrong note\n";
                }
            
    if(notes[0] == note){
       boxNode->Translate(Vector3(0.0f, 8.0f, .0f));
    }
    else if (notes[1] == note){
       boxNode->Translate(Vector3(0.0f, y+4.0f, .0f));
    }
    else if (notes[2] == note){
       boxNode->Translate(Vector3(0.0f, y+6.0f, .0f));
    }
    else if (notes[3] == note){
       boxNode->Translate(Vector3(0.0f, 8.0f, .0f));
    }
    else if (notes[4] == note){
       boxNode->Translate(Vector3(0.0f, -2.0f, .0f));
    }
    else if (notes[5] == note){
       boxNode->Translate(Vector3(0.0f, -4.0f, .0f));
    }
    else if (notes[6] == note){
       boxNode->Translate(Vector3(0.0f, -6.0f, .0f));
    }
    else if (notes[7] == note){
       boxNode->Translate(Vector3(0.0f, 5.0f, .0f));
    }
    else if {
       boxNode->SetPosition(Vector3(0.0f, 5.0f, .0f));
    }
    // Make relevant note more opaque and all others less opaque
    for(int i= 0; i<8; i++){
        if(notes[i] == note){
            Urho3D::PODVector<Urho3D::UIElement*> noteText = 
                root->GetChildrenWithTag(note+"Text");
            noteText[0]->SetOpacity(1);
        }
        else{
            Urho3D::PODVector<Urho3D::UIElement*> otherText = 
                root->GetChildrenWithTag(notes[i]+"Text");
            otherText[0]->SetOpacity(0.5);
        }
    }
     



}

/** 
 * when you click on the start button, the UI elements dissapear
 * 
 */
void HelloWorld::HandleStartClick(StringHash eventType, VariantMap& eventData)
{
    using namespace Click;
      
    DeleteScene1();
    printf("Deleted scene1");
    //Show the main game screen
    CreateScene2();
    printf("created scene 2");
    SetupViewport();
    printf("setup viewport");

    // Finally subscribe to the update event so we can move the camera.
    printf("sub");
    SubscribeToEvents();    
}

void HelloWorld::DeleteScene1()
{
    UIElement* root = GetSubsystem<UI>()->GetRoot();
    auto* cache = GetSubsystem<ResourceCache>();
    
    // erase welcome text
    Urho3D::PODVector<Urho3D::UIElement*> welcomeText = root->GetChildrenWithTag("welcomeText");
    welcomeText[0]->SetVisible(false);
    
    // erase button
    Urho3D::PODVector<Urho3D::UIElement*> button = root->GetChildrenWithTag("StartButton");
    button[0]->SetVisible(false);
}

/**
 * Creates the scene with the ship
 * 
 * 
 */ 
void HelloWorld::CreateScene2()
{
    auto* cache = GetSubsystem<ResourceCache>();
    scene_ = new Scene(context_);

    // Create the Octree component to the scene. This is required before adding any drawable components, or else nothing will
    // show up. The default octree volume will be from (-1000, -1000, -1000) to (1000, 1000, 1000) in world coordinates; it
    // is also legal to place objects outside the volume but their visibility can then not be checked in a hierarchically
    // optimizing manner
    scene_->CreateComponent<Octree>();
    //scene_->CreateComponent<PhysicsWorld>();
    scene_->CreateComponent<DebugRenderer>();
    
    Node* zoneNode = scene_->CreateChild("Zone");
    auto* zone = zoneNode->CreateComponent<Zone>();
    zone->SetBoundingBox(BoundingBox(-1000.0f, 1000.0f));
    zone->SetAmbientColor(Color(0.15f, 0.15f, 0.15f));
    zone->SetFogColor(Color(1.0f, 1.0f, 1.0f));
    zone->SetFogStart(300.0f);
    zone->SetFogEnd(500.0f);  
    Node* planeNode = CreatePlane();
    
    Node* shipNode = CreateShip();
    shipNode->AddTag("ship");
    
    // Create a directional light to the world so that we can see something. The light scene node's orientation controls the
    // light direction; we will use the SetDirection() function which calculates the orientation from a forward direction vector.
    // The light will use default settings (white light, no shadows)
    Node* lightNode = scene_->CreateChild("DirectionalLight");
    lightNode->SetDirection(Vector3(0.6f, -1.0f, 0.8f)); // The direction vector does not need to be normalized
    auto* light = lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);  

    Node* skyNode = scene_->CreateChild("Sky");
    skyNode->SetScale(500.0f); // The scale actually does not matter
    auto* skybox = skyNode->CreateComponent<Skybox>();
    //skybox->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
    //skybox->SetMaterial(cache->GetResource<Material>("Materials/Skybox.xml"));    
    // Create a scene node for the camera, which we will move around
    // The camera will use default settings (1000 far clip distance, 45 degrees FOV, set aspect ratio automatically)
    cameraNode_ = scene_->CreateChild("Camera");
    cameraNode_->CreateComponent<Camera>();

    // Set an initial position for the camera scene node above the plane
    cameraNode_->SetPosition(Vector3(0.0f, 10.0f, 30.0f));
    
    
    // Create 7 buttons, one for each note
    auto* ui = GetSubsystem<UI>();
    UIElement* root = ui->GetRoot();
    Button* noteButtons[7];
    Text* noteTexts[8];
    String notes[8] = {"C4", "D4", "E4", "F4", "G4", "A4", "B4", "None"};
    int leftOffset = 20;
    int spacing = 20;
    int width = 40;
    int buttonHeight = 40;
    int textHeight = 40;
    for(int i = 0; i < 7; i++){
        noteButtons[i] = CreateButton(root, notes[i]+"Butt", notes[i]+"ButtText", notes[i], 
                                      leftOffset+i*(width+spacing), buttonHeight, width);
        
    }
    for(int i = 0; i<8; i++){
        noteTexts[i] = CreateText
            (notes[i], notes[i]+"Text", cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 
                leftOffset+i*(width+spacing)+width/2, textHeight);
    }
    

    cameraNode_ = new Node(context_);
    auto* camera = cameraNode_->CreateComponent<Camera>();
    camera->SetFarClip(500.0f);

    // Set an initial position for the camera scene node above the floor
    cameraNode_->SetPosition(Vector3(0.0f, 5.0f, -20.0f));
}

/**
 * Creates a plane underneath the entire scene
 */
Node* HelloWorld::CreatePlane()
{
    auto* cache = GetSubsystem<ResourceCache>();
    
    Node* planeNode = scene_->CreateChild("Plane");
    planeNode->SetScale(Vector3(100.0f, 1.0f, 100.0f)); 
    auto* planeObject = planeNode->CreateComponent<StaticModel>();
    planeObject->SetModel(cache->GetResource<Model>("Models/Plane.mdl"));
    planeObject->SetMaterial(cache->GetResource<Material>("Materials/StoneTiled.xml")); 
    return planeNode;
}

/**
 * Creates the enemy ship to pursue
 */
Node* HelloWorld::CreateShip()
{
    auto* cache = GetSubsystem<ResourceCache>();
    
    Node* coneNode = scene_->CreateChild("Cone");
    coneNode->SetPosition(Vector3(0.0f, 10.0f, 10.0f));
    coneNode->SetScale(Vector3(10.0f, 10.0f, 10.0f));
    auto* coneObject = coneNode->CreateComponent<StaticModel>();
    coneObject->SetModel(cache->GetResource<Model>("Models/Cone.mdl"));
    coneObject->SetMaterial(cache->GetResource<Material>("Materials/torch_metal.xml")); 
    return coneNode;
}

void HelloWorld::MoveCamera(float timeStep)
{
    // Do not move if the UI has a focused element (the console)
    if (GetSubsystem<UI>()->GetFocusElement())
        return;

    auto* input = GetSubsystem<Input>();

    // Movement speed as world units per second
    const float MOVE_SPEED = 20.0f;
    // Mouse sensitivity as degrees per pixel
    const float MOUSE_SENSITIVITY = 0.05f;
    
    // Use this frame's mouse motion to adjust camera node yaw and pitch. 
    // Clamp the pitch between -90 and 90 degrees
    IntVector2 mouseMove = input->GetMouseMove();
    yaw_ += MOUSE_SENSITIVITY * mouseMove.x_;
    pitch_ += MOUSE_SENSITIVITY * mouseMove.y_;
    pitch_ = Clamp(pitch_, -90.0f, 90.0f);
    
    // Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
    if (input->GetKeyDown(KEY_Q))
        cameraNode_->SetRotation(Quaternion(pitch_, yaw_, 0.0f));
    
    // Read WASD keys and move the camera scene node to the corresponding direction if they are pressed
    // Use the Translate() function (default local space) to move relative to the node's orientation.
    if (input->GetKeyDown(KEY_W))
        cameraNode_->Translate(Vector3::FORWARD * MOVE_SPEED * timeStep);
    if (input->GetKeyDown(KEY_S))
        cameraNode_->Translate(Vector3::BACK * MOVE_SPEED * timeStep);
    if (input->GetKeyDown(KEY_A))
        cameraNode_->Translate(Vector3::LEFT * MOVE_SPEED * timeStep);
    if (input->GetKeyDown(KEY_D))
        cameraNode_->Translate(Vector3::RIGHT * MOVE_SPEED * timeStep);
}

void HelloWorld::SetupViewport()
{
    auto* renderer = GetSubsystem<Renderer>();

    // Set up a viewport to the Renderer subsystem so that the 3D scene can be seen. We need to define the scene and the camera
    // at minimum. Additionally we could configure the viewport screen size and the rendering path (eg. forward / deferred) to
    // use, but now we just use full screen and default render path configured in the engine command line options
    SharedPtr<Viewport> viewport(new Viewport(context_, scene_, cameraNode_->GetComponent<Camera>()));
    renderer->SetViewport(0, viewport);
}