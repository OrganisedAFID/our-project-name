/**
 * @file splash.cpp
 * Creates a splash screen
 */


/************************************************************************/
/*!

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
*/
/************************************************************************/

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

#include <complex>     
#include <string>
#include "audioIn.h"
#include "fft.h"
#include "playNote.h"
#include "instructionsStatements.h"
#include "processBuffer.h"
#include "defineNote.h"
#include <alsa/asoundlib.h>


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

#include <Urho3D/Physics/CollisionShape.h>
#include <Urho3D/Physics/Constraint.h>

#include <Urho3D/Physics/RigidBody.h>

#include "splash.h"
#include <Urho3D/DebugNew.h>


/**
 * 
 * global variables list to be incorporated in setup
 */
int a = 0;
std::vector<double> v;
int pipefds[2];
int freqMax;  
std::vector<double> window;
const int bandNumber = 128;
unsigned int sampleRate = 44100;
unsigned int bufferFrames = 4410; // 512 sample frames
volatile sig_atomic_t stop;
float time_ = 0;
Timer countDownTimer_ = Timer();
int pid;
int parentpid;
char OutputNote;
float timestep;
bool ready;
bool endGame;

Node* ship;
UI* ui;
ResourceCache* cache;
Context* globalContext_;
Vector3 cameraPos = Vector3(0.0f, -6.0f, -25.0f);
GameSys* ourGame;
Scene* mainScene;


/**
 * inthand function allows close of terminal with ctrl C
 * 
 */

void inthand(int signum) {
    stop = 1;
    return;
}

/**
 * processBuffer fuction. Calls fft, takes output of fft and sorts max freq into note to report
 * output freqMax
 * called by record
 * 
 */
int processBuffer()
{
    using namespace std::literals::chrono_literals;

    auto startBuf = std::chrono::high_resolution_clock::now();

    
    ::freqMax;
    ::pipefds[2];

    std::vector<double> output;
    fft(window, output);

    freqMax = 0;
    int freqMaxIndex = 51;
    int amplitudeThreshold = 45000;

    for (int i = 51; i < 100; i++)
    {
        if (output[i] >= output[freqMaxIndex] && output[i] > amplitudeThreshold)
        {
            freqMaxIndex = i;
            freqMax = i * 44100.0 / window.size();    
            //std::cout<< "amplitude "<< output[i] <<"\n" ;
        }
    } 
    char note_to_write = define_note(freqMax); 



std::cout<< "OutputNote (Game played): "<< OutputNote <<"\n" ;
std::cout<< "note_to_write (You played): "<< note_to_write <<"\n" ;
    if(freqMax != 0 && ready){
        if(note_to_write == OutputNote){
           std::cout<< "SIGUSR1 (correct)" <<"\n" ;
            kill(pid, SIGUSR1);           
        } else{
            std::cout<< "SIGUSR2 (incorrect)" <<"\n" ;
            kill(pid, SIGUSR2);
        }
        ready = false;
    } else {
        
      std::cout<< "neither SIGUSR1 (correct) or SIGUSR2 (incorrect) called" <<"\n" ; 
    }
    
    
    std::cout << freqMax << std::endl;

    auto endBuf = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> durationB = endBuf -startBuf;
    std::cout << "duration of process buffer" << durationB.count() << "s" <<std::endl;

    return freqMax, pipefds[2];
}

/**
 * record function. Activate the audio input and write to buffer
 * called by audioIn
 *  
 */

int record(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
           double streamTime, RtAudioStreamStatus status, void *userData)
{
    using namespace std::literals::chrono_literals;

    auto startRec = std::chrono::high_resolution_clock::now();

    printf("Called Record \n");
    if (status)
    {
        std::cout << "Stream overflow detected!" << std::endl;
    }

    int i = 0;
    signed short *a = (signed short *)inputBuffer;

    //Add nBufferFrames values from the input buffer into window
    while (window.size() < nBufferFrames * 2 && i < nBufferFrames)
    {
        window.push_back(a[i++]);
    }

    processBuffer();

    if (window.size() == nBufferFrames * 2)
    {
        //get rid of the first half of window
        window.erase(window.begin(), window.begin() + nBufferFrames);
    }

    auto endRec = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> durationR = endRec -startRec;
    std::cout << "duration of Record" << durationR.count() << "s" <<std::endl;
  

    return 0;
}


void readyHandler(int signum){
    signal(SIGUSR1, readyHandler);  
    ready = false;  
    printf("Called ready\n");  
    ::OutputNote = playNote();
    ready = true;
    return;
}

static void correctHandler(int signum){
    signal(SIGUSR1, correctHandler);
    printf("Called correct\n");  
    AnswerHandler(true);
    return;
}

static void incorrectHandler(int signum){
    signal(SIGUSR2, incorrectHandler);
    printf("Called incorrect\n");   
    AnswerHandler(false);
    return;
}



/**
 * audioIn function. 
 * calls record, which calls processBuffer,which calls fft
 * 
 */
int audioIn()
{    
    snd_pcm_t * _soundDevice;
    snd_pcm_hw_params_t *hw_params;
    //access audio device
    RtAudio adc;
    //int err = snd_pcm_open( &_soundDevice, "plughw:0,0", SND_PCM_STREAM_PLAYBACK, 0 );
    if (adc.getDeviceCount() < 1) {
        std::cout << "No audio devices found!\n";
        return -1;
    }
     

    //Print device infos
    unsigned int numDev = adc.getDeviceCount();
    RtAudio::DeviceInfo di;
    for (unsigned int i = 0; i < numDev; ++i)
    {
        // use the Debugger if you need to know deviceID
        std::cout << "Device info" << std::endl;
        di = adc.getDeviceInfo(i);     
    }

    //Set parameters
    RtAudio::StreamParameters parameters;
    parameters.deviceId = adc.getDefaultInputDevice();
    parameters.nChannels = 1;
    parameters.firstChannel = 0;

    try
    {
        //Calls the record function
        adc.openStream(NULL, &parameters, RTAUDIO_SINT16, sampleRate, &bufferFrames, &record);
        adc.startStream();
        std::cout << adc.getVersion();
    }
    catch (RtAudioError &e)
    {
        e.printMessage();
        return -1;
    }

    char input;
    std::cout << "\nRecording ... press <enter> to quit.\n";
    
    signal(SIGUSR1, readyHandler);

    //This code keeps the recording going and enables us to stop it be using ctrl-c on the command line
    signal(SIGINT, inthand);
    stop = 0;
    while(!stop){}
    adc.stopStream();
    adc.closeStream();
    return 0;
}



/**
 * Main program. Starts the Urho program setup, opens pipe and sets state machine in motion
 * 
 */
//URHO3D_DEFINE_APPLICATION_MAIN(GameSys)

int RunApplication() { 
    Urho3D::SharedPtr<Urho3D::Context> context(new Urho3D::Context()); 
    ourGame = new GameSys(context);
    Urho3D::SharedPtr<GameSys> application(ourGame); 
    return application->Run(); 
} 
URHO3D_DEFINE_MAIN(RunApplication())

/** 
 * GameSys function. instigates pipeline, checks and returns error if unable
 * starts game process
 * calls audioIn function and playNote function
 * 
 */ 
GameSys::GameSys(Context* context) :Sample(context)
{   
    ::pid;
    ::parentpid = getpid();
    pid = fork();
    //Game process
    if (pid == 0)
    {
        signal(SIGUSR1, correctHandler);
        signal(SIGUSR2, incorrectHandler);
    
    }
    //SP process
    else
    {
        engine_->Exit();
        audioIn();
        
    }
}
/**
 * Start function. Executes base class startup, creates the title scene 
 * and accepts mouse input 
 * 
 */
void GameSys::Start()
{   
    globalContext_ = context_;
    mainScene = new Scene(globalContext_);
    
    // Execute base class startup
    Sample::Start();


    // Create title scene
    CreateTitleScene();

    // Set the mouse mode to use in the sample
    Sample::InitMouseMode(MM_FREE);
}


void AnswerHandler(bool isCorrect){
    
    Vector3 newShipPos = ship->GetPosition();
    float distance = newShipPos.DistanceToPoint(cameraPos);
    float winThreshold = 20.0f;
    float lossThreshold = 100.0f;
    
    if (distance < winThreshold){
       
        endGame = true;
        ourGame->CreateWinScene();
        
    }
    else if (distance > lossThreshold){
       
        endGame = true;
        ourGame->CreateLossScene();
        
    }
    else{

    Vector3 shipPos = ship->GetPosition();
    UIElement *root = ui->GetRoot();
  
        
    float MOVE_SPEED=30.0f;
    std::string correctness;
    float y;
    float z;
    if(isCorrect){
        correctness = "correct";
        y = 10.0f;
        z = 0.0f;
    }
    else{
        correctness = "incorrect";
        y = -10.0f;
        z = 0.0f;
    }
    ::timestep;
    ship->Translate(Vector3(0.0f, y, z)*timestep*MOVE_SPEED);



    std::string txt = { "You played the "+correctness+" note" };

    String txtMessage = String(txt.c_str());
    std::string tag = correctness+"NoteText";
    String txtTag = String(tag.c_str()); 
    auto* screenText = CreateText(txtMessage, txtTag, ui->GetRoot()->GetWidth()/4 -10, 
    (ui->GetRoot()->GetHeight() / 4)*3);  
    screenText-> CreateChild<Text>(txtMessage);
    std::cout << "You played the "+correctness+" note\n";
    screenText->SetHorizontalAlignment(HA_LEFT);
    screenText->SetVerticalAlignment(VA_TOP);

    //Check if the ship is close/far enough to call the win/loss scene
   
  }
}



/**
 * CreateTitleScene function. Start screen splash, with button
 * calls CreateText, provides text content, calls Subscribe to events to allow input for state change
 * 
 */
void GameSys::CreateTitleScene()
{
        printf("inside title\n");
    ui = GetSubsystem<UI>();
    printf("got ui\n");
    UIElement *root = ui->GetRoot();
    printf("got root\n");
    cache = GetSubsystem<ResourceCache>();
    printf("got cache\n");
    
    // Load the style sheet from xml
    root->SetDefaultStyle(cache->GetResource<XMLFile>("UI/DefaultStyle.xml"));
    printf("set default\n");
    auto* startButton = CreateButton(root, "StartButton", 
        "StartText", "Start Game!", 250, 500);
    auto* insButton = CreateButton(root, "InsButton", "InsText", 
        "Instructions", 600, 500);
    auto* helloText = CreateText("Welcome to Sound Pirates!", 
        "welcomeText", 300, 300);
    printf("Made texts\n");
    SubscribeToEvent(startButton, E_CLICK, URHO3D_HANDLER(GameSys, HandleStartClick));
    SubscribeToEvent(insButton, E_CLICK, URHO3D_HANDLER(GameSys, HandleInsClick));
    printf("Subscribed!\n");
}
/**
 * CreateText function. Defines text parameters font (optional), colour, position
 * returns text
 * 
 */
Text* CreateText(String content, String tagName, int x, int y, String fontText)
{  
    Urho3D::Font* font = cache->GetResource<Font>(fontText);
    // Construct new Text object
    SharedPtr<Text> text(new Text(globalContext_));

    // Set String to display
    text->SetText(content);
    // Set font and text color
    text->SetFont(font, 30);
    text->SetColor(Color(0.0f, 10.0f, 1.0f));
    text->SetPosition(IntVector2(x, y));
    text->AddTag(tagName);
    // Add Text instance to the UI root element
    ui->GetRoot()->AddChild(text);
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
Button* GameSys::CreateButton
(UIElement* root, String tag, String txtName, String txtCont, 
  int x, int y, int width)
{
    auto *b = new Button(context_);

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
    auto *t = b->GetChildStaticCast<Text>(txtName, false);
    t->SetText(txtCont);
    t->SetHorizontalAlignment(HA_CENTER);

    return b;
}
/**
 * SubscribeToEvents function. Takes described events as inputs to change state
 * 
 */
void GameSys::SubscribeToEvents()
{
    // Subscribe HandleUpdate() function for processing update events

    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(GameSys, HandleUpdate)); 
}
/**
 * 
 * 
 */
void GameSys::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;

    // Take the frame time step, which is stored as a float
    ::timestep = eventData[P_TIMESTEP].GetFloat();
    if(countDownTimer_.GetMSec(false) >= 5000 && !endGame){
        countDownTimer_.Reset();
        kill(parentpid, SIGUSR1);
    }
}


/** 
 * when you click on the start button, the second scene appears
 * 
 */

void GameSys::HandleStartClick(StringHash eventType, VariantMap& eventData)
{
    using namespace Click;
    //delete title scene
    GetSubsystem<UI>()->GetRoot()->RemoveAllChildren();

    //Show the main game screen
    CreateMainScene();
    SetupViewport();

    // Finally subscribe to the update event so we can move the camera.
    SubscribeToEvents();  
}

/** 
 * when you click on the instructions button, the instructions appear
 * 
 */
void GameSys::HandleInsClick(StringHash eventType, VariantMap& eventData)
{
    using namespace Click;
    //Delete the title scene
    GetSubsystem<UI>()->GetRoot()->RemoveAllChildren();

    //Show the instructions
    CreateInstructionsScene();
}

/**
 * Shows the instruction text onto the screen
 */
void GameSys::CreateInstructionsScene()
{
    using namespace std::literals::chrono_literals;

    auto startIn = std::chrono::high_resolution_clock::now();

    UIElement* root = GetSubsystem<UI>()->GetRoot();
    auto* backButton = CreateButton(root, "BackButton", 
        "BackText", "Back to title screen", 400, 500);   
    auto* instructionsText = CreateText("Welcome to the first playable (alpha) version of Sound Pirates!  – In space, the sounds will move you! \n"
                                        "You are about to enter a universe where starships sing to each other across the void. \n"
                                        "Where buccaneers race the spaceways looking for loot and smugglers run their contraband \n"
                                        "from port to shady port. In the Galaxy of Audiorum, ships travel space carrying great prizes.\n" 
                                        "Fleets move as one in warp jumps, synchronised by ‘The Resonance’ – a tone send out \n"
                                        "by the warp engines encoding each jump. Planned journeys are symphonies played out by ships \n"
                                        "in glorious rhythm across the stars. You are taking on the role of Chantilly Lace, a pirate with \n"
                                        "such genius they can tweak their engines so that the Resonance sent out by other ships is trackable \n"
                                        "and you can catch and board great frigates in deep space in your mighty and feared ship \n"
                                        "The Space Shanty’. The game is currently limited to C major scal and the chase is short. \n"
                                        "With updates there will be more complexity and sub-games to help train your ear and vocal chords \n"
                                        "or playing fingers to match whichever notes, tones, or microtones\n" 
                                        "you might want to familiarise yourself with. \n"
                                        "\n"
                                        "We have tested it with raspberry pi 4 with Raspbian installed, a Disdim condenser mic \n"
                                        "and a USB sound card. It uses the Urho3D game engine and features original art from the team.\n"
                                        "Chantilly is a former engineer turned pirate who realised they could use \n"
                                        "their new technology to take from the rich to give to the poor Robin Hood style. \n"
                                        "Living outside the law means you need to work with unsavoury types though, \n"
                                        "so Lace has built a reputation as a fearsome Captain and a hardy warrior. \n"
                                        "The problem is, the crew of the Space Shanty can see a whole lot of wealth, and feel not enough is going in \n"
                                        "their pockets! Will you be able to guide Lace through the trials that await?", "Instructions", 0, 0);
    instructionsText->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 14);

    SubscribeToEvent(backButton, E_CLICK, URHO3D_HANDLER(GameSys, HandleBackClick));
    auto endIn = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> durationI = endIn -startIn;
    std::cout << "duration of Record" << durationI.count() << "s" <<std::endl;
}

/**
 * Shows the instruction text onto the screen
 */
void GameSys::CreateWinScene()
{
    //delete main scene
    mainScene->Clear();  
    


    UIElement* root = ui->GetRoot();
    auto* resetButton = 
        CreateButton(root, "ResetButton", "ResetText", "Back to title screen", 400, 500);   
    auto* winText = CreateText("You won!", "WinText", 
        ui->GetRoot()->GetWidth()/2-10, ui->GetRoot()->GetHeight()/2);
    SubscribeToEvent(resetButton, E_CLICK, URHO3D_HANDLER(GameSys, HandleResetClick));
}

/**
 * Shows the instruction text onto the screen
 */
void GameSys::CreateLossScene()
{
    //delete main scene
    mainScene->Clear();


    UIElement* root = GetSubsystem<UI>()->GetRoot();
    auto* resetButton = 
    CreateButton(root, "ResetButton", "ResetText", "Back to title screen", 400, 500);   
    auto* lossText = CreateText("You lose!", "LossText", 
        ui->GetRoot()->GetWidth()/2-10, ui->GetRoot()->GetHeight()/2);
    SubscribeToEvent(resetButton, E_CLICK, URHO3D_HANDLER(GameSys, HandleResetClick));
}

/** 
 * when you click on the instructions button, the instructions appear
 * 
 */
void GameSys::HandleResetClick(StringHash eventType, VariantMap& eventData)
{
    using namespace Click;
    GetSubsystem<UI>()->GetRoot()->RemoveAllChildren();

    endGame = false;
    UnsubscribeFromAllEvents();
    CreateTitleScene();
}

/** 
 * when you click on the back button, the instructions dissappear 
 * and the title screen comes back
 * 
 */
void GameSys::HandleBackClick(StringHash eventType, VariantMap& eventData)
{
    using namespace Click;

    //Delete the instructions
    GetSubsystem<UI>()->GetRoot()->RemoveAllChildren();

    //Create the title scene again
    CreateTitleScene();
}


/**
 * Creates the scene with the ship
 * 
 * 

 */ 
void GameSys::CreateMainScene()
{
    using namespace std::literals::chrono_literals;

    auto startMain = std::chrono::high_resolution_clock::now();

  
    auto *cache = GetSubsystem<ResourceCache>();
    printf("After cache\n");
    /** Create the Octree component to the scene. This is required before adding any drawable components, or else nothing will
     * show up. The default octree volume will be from (-1000, -1000, -1000) to (1000, 1000, 1000) in world coordinates; it
     * is also legal to place objects outside the volume but their visibility can then not be checked in a hierarchically
     * optimizing manner
     */
    mainScene->CreateComponent<Octree>();
    printf("After octree\n");

    //Creates the background for the scene
    Node* bgNode = CreateBackground();
    printf("bg\n");
    Node *zoneNode = mainScene->CreateChild("Zone");
    auto *zone = zoneNode->CreateComponent<Zone>();
    zone->SetBoundingBox(BoundingBox(-1000.0f, 1000.0f));
    zone->SetAmbientColor(Color(0.15f, 0.15f, 0.15f));
    zone->SetFogColor(Color(0.2f, 0.2f, 0.2f));
    zone->SetFogStart(300.0f);
    zone->SetFogEnd(500.0f);
    Node *shipNode = CreateShip();
    shipNode->AddTag("ship");
    ship = shipNode;

     Node* skyNode = mainScene->CreateChild("Sky");
    skyNode->SetScale(1.0f); // The scale actually does not matter
    auto* skybox = skyNode->CreateComponent<Skybox>();
    skybox->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
    skybox->SetMaterial(cache->GetResource<Material>("Materials/main_bg.xml"));

    // Create a directional light to the world so that we can see something. The light scene node's orientation controls the
    // light direction; we will use the SetDirection() function which calculates the orientation from a forward direction vector.
    // The light will use default settings (white light, no shadows)
            // Create a red directional light (sun)
        
    Node* lightNode=mainScene->CreateChild();
    lightNode->SetDirection(Vector3::FORWARD);
    lightNode->Yaw(50);     // horizontal
    lightNode->Pitch(10);   // vertical
    Light* light=lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);
    light->SetBrightness(3);
    light->SetColor(Color(1.0,.6,0.3,1));
    light->SetCastShadows(true);
    
   

    // Create a scene node for the camera, which we will move around
    // The camera will use default settings (1000 far clip distance, 45 degrees FOV, set aspect ratio automatically)
    cameraNode_ = mainScene->CreateChild("Camera");
    cameraNode_->CreateComponent<Camera>();

    // Set an initial position for the camera scene node above the plane
     cameraNode_->SetPosition(Vector3(0.0f, -6.0f, -25.0f));



        auto* instructionText = ui->GetRoot()->CreateChild<Text>();

    auto endMain = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> durationM = endMain -startMain;
    std::cout << "duration to create main scene " << durationM.count() << "s " <<std::endl;
}

/**
 * Create a background for the main scene.
 * Implemented as a cube positioned in front of the camera with the 
 * background png as a texture.
 */
Node* GameSys::CreateBackground()
{
    auto* cache = GetSubsystem<ResourceCache>();

    Node* skyNode = mainScene->CreateChild("Sky");
    skyNode->SetScale(Vector3(100.0f, 100.0f, 1.0f)); 
     skyNode->SetPosition(Vector3(0.0f, -6.0f, -25.0f));
         auto* skyObject = skyNode->CreateComponent<StaticModel>();
    skyObject->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
    skyObject->SetMaterial(cache->GetResource<Material>("Materials/main_bg.xml"));
    return skyNode;
}

/**
 * CreateShip function. Creates the enemy ship to pursue
 */
Node* GameSys::CreateShip()
{
    auto *cache = GetSubsystem<ResourceCache>();
    Node *boxNode = mainScene->CreateChild("Box");
    boxNode->SetRotation(Quaternion(215.0f, -45.0f, 25.0f));
    boxNode->SetPosition(Vector3(9.0f, -1.0f, 35.0f));
    boxNode->SetScale(Vector3(0.2f, 0.2, 0.2));
    auto *boxObject = boxNode->CreateComponent<StaticModel>();
    boxObject->SetModel(cache->GetResource<Model>("Models/SpaceShip.mdl"));
    boxObject->SetMaterial(cache->GetResource<Material>("Materials/Water.xml"));
    return boxNode;  
}

/**
 * 
 * 
 */
void GameSys::MoveCamera(float timeStep)
{
    /**
     *  Do not move if the UI has a focused element (the console)
     */
    if (GetSubsystem<UI>()->GetFocusElement())
        return;

    auto* input = GetSubsystem<Input>();

    /** 
     * Movement speed as world units per second
     */
    const float MOVE_SPEED = 20.0f;
    /**
     *  Mouse sensitivity as degrees per pixel
     */
    const float MOUSE_SENSITIVITY = 0.05f;
    
    /**
     *  Use this frame's mouse motion to adjust camera node yaw and pitch.
     *  Clamp the pitch between -90 and 90 degrees
     */
    IntVector2 mouseMove = input->GetMouseMove();
    yaw_ += MOUSE_SENSITIVITY * mouseMove.x_;
    pitch_ += MOUSE_SENSITIVITY * mouseMove.y_;
    pitch_ = Clamp(pitch_, -90.0f, 90.0f);
    
    /**
     *  Construct new orientation for the camera scene node from yaw and pitch. Roll is fixed to zero
     */
    if (input->GetKeyDown(KEY_Q))
        cameraNode_->SetRotation(Quaternion(pitch_, yaw_, 0.0f));
    
    /**
     * Read WASD keys and move the camera scene node to the corresponding direction if they are pressed
     * Use the Translate() function (default local space) to move relative to the node's orientation.
     */
    if (input->GetKeyDown(KEY_W))
        cameraNode_->Translate(Vector3::FORWARD * MOVE_SPEED * timeStep);
    if (input->GetKeyDown(KEY_S))
        cameraNode_->Translate(Vector3::BACK * MOVE_SPEED * timeStep);
    if (input->GetKeyDown(KEY_A))
        cameraNode_->Translate(Vector3::LEFT * MOVE_SPEED * timeStep);
    if (input->GetKeyDown(KEY_D))
        cameraNode_->Translate(Vector3::RIGHT * MOVE_SPEED * timeStep);
}
/**
 * 
 * 
 */
void GameSys::SetupViewport()
{
    auto *renderer = GetSubsystem<Renderer>();

    /**
     * Set up a viewport to the Renderer subsystem so that the 3D scene can be seen. We need to define the scene and the camera
     * at minimum. Additionally we could configure the viewport screen size and the rendering path (eg. forward / deferred) to
     * use, but now we just use full screen and default render path configured in the engine command line options
     */
    SharedPtr<Viewport> viewport(new Viewport(context_, mainScene, cameraNode_->GetComponent<Camera>()));
    renderer->SetViewport(0, viewport);
}
