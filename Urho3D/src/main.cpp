/**
 * @file main.cpp
 * Creates a main screen
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
#include "findFreqMax.h"
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
#include <future>


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
#include "main.h"
#include <Urho3D/DebugNew.h>


/**
 * 
 * global variables list to be incorporated in setup
 */
// Parameters for the sound processing (SP)
std::vector<double> window;
unsigned int sampleRate = 44100;
unsigned int bufferFrames = 4410; // 512 sample frames

char OutputNote; //note played out by the game

// Boolean to activate ctrl-c behaviour and stop the SP process
volatile sig_atomic_t stop;

// Timer used for the game process to know when to ask SP 
// to play a note and get user input
Timer countDownTimer_ = Timer();

// Pids used for communication between processes
int pid;
int parentpid;

// Used to move the ship smoothly (this doesn't work at the moment because movement isn't in update) 
float timestep;

// Used to control the flow of the game
bool ready; //signal for SP to playNote and listen for user
bool endGame; //says whether or not the game is active
bool notePlayed = true; //says whether or not the user played a note
bool playTime = true; //says if it is time for the user to play a note

int score = 0; // user's score


// Elements from GameSys which are needed globally 
// so functions out of the GameSys clas can access them
Node* ship;
UI* ui;
ResourceCache* cache;
Context* globalContext_;
Vector3 cameraPos = Vector3(0.0f, -6.0f, -25.0f);
GameSys* ourGame;
Scene* mainScene;
Text* scoreText;

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
 * 
 */
int processBuffer()
{  
    std::vector<double> output;
    fft(window, output);
    int freqMax = 0;
    int detectfreqMax = 0;
  
    int amplitudeThreshold = 45000; 


     freqMax = findFreqMax(detectfreqMax, output, window); 
    char noteUserPlayed= define_note(freqMax); 


    if(freqMax != 0 && ready && !endGame){
        if(noteUserPlayed == OutputNote){
            kill(pid, SIGUSR1);           
        } else{
            kill(pid, SIGUSR2);
        }
        ready = false;
    }
    
    std::cout << freqMax << std::endl;
    return freqMax;
}

/**
 * record function. Activate the audio input and write to buffer
 * 
 *  
 */
int record(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
           double streamTime, RtAudioStreamStatus status, void *userData)
{
    printf("Called Record \n");

    if (status)
    {
        std::cout << "Stream overflow detected!" << std::endl;
    }

    int i = 0;
    signed short *input_buffer = (signed short *)inputBuffer;

    //Add nBufferFrames values from the input buffer into window
    while (window.size() < nBufferFrames * 2 && i < nBufferFrames)
    {
        window.push_back(input_buffer[i++]);
    }

    processBuffer();

    if (window.size() == nBufferFrames * 2)
    {
        //get rid of the first half of window
        window.erase(window.begin(), window.begin() + nBufferFrames);
    }

    return 0;
}

/** Handles the ready interrupt signal sent by the game process
 *  Plays a note and sets ready to true, thus enabling the SP to 
 *  listen for user input.
 */ 
void readyHandler(int signum){
    signal(SIGUSR1, readyHandler);  
    ready = false;      
    OutputNote = playNote();
    ready = true;
    return;
}

/** Handles the correct interrupt signal sent by the SP
 *  Moves the ship closer and increments the score via Answerhandler
 */ 
static void correctHandler(int signum){
    signal(SIGUSR1, correctHandler); 
    if(playTime) //only move the ship if we allowed to 
        AnswerHandler(true);
    return;
}

/** Handles the incorrect interrupt signal sent by the SP
 *  Moves the ship further and decrements the score via Answerhandler
 */ 
static void incorrectHandler(int signum){
    signal(SIGUSR2, incorrectHandler);  
    if(playTime)
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


/** React to the behaviour fo the player after a note is played
 * If the player played the right note, make the ship move closer
 * and tell the player they played the correct note
 * If the player played the wrong note, make the ship move further away
 * and tell the player they were incorrect
 * If the player did not play anything, make the ship move further away
 * and tell the player they did not play a note
 * 
 */
void AnswerHandler(bool isCorrect, bool didntPlay){
    notePlayed = true;

    float winThreshold = 40.0f;
    float lossThreshold = 110.0f;

    Vector3 shipPos = ship->GetPosition();
    UIElement *root = ui->GetRoot();
        
    float MOVE_SPEED=30.0f;
    std::string correctness;
    float y;
    float z;
    if(!isCorrect || didntPlay){
        correctness = "incorrect";
        y = -10.0f;
        z = 0.0f;
        score = score - 1;
    }
    else{ //if isCorrect and !didntPlay
       correctness = "correct";
        y = 5.0f;
        z = 0.0f; 
        score = score+1;
    }

    ship->Translate(Vector3(0.0f, y, z)*timestep*MOVE_SPEED);
    

    std::string scoreTxt = {"Score: "+std::to_string(score)};
    String scoreMessage = String(scoreTxt.c_str());
    Urho3D::PODVector<Urho3D::UIElement*> scoreVec = root->GetChildrenWithTag("scoreText");
    if (scoreVec.Size() > 0){
        scoreText->SetText(scoreMessage);
    }
    else{
        scoreText = CreateText(scoreMessage, "scoreText", 590, 560);
    }
    
    std::string txt = { "You played the "+correctness+" note" };
    String txtMessage = String(txt.c_str());
    if(!didntPlay){
        CreateText(txtMessage, "correctnessText", 200, 100);  
        std::cout << "You played the "+correctness+" note\n";
    } else{
        CreateText("You didn't play a note", "correctnessText", 200, 100);  
        std::cout << "You didn't play a note\n";
    }
    

    //Check if the ship is close/far enough to call the win/loss scene

    Vector3 newShipPos = ship->GetPosition();
    float distance = newShipPos.DistanceToPoint(cameraPos);
    if (distance < winThreshold){
        ourGame->DeleteCorrectnessText();
        ourGame->DeleteScoreText();
        ourGame->CreateWinScene();
        endGame = true;
    }
    else if (distance > lossThreshold){
        ourGame->DeleteCorrectnessText();
        ourGame->DeleteScoreText();
        ourGame->CreateLossScene();
        endGame = true;
    }

}

/** Create the octree, camera and lighting for a scene
 * 
 * 
 */
void GameSys::SetupScene(){
    /** Create the Octree component to the scene. This is required before adding any drawable components, or else nothing will
     * show up. The default octree volume will be from (-1000, -1000, -1000) to (1000, 1000, 1000) in world coordinates; it
     * is also legal to place objects outside the volume but their visibility can then not be checked in a hierarchically
     * optimizing manner
     */  
    mainScene->CreateComponent<Octree>();

    /// Create a directional light to the world so that we can see something. The light scene node's orientation controls the
    /// light direction; we will use the SetDirection() function which calculates the orientation from a forward direction vector.
    /// The light will use default settings (white light, no shadows)
    /// Create a red directional light (sun)      
    Node* lightNode=mainScene->CreateChild();
    lightNode->SetDirection(Vector3::FORWARD);
    lightNode->Yaw(50);     // horizontal
    lightNode->Pitch(10);   // vertical
    Light* light=lightNode->CreateComponent<Light>();
    light->SetLightType(LIGHT_DIRECTIONAL);
       

    /// Create a scene node for the camera, which we will move around
    /// The camera will use default settings (1000 far clip distance, 45 degrees FOV, set aspect ratio automatically)
    cameraNode_ = mainScene->CreateChild("Camera");
    cameraNode_->CreateComponent<Camera>();

    /// Set an initial position for the camera scene node above the plane
    cameraNode_->SetPosition(cameraPos);
    cameraNode_->SetScale(Vector3(0, 0, 0));

    SetupViewport();
}


/**
 * CreateTitleScene function. Start screen main, with button
 * calls CreateText, provides text content, calls Subscribe to events to allow input for state change
 * 
 */
void GameSys::CreateTitleScene()
{

    SetupScene(); 
    score = 0;

    CreateBackground("Materials/planet_bg.xml");
    ui = GetSubsystem<UI>();
    UIElement *root = ui->GetRoot();
    cache = GetSubsystem<ResourceCache>();

    // Load the style sheet from xml
    root->SetDefaultStyle(cache->GetResource<XMLFile>("UI/DefaultStyle.xml"));
    auto* startButton = CreateButton(root, "StartButton", 
        "StartText", "Start Game!", 50, 500);
    auto* insButton = CreateButton(root, "InsButton", "InsText", 
        "Instructions", 400, 500);
    auto* loreButton = CreateButton(root, "LoreButton", "LoreText", 
        "Lore", 750, 500);
    auto* helloText = CreateText("Welcome to Sound Pirates!", 
        "welcomeText", 300, 300);
    SubscribeToEvent(startButton, E_CLICK, URHO3D_HANDLER(GameSys, HandleStartClick));
    SubscribeToEvent(insButton, E_CLICK, URHO3D_HANDLER(GameSys, HandleInsClick));
    SubscribeToEvent(loreButton, E_CLICK, URHO3D_HANDLER(GameSys, HandleLoreClick));
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
    text->SetColor(Color(1.0f, 1.0f, 1.0f));
    text->SetPosition(IntVector2(x, y));
    text->AddTag(tagName);
    // Add Text instance to the UI root element
    ui->GetRoot()->AddChild(text);
    return text;
}


/**
 * Creates a button on the gchar OutputNote=playNote();   
       playNote();iven root, with the given tag.
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
    t->SetHorizontalAlignment(HA_LEFT);

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

/** Handle the update called every frame of the game
 *  Takes in some informatio nabout the previous frame
 *  Loops the play tone -> user input every 6secs
 *  After 5s of the loop, makes user input impossible
 *  and shows a feedback message if the user did not
 *  play a note
 * 
 *  Also updates the timestep variable to be the time taken 
 *  of the previous frame
 * 
 * 
 */
void GameSys::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
    using namespace Update;

    // Take the frame time step, which is stored as a float
    ::timestep = eventData[P_TIMESTEP].GetFloat();
    if(countDownTimer_.GetMSec(false) >= 6000 && !endGame){
        countDownTimer_.Reset();
        DeleteCorrectnessText();
        notePlayed = false;
        playTime = true;
        kill(parentpid, SIGUSR1);
    }
    else if(countDownTimer_.GetMSec(false) >= 5000 && !endGame && playTime){
        DeleteCorrectnessText();
        if(notePlayed == false){
            AnswerHandler(false, true);
        }
        playTime = false;
    }
}

/** Delete the score text node from the main scene
 * 
 */ 
void GameSys::DeleteScoreText()
{
    //Delete existing score text from the screen if it exists
    UIElement* root = ui->GetRoot();
    Urho3D::PODVector<Urho3D::UIElement*> scoreText = root->GetChildrenWithTag("scoreText");

    if(scoreText.Size() > 0)
        scoreText[0]->Remove();       
}

/** Delete the correctness text node from the main scene
 * 
 */ 
void GameSys::DeleteCorrectnessText()
{
    //Delete existing correctness text from the screen if it exists
    UIElement* root = ui->GetRoot();
    Urho3D::PODVector<Urho3D::UIElement*> correctnessText = root->GetChildrenWithTag("correctnessText");
    if(correctnessText.Size() > 0)
        correctnessText[0]->Remove();
}

/** 
 * when you click on the start button, the second scene appears
 * 
 */

void GameSys::HandleStartClick(StringHash eventType, VariantMap& eventData)
{
    using namespace Click;
    //delete title scene UI
    GetSubsystem<UI>()->GetRoot()->RemoveAllChildren();
    //delete title scene background
    Urho3D::PODVector<Urho3D::Node *> bg = mainScene->GetChildrenWithTag("background");
    bg[0]->Remove();
    //Show the main game screen

    CreateMainScene();  

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
    //delete title scene background
    mainScene->Clear();

    //Show the instructions
    CreateInstructionsScene();
}

/** 
 * when you click on the lore button, the lore appears
 * 
 */
void GameSys::HandleLoreClick(StringHash eventType, VariantMap& eventData)
{
    using namespace Click;
    //Delete the title scene
    GetSubsystem<UI>()->GetRoot()->RemoveAllChildren();
    //delete title scene background
    mainScene->Clear();

    //Show the instructions
    CreateLoreScene();
}

/**
 * Shows the instruction text onto the screen
 */
void GameSys::CreateLoreScene()
{
    UIElement* root = GetSubsystem<UI>()->GetRoot();
    auto* backButton = CreateButton(root, "BackButton", 
        "BackText", "Back to title screen", 700, 500);   
    auto* instructionsText = CreateText(
        "You are about to enter a universe where starships sing\n"
        "to each other across the void. Where buccaneers race the\n"
        "spaceways looking for loot and smugglers run their contraband\n"
        "from port to shady port. In the Galaxy of Audiorum, ships travel\n"
        "space carrying great prizes. Fleets move as one in warp jumps,\n"
        "synchronised by ‘The Resonance’ – a tone send out by the warp\n"
        "engines encoding each jump. Planned journeys are symphonies\n"
        "played out by ships in glorious rhythm across the stars.\n\n"
        "You are taking on the role of Chantilly Lace, a pirate with\n"
        "such genius they can tweak their engines so that the Resonance\n"
        "sent out by other ships is trackable and you can catch and board\n"
        "great frigates in deep space in your mighty and feared ship\n"
        "‘The Space Shanty’.\n\n"
        "Chantilly is a former engineer turned pirate who realised\n"
        "they could use their new technology to take from the rich\n"
        "to give to the poor Robin Hood style.\n"
        "Living outside the law means you need to work with\n"
        "unsavoury types though, so Lace has built a reputation\n"
        "as a fearsome Captain and a hardy warrior.\n"
        "The problem is, the crew of The Space Shanty can see a\n"
        "whole lot of wealth, and feel not enough is going in their\n"
        "pockets! Will you be able to guide Lace through the trials\n"
        "that await?", 
        "Instructions", 100, 100);
    instructionsText->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 14);

    SubscribeToEvent(backButton, E_CLICK, URHO3D_HANDLER(GameSys, HandleBackClick));
}

/**
 * Shows the instruction text onto the screen
 */
void GameSys::CreateInstructionsScene()
{
    UIElement* root = GetSubsystem<UI>()->GetRoot();
    auto* backButton = CreateButton(root, "BackButton", 
        "BackText", "Back to title screen", 400, 500);   
    auto* instructionsText = CreateText(
        "When the game begins you are chasing your ship.\n"
        "To get closer you need to match the note that is played \n"
        "as closely and as quickly as you can. \n"
        "If you get the note right you’ll go closer to your ship,\n"
        "wrong, they get further away until either you catch them, \n"
        "or you’re stranded in space! \n\n"
        "So a tone will sound and you’ll have five seconds to play and match it. \n"
        "If you’re too slow, or too quiet, the system may not pick you up, \n"
        "so loud and fast and long! \n"
        "The notes will all be in middle C so that should give you a good starting point. \n"
        "Good Luck!", 
        "Instructions", 100, 100);
    instructionsText->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 14);

    SubscribeToEvent(backButton, E_CLICK, URHO3D_HANDLER(GameSys, HandleBackClick));
}

/**
 * Shows the instruction text onto the screen
 */
void GameSys::CreateWinScene()
{
    //delete main scene
    GetSubsystem<UI>()->GetRoot()->RemoveAllChildren();
    mainScene->Clear();
    SetupScene();
    Node* bgNode = CreateBackground("Materials/win_bg.xml");

    UIElement* root = ui->GetRoot();
    auto* resetButton = 
        CreateButton(root, "ResetButton", "ResetText", "Back to title screen", 100, 650);   
    SubscribeToEvent(resetButton, E_CLICK, URHO3D_HANDLER(GameSys, HandleResetClick));
}

/**
 * Shows the instruction text onto the screen
 */
void GameSys::CreateLossScene()
{
    
    GetSubsystem<UI>()->GetRoot()->RemoveAllChildren();
    //delete main scene
    mainScene->Clear();
    SetupScene();
    Node* bgNode = CreateBackground("Materials/lose_bg.xml");
     
    UIElement* root = GetSubsystem<UI>()->GetRoot();
    auto* resetButton = CreateButton(root, "ResetButton", 
        "ResetText", "Back to title screen", 650, 100);   
    SubscribeToEvent(resetButton, E_CLICK, URHO3D_HANDLER(GameSys, HandleResetClick));
}

/** 
 * when you click on the return to title screen, the scene is removed and title reset
 * 
 */
void GameSys::HandleResetClick(StringHash eventType, VariantMap& eventData)
{
    using namespace Click;
    //remove UI and 3D elements from the scene
    GetSubsystem<UI>()->GetRoot()->RemoveAllChildren();
 
    mainScene->Clear();

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
    //Creates the background for the scene
    Node* bgNode = CreateBackground("Materials/main_bg.xml");
    Node *zoneNode = mainScene->CreateChild("Zone");
    auto *zone = zoneNode->CreateComponent<Zone>();
    zone->SetBoundingBox(BoundingBox(-1000.0f, 1000.0f));
    scoreText = CreateText("Score: 0", "scoreText",  590, 560);
    Node *shipNode = CreateShip();
    shipNode->AddTag("ship");
    ship = shipNode;
    
           
    UIElement* root = GetSubsystem<UI>()->GetRoot();
    auto* resetButton = CreateButton(root, "ResetButton", 
        "ResetText", "Back to title screen", 400, 650);   
    
    SubscribeToEvent(resetButton, E_CLICK, URHO3D_HANDLER(GameSys, HandleResetClick));
}

/**
 * Create a background for the main scene.
 * Implemented as a cube positioned in front of the camera with the 
 * background png as a texture.
 */
Node* GameSys::CreateBackground(String path)
{
    auto* cache = GetSubsystem<ResourceCache>();

    Node* skyNode = mainScene->CreateChild("Sky");

    skyNode->SetScale(Vector3(145.0f, 104.0f, 1.0f)); 
    skyNode->SetPosition(Vector3(0.0f, -5.0f, 100.0f));
    auto* skyObject = skyNode->CreateComponent<StaticModel>();
    skyObject->SetModel(cache->GetResource<Model>("Models/Box.mdl"));
    skyObject->SetMaterial(cache->GetResource<Material>(path));
    skyNode->AddTag("background");
    

    return skyNode;
}


/**
 * CreateShip function. Creates the enemy ship to pursue
 */
Node* GameSys::CreateShip()
{
    auto *cache = GetSubsystem<ResourceCache>();
    Node *boxNode = mainScene->CreateChild("Box");
    boxNode->SetRotation(Quaternion(-115.0f, 0.0f, 0.0f));
    boxNode->SetPosition(Vector3(6.0f, 8.0f, 50.0f));
    boxNode->SetScale(Vector3(0.17f, 0.17, 0.17));
    auto *boxObject = boxNode->CreateComponent<StaticModel>();
    boxObject->SetModel(cache->GetResource<Model>("Models/SpaceShip.mdl"));
    boxObject->SetMaterial(cache->GetResource<Material>("Materials/ship_texture.xml"));
    return boxNode;  
}



/** Setup the viewport for the scene, enabling the user to see things
 *  Do this after setting up lighting and a camera in a scene
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
